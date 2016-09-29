#include "stdafx.h"
#include "CameraResultCollator.h"


IMPLEMENT_DYNCREATE(CameraResultCollator, CWinThread)

CameraResultCollator::CameraResultCollator()
{
	RCStopEvent = NULL;
	RCExitEvent = NULL;
	InitializeCriticalSection(&cameraResultMutex);
	InitializeCriticalSection(&imageMutex);	
	cameraResultReceiversList.clear();
}


CameraResultCollator::~CameraResultCollator()
{
	DeleteCriticalSection(&cameraResultMutex);
	DeleteCriticalSection(&imageMutex);
	cameraResultReceiversList.clear();
}

BOOL CameraResultCollator::InitInstance(void)
{
	return TRUE;
}


int CameraResultCollator::SetInspectionTask(std::map<UINT, InspectionTask *> *_tasksMap)
{
	if (_tasksMap != NULL)
	{
		taskMap = _tasksMap;
		noOfInspectionTasks = taskMap->size();
		return 1;
	}
	else
	{
		// ToDo Raise Excption;
		LOGERROR(_T("ERROR: Inspection Task not initilaized (Camera Result Collater::SetInspectionTask)"));
		return 0;
	}
}

int CameraResultCollator::SetStopEvent(HANDLE &_RCStopEvent, HANDLE &_RCExitEvent)
{
	if (_RCStopEvent != NULL)
	{
		this->RCStopEvent = _RCStopEvent;
	}
	else
	{
		LOGERROR(_T("ERROR: Stop Event not initilaized (CResultCollator::SetStopEvent)"));
		return 0;
	}
	if (_RCExitEvent != NULL)
	{
		this->RCExitEvent = _RCExitEvent;
	}
	else
	{
		LOGERROR(_T("ERROR: Stop Event not initilaized (CResultCollator::SetStopEvent)"));
		return 0;
	}
	return 1;
}

void CameraResultCollator::InitCameraResultCollator(int _cameraID)
{
	this->cameraID = _cameraID;
}


void CameraResultCollator::RegisterForCameraResult(iCameraResultReceiver *_cameraResultReceiver)
{
	cameraResultReceiversList.push_back(_cameraResultReceiver);
}


void CameraResultCollator::SetInspectionWindow(HRegion &_inspectionWindow)
{
	inspectionWindow = _inspectionWindow;
}

void CameraResultCollator::OnImageReceived(ImageData &_imageData)
{
	EnterCriticalSection(&imageMutex);
	int buffSize = imgDataList.size();
	LeaveCriticalSection(&imageMutex);

	if (buffSize < IMAGE_BUFFER_SIZE)
	{
		EnterCriticalSection(&imageMutex);
		imgDataList.push_back(_imageData);
		LeaveCriticalSection(&imageMutex);
	}
	else
	{
		EnterCriticalSection(&imageMutex);
		imgDataList.clear();
		imgDataList.push_back(_imageData);
		LeaveCriticalSection(&imageMutex);
		/*
		InspectionTaskException *exception;
		exception = new InspectionTaskException(inspectionItemID,inspectionType,_T("SetImage"),EX1012);
		throw exception;  */
		LOGERROR(_T("Result Collator Image Buffer overloaded"));
		// ToDo raise exception buffer overloaded

	}
}


int CameraResultCollator::Run(void)
{
	HANDLE      eventHandle[MAX_NO_OF_INSPECTION_TASKS];
	register int insIndex;
	CString             resultString;
	ResultData		    *resultData=NULL;
	int                 finalResult;
	int                 failedItemID;
	int                 denomCheckResult;
	int                 serialNumberResult;

	double              startTime = 0.0;
	double              endTime = 0.0;
	double				resStart = 0.0;
	double              timeTaken = 0.0;

	bool                resultAvailable = false;
	unsigned int        prevImageNumber = 0;
	unsigned int        maxImageNumber = 0;
	int                 resultBufferSize = 0;

	insIndex = 0;
	for (auto &e : (*taskMap))
	{
		eventHandle[insIndex] = e.second->resultEvent;
		insIndex++;
	}
	
	LOGINFO(_T("Result collator started"));

	while (WAIT_OBJECT_0 != WaitForSingleObject(RCStopEvent, 0)) // wait for inspection stop event from Model processor
	{
		while (WAIT_OBJECT_0 == WaitForMultipleObjects(noOfInspectionTasks, eventHandle,
			TRUE, RESULT_TIMEOUT))                               // any inspection items are finished processing and
																 // set result event
		{

			//LOGDEBUG(_T("Result Collation Started") << cameraID);
#ifdef RESULTS_LOG_NEEDED
			startTime = HSystem::CountSeconds();
#endif
			resultAvailable = true;
			insIndex = 0;
			for (auto &e : (*taskMap))
			{
				EnterCriticalSection(&(e.second->resultMutex));
				resultBufferSize = e.second->resultDataList.size();
				LeaveCriticalSection(&(e.second->resultMutex));
				if (resultBufferSize < 1)
				{
					resultAvailable = false;
					break;
				}
				else
				{
					EnterCriticalSection(&(e.second->resultMutex));
					resultData = e.second->resultDataList.front();
					LeaveCriticalSection(&(e.second->resultMutex));

					if (insIndex == 0)
					{
						prevImageNumber = resultData->imageNumber;
						maxImageNumber = resultData->imageNumber;
					}
					else
					{
						if (resultData->imageNumber != prevImageNumber)
						{
							LOGERROR(_T("Image count mismatch at ") << prevImageNumber << _T(" # ") << resultData->imageNumber);
							if (resultData->imageNumber < maxImageNumber)
							{
								if (resultBufferSize > 0)
								{
									EnterCriticalSection(&(e.second->resultMutex));
									e.second->resultDataList.pop_front();
									LeaveCriticalSection(&(e.second->resultMutex));
								}
							}
							else
							{
								maxImageNumber = resultData->imageNumber;
								for (int i = 0; i<insIndex; i++)
								{
									EnterCriticalSection(&(e.second->resultMutex));
									if (e.second->resultDataList.size() > 0)
									{
										e.second->resultDataList.pop_front();
									}
									LeaveCriticalSection(&(e.second->resultMutex));
								}
							}
							resultAvailable = false;
							break;
						}
					}
				}
				insIndex++;
			}
			if (!resultAvailable)
			{
				continue;
			}
#ifdef RESULTS_LOG_NEEDED
			resStart = HSystem::CountSeconds();
#endif
			finalResult = (int)NotDefined;
			failedItemID = 0;                                   // No inspection failed To define inspection id for all pass

			// Memory will be deleted at Reject Image Viewer
			shared_ptr<CameraResultData>cameraResultData = make_shared<CameraResultData>();// new CameraResultData();
			cameraResultData->cameraID = cameraID;
			// collect results from all inspection items and prepare it for sending to MCA and GUI
			for (auto &e : (*taskMap))
			{
				resultData = e.second->GetInspectionResult();
				finalResult = MIN(finalResult, resultData->result);
				cameraResultData->taskResults[e.first] = resultData;
			}
			BlobAnalyzerResultData *blobAnalysisResult = cameraResultData->GetBlobAnalysisResults();
			if (blobAnalysisResult != NULL)
			{
				for (auto &e : cameraResultData->taskResults)
				{
					if (e.second->typeOfInspection == inspection_type_LayerInspection || e.second->typeOfInspection == inspection_type_SpecialLayerInspection)
					{
						if (blobAnalysisResult->groupOfDefectBlobsUPWiseStatus.find(e.first) != blobAnalysisResult->groupOfDefectBlobsUPWiseStatus.end())
						{
							e.second->result = blobAnalysisResult->groupOfDefectBlobsUPWiseStatus[e.first].TupleMax()[0].I() ? Fail : e.second->result;
						}
					}
				}
			}
			cameraResultData->inspectionWindow = inspectionWindow;
			cameraResultData->UpdateLayerUpwiseResults();

			cameraResultData->result = (InspectionResults)finalResult;
			cameraResultData->imageNumber = prevImageNumber;
			EnterCriticalSection(&imageMutex);
			int buffSize = imgDataList.size();
			LeaveCriticalSection(&imageMutex);
			if (buffSize > 0)
			{
				EnterCriticalSection(&imageMutex);
				ImageData tempImageData = imgDataList.front();
				LeaveCriticalSection(&imageMutex);

				while (tempImageData.imageNumber < prevImageNumber)
				{
					EnterCriticalSection(&imageMutex);
					imgDataList.pop_front();
					tempImageData = imgDataList.front();
					LeaveCriticalSection(&imageMutex);
				}
				if (tempImageData.imageNumber == prevImageNumber)
				{
					cameraResultData->imageData = tempImageData;
					for (auto &e : cameraResultReceiversList)
					{
						weak_ptr<CameraResultData> temp(cameraResultData);
						e->OnCameraResultReceived(prevImageNumber, temp);
					}
				}
				else
				{
					
					//Notify GUI that Image is not received
				}
			}
			else
			{
				//Notify GUI that Image is not received
			}
#ifdef RESULTS_LOG_NEEDED
			endTime = HSystem::CountSeconds();
			std::string comma = ",";
			std::string mainLog = std::to_string(cameraResultData->imageNumber) + comma +
				std::to_string(finalResult) + comma +
				std::to_string(cameraResultData->imageData.timeStamp) + comma +
				std::to_string((endTime - cameraResultData->imageData.timeStamp) * 1000) + comma +
				std::to_string((startTime - cameraResultData->imageData.timeStamp) * 1000) + comma +
				std::to_string((endTime - startTime) * 1000) + comma +
				std::to_string((endTime - resStart) * 1000) + "\n";

				if (resultsLog.size() > MAX_RESULT_LOG_COUNT)
				{
					resultsLog.pop_front();
				}
				resultsLog.push_back(mainLog);

#endif
			// print results to screen
			timeTaken = (endTime - resultData->imageTimeStamp) * 1000;
			// moreResults = true;
			for (auto &e : (*taskMap))
			{
				EnterCriticalSection(&(e.second->resultMutex));
				resultBufferSize = e.second->resultDataList.size();
				LeaveCriticalSection(&(e.second->resultMutex));
				if (resultBufferSize > 0)
				{
					SetEvent(e.second->resultEvent);
				}
			}
			//LOGDEBUG(_T("Result collection finished ") << cameraID);
		}
	}
#ifdef RESULTS_LOG_NEEDED
	FILE            *fp;
	std::string fileName;
	fileName = std::string(IPA_LOGS_DIRECTORY) + "//Online Processing Camera Result Collator" + std::to_string(cameraID) + " Results.csv";

	fp = fopen(fileName.c_str(), "w");
	if (fp != NULL)
	{
		fprintf(fp, "ImageCount,Result,Image Time Stamp,Processing Time,Image Grab to Process Finish Time,Process finish to Result Collation & Publish Time,Result Publish Time\n");
		for (std::list<std::string>::iterator iter = this->resultsLog.begin(); iter != this->resultsLog.end(); iter++)
		{
			fprintf(fp, "%s", (*iter).c_str());
		}
		fclose(fp);
	}
	resultsLog.clear();
#endif
	// MCAResultSenderSocket.CloseSocket();
	LOGDEBUG(_T("Result collector exit "));
	SetEvent(RCExitEvent);
	::PostQuitMessage(0);   // quit threads safely
	return 1;
}