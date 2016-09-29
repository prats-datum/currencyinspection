#pragma once
#include "GoldenData.h"
#include "CameraProcessor.h"
#include <string>
#include <map>
#include "DocumentResultCollator.h"

class GoldenProcessor
{
private:
	int                     noOfCameraProcessors;                            // Number of Camera processors
	GoldenData				*goldenData;
	std::map<UINT, CameraProcessor*>	cameraProcessorsList;
	DocumentResultCollator docResultCollator;
	std::vector<GPUProvider> *gpuList;
public:
	GoldenProcessor();
	~GoldenProcessor();
	
	// Start Inspection
	int StartCameraProcessors(void);
	// Stop Inspection
	int StopCameraProcessors(void);
	// initialize model interpretor
	bool InitGoldenProcessor(std::string _modelLocation, std::map<UINT, iCameraResultReceiver *> camResultReceiversList, iStatusUpdateReceiver *_statusUpdateReceiver, ULONG _imageNumber=1);

	bool UpdateGoldenData(std::string _modelLocation, iStatusUpdateReceiver *_statusUpdateReceiver, int _imageNumber);

	std::vector<DocumentResult> *GetActiveResultBuffer();
	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}

	void SetModeOfOperation(OperationMode _operationMode);
};

