#pragma once
#include "InspectionTask.h"
#include "ImageGrabber.h"
#include "InterTaskCommunicator.h"
#include "GoldenData.h"
#include "ModelBuidingTask.h"
#include<map>

class CameraModelGenerator :
	public CWinThread,
	public iModelBuildiingEventReceiver,
	public GPUProvider
{
	DECLARE_DYNCREATE(CameraModelGenerator)
	int cameraID;
	ImageGrabber *imageGrabber;
	InterTaskCommunicator interTaskCommunicator;
	CameraData* cameraModelData;
	std::map<UINT, ModelBuidingTask *> modelBuildersList;

	HANDLE modelBuildCancelEvent;
	HANDLE threadExitEvent;
	HANDLE exitEvent;
	HANDLE allBuiderTaskExitedEvents[MAX_NO_OF_INSPECTION_TASKS];
	HANDLE imageExtensionCompletedEvent[MAX_NO_OF_INSPECTION_TASKS];
	std::list<iModelBuildiingEventReceiver *> modelBuildiingEventReceiverList;
	std::vector<GPUProvider> *gpuList;
public:
	CameraModelGenerator();
	~CameraModelGenerator();

	// virtual function override from base class
	virtual BOOL InitInstance(void);
	// virtual function override from base class
	virtual int Run(void);

	int InitCameraProcessor(CameraData &_camData);

	virtual void OnModelBuidingExceptionReceived(UINT trainingSetNumber, UINT taskID, IPAException *exception);

	void SetEvents(HANDLE &_modelBuildCancelEvent, HANDLE &_threadExitEvent)
	{
		modelBuildCancelEvent = _modelBuildCancelEvent;
		threadExitEvent = _threadExitEvent;
	}

	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}

	void AddModelBuildingExceptionReceiver(iModelBuildiingEventReceiver *exceptionReceiver)
	{
		modelBuildiingEventReceiverList.push_back(exceptionReceiver);
	}

	virtual int OpenGPU();
	virtual int InitAndActivateGPU();
	virtual int CloseGPU();
};

