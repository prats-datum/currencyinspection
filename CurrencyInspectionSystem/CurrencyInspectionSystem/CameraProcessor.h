#pragma once
#include "InspectionTask.h"
#include "ImageGrabber.h"
#include "InterTaskCommunicator.h"
#include "GoldenData.h"
#include "CameraResultCollator.h"
#include "ImageSourceSettingsReader.h"

class CameraProcessor
{
	int cameraID;
	CameraData cameraData;
	ImageGrabber *imageGrabber;
	ImagePreprocessor *imagePreprocessor;
	CameraResultCollator *camResultCollator;
	std::map<UINT, InspectionTask *> inspectionTasksList;
	std::vector<iCameraResultReceiver *> cameraResultReceiversList;
	std::vector<GPUProvider> *gpuList;
	InterTaskCommunicator interTaskCommunicator;
	HANDLE exitEventForInspectionTasks, exitEventForImageGrabber, exitEventForResultCollator, imgGrabberExitedEvent, resultCollatorExitedEvent, pauseEventforInspectionTasks, resumeEventforInspectionTasks; 
	HANDLE exitEventForImagePreprocessor, imagePreprocessorExitedEvent;
	HANDLE allInspectionTaskExitedEvents[MAX_NO_OF_INSPECTION_TASKS], allInspectionTaskPausedEvents[MAX_NO_OF_INSPECTION_TASKS], allInspectionTaskResumedEvents[MAX_NO_OF_INSPECTION_TASKS];

public:
	CameraProcessor();
	~CameraProcessor();

	// Start Inspection
	int StartCameraProcessors(void);
	// Stop Inspection
	int StopCameraProcessors(void);
	// initialize model interpretor
	bool InitCameraProcessor(CameraData &_cameraData, ULONG _imageNumber);

	bool UpdateCameraProcessor(CameraData &_cameraData);
	bool PauseCameraProcessor();
	bool ResumeCameraProcessor();
	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}

	void SetCameraResultReceiver(std::vector<iCameraResultReceiver *> _cameraResultReceiversList);
};

