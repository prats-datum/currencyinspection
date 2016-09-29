#include "stdafx.h"
#include "BlobAnalyzerAlgo.h"
#include "InspectionParametersConfigReader.h"

BlobAnalyzerAlgo::BlobAnalyzerAlgo()
{
}


BlobAnalyzerAlgo::~BlobAnalyzerAlgo()
{
	if (inspectionData != NULL)
	{
		delete inspectionData;
	}
}

bool BlobAnalyzerAlgo::PopResultData(std::list<LayerDiffImageResult> *_reslultList, LayerDiffImageResult &_resultData, ULONG _imageNumber)
{
	bool received = false;

	_resultData = _reslultList->front();

	if (_resultData.imageNumber == _imageNumber)
	{
		_reslultList->pop_front();
		received = true;
	}
	else if (_resultData.imageNumber < _imageNumber)
	{
		_reslultList->pop_front();
		received = false;
	}
	else
	{
		received = true;
	}
	return received;
}

void BlobAnalyzerAlgo::OnLayerDifferenceImageResult(UINT _layerId, ULONG _imageNumber, int _inspectionResult, const HImage &_layerDiffImageReult, const HRegion &_statisticsRegion, const HRegion &_layerRegion)
{
	//LayerDiffImageResult layerDiffImageData(_layerId, _imageNumber, _inspectionResult, _layerDiffImageReult, _statisticsRegion, _layerRegion);
	LayerDiffImageResult layerDiffImageData(_layerId, _imageNumber, _inspectionResult, _layerDiffImageReult, _statisticsRegion, _layerDiffImageReult.Threshold(1.0, 255.0));

	for (register int i = 0; i<numberOfLayerTasks; i++)
	{
		if (_layerId == inspectionData->layerInspectionTaskID[i])
		{
			EnterCriticalSection(&ldResultMutex);
			layerDiffImageResultsList[i].push_back(layerDiffImageData);
			SetEvent(resultsRecievedEvent[i]);
			LeaveCriticalSection(&ldResultMutex);
			break;
		}
	}

}


int BlobAnalyzerAlgo::SetParameters(InspectionData *_inspectionData)
{
	inspectionData = static_cast<BlobAnalyzerData *> (_inspectionData);
	UpdateData();
	return 1;
}

void BlobAnalyzerAlgo::UpdateData()
{
	numberOfLayerTasks = inspectionData->layerInspectionTaskID.size();
	for (int index = 0; index < numberOfLayerTasks; index++)
	{
		interAlgoResultProvider->RegisterForLayerDiffImageResult(inspectionData->layerInspectionTaskID[index], this);
	}
	interAlgoResultProvider->RegisterForResetTransferDataBufferNotification(this);
	blopAnalyzerParameterLookup = InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[inspectionData->blopParametersGroupID];

	HImage temp;
	temp.GenImageConst("byte", inspectionData->imageWidth, inspectionData->imageHeight);
	blobThresholdImage = temp.GenImageProto(blopAnalyzerParameterLookup.globalTolerance);
}

void BlobAnalyzerAlgo::ResetResults(BlobAnalyzerResultData &_ResultData, map<UINT, HRegion> &layerInspectionRegion, map<UINT, HRegion> &statRegion)
{
	_ResultData.result = Pass;
	_ResultData.disconnectedMajorBlob.GenEmptyObj();
	_ResultData.dominantBlob.GenEmptyObj();
	_ResultData.disconnectedMajorBlobEnergy = 0;
	_ResultData.dominantBlobEnergy = 0;
	_ResultData.groupOfDefectBlobsUPWiseEnergy = _ResultData.groupOfDefectBlobsUPWiseEnergy.TupleGenConst(inspectionData->UpWisePartation.CountObj(), 0);
	_ResultData.groupOfDefectBlobsUPWiseStatus[inspectionData->taskID] = _ResultData.groupOfDefectBlobsUPWiseEnergy;
	for (auto &e : layerInspectionRegion)
	{
		_ResultData.groupOfDefectBlobsUPWiseStatus[e.first] = _ResultData.groupOfDefectBlobsUPWiseEnergy;
	}
	for (auto &e : statRegion)
	{
		HTuple zeroTup;
		zeroTup = zeroTup.TupleGenConst(e.second.CountObj(), 0);
		_ResultData.statisticsResultStatus[e.first] = zeroTup;
	}
}

InspectionResults BlobAnalyzerAlgo::DoBlobAnalysis(HImage _Image, ULONG _imageNumber, BlobAnalyzerResultData &_ResultData, map<UINT, HRegion> &layerInspectionRegion,
	map<UINT, HRegion> &statRegion)
{	
	HTuple imgWidth, imgHeight;
	HTuple row, col;
	HRegion defectRegion;
	InspectionResults returnValue = Pass;
	_ResultData.result = Pass;
	
	HImage DiffImageAfterBlobThreshold;
	_Image.GetImageSize(&imgWidth, &imgHeight);
	defectRegion = _Image.Threshold(1.0, 255.0);

	if (defectRegion.Area() > 0)
	{
		if (defectRegion.Area() < 200000)
		{
			HRegion closedDefectRegion = defectRegion.ClosingRectangle1(5, 5);
			HRegion DefectCandidates = closedDefectRegion.Connection();
			DiffImageAfterBlobThreshold = _Image.SubImage(blobThresholdImage, 1.0, 0.0);
			_ResultData.disconnectedMajorBlob = DefectCandidates.SelectGray(DiffImageAfterBlobThreshold, "area", "and", (double)blopAnalyzerParameterLookup.majorBlobThreshold, (double)(imgWidth * imgHeight * 255.0));
			if (_ResultData.disconnectedMajorBlob.CountObj() > 0)
			{
				_ResultData.dominantBlob = _ResultData.disconnectedMajorBlob.SelectGray(DiffImageAfterBlobThreshold, "area", "and", (double)(blopAnalyzerParameterLookup.dominantBlobThreshold + blopAnalyzerParameterLookup.majorBlobThreshold), (double)(imgWidth * imgHeight * 255.0));
				if (_ResultData.dominantBlob.CountObj() > 0)
				{
					_ResultData.dominantBlobEnergy = _ResultData.dominantBlob.AreaCenterGray(DiffImageAfterBlobThreshold, &row, &col);
					_ResultData.dominantBlobEnergy = _ResultData.dominantBlobEnergy - blopAnalyzerParameterLookup.majorBlobThreshold;
					returnValue = Fail;
				}
				else
				{
					_ResultData.dominantBlob.GenEmptyObj();
				}

				//
				HRegion GroupOfDefectBlobsUpWise = inspectionData->UpWisePartation.Intersection(_ResultData.disconnectedMajorBlob);
				HTuple groupOfDefectBlobsUPWiseEnergytemp = GroupOfDefectBlobsUpWise.AreaCenterGray(DiffImageAfterBlobThreshold, &row, &col) - blopAnalyzerParameterLookup.majorBlobThreshold;
				HTuple groupOfDefectBlobsUPWiseStatustemp = groupOfDefectBlobsUPWiseEnergytemp.TupleGreaterElem(blopAnalyzerParameterLookup.groupOfBlobThreshold);

				_ResultData.groupOfDefectBlobsUPWiseEnergy = groupOfDefectBlobsUPWiseEnergytemp;

				HTuple qualifiedMajorBlobIndex = groupOfDefectBlobsUPWiseStatustemp.TupleFind(1);
				HRegion qualifiedMajorBlob;
				qualifiedMajorBlob.GenEmptyRegion();
				if (qualifiedMajorBlobIndex >= 0)
				{
					qualifiedMajorBlob = GroupOfDefectBlobsUpWise.SelectObj(qualifiedMajorBlobIndex.TupleAdd(1));
					returnValue = InspectionResults::Fail;
				}
				HRegion overallDefects = qualifiedMajorBlob.Union2(_ResultData.dominantBlob).Union1();

				//statistics region result status computation
				for (auto &e : statRegion)
				{
					_ResultData.statisticsResultStatus[e.first] = e.second.Intersection(overallDefects).Area();
				}

				HRegion failedPartations = inspectionData->UpWisePartation.Intersection(overallDefects);
				HTuple areaTemp = failedPartations.Area();
				_ResultData.groupOfDefectBlobsUPWiseStatus[inspectionData->taskID] = areaTemp;
				for (auto &e : layerInspectionRegion)
				{
					HRegion layerInsp = e.second;
					HRegion GroupOfDefectBlobsUpWise3 = failedPartations.Intersection(e.second);
					_ResultData.groupOfDefectBlobsUPWiseStatus[e.first] = GroupOfDefectBlobsUpWise3.Area();
				}


				_ResultData.disconnectedMajorBlob = _ResultData.disconnectedMajorBlob.Difference(_ResultData.dominantBlob);
				_ResultData.disconnectedMajorBlob = _ResultData.disconnectedMajorBlob.SelectShape(HTuple("area"), HTuple("and"), HTuple(1), HTuple(imgWidth * imgHeight));

				if (_ResultData.disconnectedMajorBlob.CountObj() > 0)
				{
					_ResultData.disconnectedMajorBlobEnergy = _ResultData.disconnectedMajorBlob.AreaCenterGray(DiffImageAfterBlobThreshold, &row, &col);
					_ResultData.disconnectedMajorBlobEnergy = _ResultData.disconnectedMajorBlobEnergy - blopAnalyzerParameterLookup.majorBlobThreshold;
				}
				else
				{
					_ResultData.disconnectedMajorBlob.GenEmptyObj();
				}
			}
			else
			{
				ResetResults(_ResultData, layerInspectionRegion, statRegion);
			}
			_ResultData.result = returnValue;
		}
		else
		{
			//char location[100];
			//sprintf(location, "D:\\DiffImage%d.bmp", _imageNumber);
			//_Image.WriteImage("bmp", 0, location);
			_ResultData.result = Fail;
			returnValue = Fail;
			DiffImageAfterBlobThreshold = _Image.SubImage(blobThresholdImage, 1.0, 0.0);
			_ResultData.dominantBlob = defectRegion;
			_ResultData.dominantBlobEnergy = _ResultData.dominantBlob.AreaCenterGray(DiffImageAfterBlobThreshold, &row, &col);
			_ResultData.disconnectedMajorBlob = defectRegion;
			_ResultData.disconnectedMajorBlobEnergy = _ResultData.dominantBlobEnergy;

			HRegion GroupOfDefectBlobsUpWise = inspectionData->UpWisePartation.Intersection(_ResultData.disconnectedMajorBlob);
			HTuple groupOfDefectBlobsUPWiseEnergytemp = GroupOfDefectBlobsUpWise.AreaCenterGray(DiffImageAfterBlobThreshold, &row, &col) - blopAnalyzerParameterLookup.majorBlobThreshold;
			HTuple groupOfDefectBlobsUPWiseStatustemp = groupOfDefectBlobsUPWiseEnergytemp.TupleGreaterElem(blopAnalyzerParameterLookup.groupOfBlobThreshold);

			_ResultData.groupOfDefectBlobsUPWiseEnergy = groupOfDefectBlobsUPWiseEnergytemp;

			//statistics region result status computation
			for (auto &e : statRegion)
			{
				_ResultData.statisticsResultStatus[e.first] = e.second.Intersection(defectRegion).Area();
			}

			HRegion failedPartations = inspectionData->UpWisePartation.Intersection(defectRegion);
			HTuple areaTemp = failedPartations.Area();
			_ResultData.groupOfDefectBlobsUPWiseStatus[inspectionData->taskID] = areaTemp;
			for (auto &e : layerInspectionRegion)
			{
				HRegion layerInsp = e.second;
				HRegion GroupOfDefectBlobsUpWise3 = failedPartations.Intersection(e.second);
				_ResultData.groupOfDefectBlobsUPWiseStatus[e.first] = GroupOfDefectBlobsUpWise3.Area();
			}
		}
	}
	else
	{
		ResetResults(_ResultData, layerInspectionRegion, statRegion);
	}
	return returnValue;
}
ResultData *BlobAnalyzerAlgo::ProcessImage(const PreprocessedImageData &_image, ULONG &_imageNumber)
{
	HImage superLayerImage;
	superLayerImage.GenEmptyObj();
	bool isGrossDefectPresent;
	HRegion MajorBlob, DominantBlob;
	BlobAnalyzerResultData *blobAnalyzerResultData = new BlobAnalyzerResultData();
	HTuple majorBlobDefectValues, dominantBlobsDefectValue, GroupOfBlobDefectValue, biggestDominantDefectValue;
	map<UINT, HRegion> layerInspectionRegion, statisticsRegion;

	InspectionResults result = InspectionResults::Pass;
	result = RecieveLayersImage(_imageNumber, superLayerImage, layerInspectionRegion, statisticsRegion);
	InspectionResults isPass = DoBlobAnalysis(superLayerImage, _imageNumber, *blobAnalyzerResultData, layerInspectionRegion, statisticsRegion);
	result = MIN(result, isPass);
	blobAnalyzerResultData->result = result;
	return blobAnalyzerResultData;
}

InspectionResults BlobAnalyzerAlgo::RecieveLayersImage(UINT _imageNumber, HImage &superLayerImage, map<UINT, HRegion> &layerRegion, map<UINT, HRegion> &statRegion)
{
	InspectionResults result = NotDefined;
	bool isAllLayerResultsReceived = true;
	LayerDiffImageResult diffImageData;
		
	for (int cCount = 0; cCount < numberOfLayerTasks; cCount++)
	{
		bool received = false;
		do
		{
			EnterCriticalSection(&ldResultMutex);
			int tpBufferSize = layerDiffImageResultsList[cCount].size();
			LeaveCriticalSection(&ldResultMutex);
			if (tpBufferSize > 0)
			{
				EnterCriticalSection(&ldResultMutex);
				received = PopResultData(&layerDiffImageResultsList[cCount], diffImageData, _imageNumber);
				LeaveCriticalSection(&ldResultMutex);
				result = (InspectionResults)MIN(result, diffImageData.inspectionResult);
				if (superLayerImage.CountObj() < 1)
				{
					superLayerImage = diffImageData.layerImageResult.FullDomain().CopyImage();
				}
				else
				{
					superLayerImage = superLayerImage.MaxImage(diffImageData.layerImageResult.FullDomain());
				}
				statRegion[diffImageData.sourceTaskID] = diffImageData.statisticsRegion;
				layerRegion[diffImageData.sourceTaskID] = diffImageData.layerRegion;
			}
			else if (WAIT_OBJECT_0 == WaitForSingleObject(resultsRecievedEvent[cCount], LAYER_RESULT_TIME_OUT))
			{
				EnterCriticalSection(&ldResultMutex);
				tpBufferSize = layerDiffImageResultsList[cCount].size();
				LeaveCriticalSection(&ldResultMutex);

				if (tpBufferSize > 0)
				{
					EnterCriticalSection(&ldResultMutex);
					received = PopResultData(&(layerDiffImageResultsList[cCount]), diffImageData, _imageNumber);
					LeaveCriticalSection(&ldResultMutex);
					result = (InspectionResults)MIN(result, diffImageData.inspectionResult);
					if (superLayerImage.CountObj() < 1)
					{
						superLayerImage = diffImageData.layerImageResult.FullDomain().CopyImage();
					}
					else
					{
						superLayerImage = superLayerImage.MaxImage(diffImageData.layerImageResult.FullDomain());
					}
					statRegion[diffImageData.sourceTaskID] = diffImageData.statisticsRegion;
					layerRegion[diffImageData.sourceTaskID] = diffImageData.layerRegion;
				}
			}
			else
			{
				LOGDEBUG(_T("Receive Layer Result Timeout!!!"));
				received = true;
				isAllLayerResultsReceived &= false;
			}

		} while (!received);
	}
	if (!isAllLayerResultsReceived)
	{
		result = MIN(result, InspectionResults::Error);
	}
	return result;
}

void BlobAnalyzerAlgo::OnResetTransferDataBufferNotificationReceived()
{
	for (int cCount = 0; cCount < numberOfLayerTasks; cCount++)
	{
		EnterCriticalSection(&ldResultMutex);
		layerDiffImageResultsList[cCount].clear();
		LeaveCriticalSection(&ldResultMutex);
	}
}
