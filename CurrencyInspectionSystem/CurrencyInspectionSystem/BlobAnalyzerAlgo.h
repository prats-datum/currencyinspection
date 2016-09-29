#pragma once
#include "InspectionTask.h"
class BlobAnalyzerAlgo :
	public InspectionAlgo,
	public iLayerDifferenceImageResultReceiver,
	public iResetTransferDataNotificationReceiver
{
	BlobAnalyzerData *inspectionData;
	void UpdateData();
public:
	BlobAnalyzerAlgo();
	BlobAnalyzerAlgo(iInterTaskResultProvider *_interAlgoResultProvider) :InspectionAlgo(_interAlgoResultProvider) 
	{
		for (int i = 0; i<MAX_NUM_OF_LAYERS_PER_CAMERA; i++)
		{
			resultsRecievedEvent[i] = CreateEventW(NULL, FALSE, FALSE, NULL);
			ResetEvent(resultsRecievedEvent[i]);
		}
		numberOfLayerTasks = 0;
		inspectionData = NULL;
		InitializeCriticalSection(&ldResultMutex);
	}
	~BlobAnalyzerAlgo();

	CRITICAL_SECTION ldResultMutex;
	HTuple GroupOfDefectBlobsValues;
	HTuple errorZonesID;
	HImage blobThresholdImage;
	list<LayerDiffImageResult> layerDiffImageResultsList[MAX_NUM_OF_LAYERS_PER_CAMERA];
	HANDLE resultsRecievedEvent[MAX_NUM_OF_LAYERS_PER_CAMERA];
	int numberOfLayerTasks;
	BlobParameterLookup blopAnalyzerParameterLookup;

	virtual int SetParameters(InspectionData *inspectionData);
	virtual ResultData *ProcessImage(const PreprocessedImageData &_image, ULONG &imageNumber);
	InspectionResults DoBlobAnalysis(HImage _Image, ULONG _imageNumber, BlobAnalyzerResultData &_ResultData, map<UINT, HRegion> &layerInspectionRegion, map<UINT, HRegion> &statRegion);

	void OnLayerDifferenceImageResult(UINT _layerId, ULONG _imageNumber, int _inspectionResult, const HImage &_layerDiffImageReult, const HRegion &_statisticsRegion, const HRegion &_layerRegion);
	bool PopResultData(std::list<LayerDiffImageResult> *_reslultList, LayerDiffImageResult &_resultData, ULONG _imageNumber);
	InspectionResults RecieveLayersImage(UINT _imageNumber, HImage &superLayerImage, map<UINT, HRegion> &layerRegion, map<UINT, HRegion> &statRegion);

	void ResetResults(BlobAnalyzerResultData &_ResultData, map<UINT, HRegion> &layerInspectionRegion, map<UINT, HRegion> &statRegion);

	void OnResetTransferDataBufferNotificationReceived(); 
	virtual ResultData *ExtendGolden(const PreprocessedTrainingImageData &_image, const HRegion &_maskRegion, ULONG &_imageNumber)
	{
		return new ResultData(_imageNumber, Pass);
	}
};

