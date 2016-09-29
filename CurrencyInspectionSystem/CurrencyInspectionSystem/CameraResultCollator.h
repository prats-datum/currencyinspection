#pragma once
#include<map>
#include "InspectionTask.h"


class CameraResultCollator :
	public CWinThread, public iImageReceiver
{
	DECLARE_DYNCREATE(CameraResultCollator)

	int cameraID;
	int noOfInspectionTasks;
	HRegion inspectionWindow;
	std::map<UINT, InspectionTask *> *taskMap;
	HANDLE RCStopEvent;                        // result collator stop event
	HANDLE RCExitEvent;                        // result collator thread terminated event
	std::list<iCameraResultReceiver *>	 cameraResultReceiversList;
	CRITICAL_SECTION                 cameraResultMutex;                           // critical section to access 
	CRITICAL_SECTION                 imageMutex;                            // critical section to access image data
	std::list<ImageData>              imgDataList;                          // image list
	std::list<std::string> resultsLog;
public:
	CameraResultCollator();
	~CameraResultCollator();

	// virtual function override from CWinthread
	virtual BOOL InitInstance();
	// virtual function override from CWinthread
	virtual int Run();
	//set inspection items to collect results
	int SetInspectionTask(std::map<UINT, InspectionTask *> *_tasksMap);
	// set result collator stop event
	int SetStopEvent(HANDLE &_RCStopEvent, HANDLE &_RCExitEvent);
	// set camera id associated to Result collator
	void InitCameraResultCollator(int _cameraID);

	void RegisterForCameraResult(iCameraResultReceiver *_cameraResultReceiver);

	void SetInspectionWindow(HRegion &inspectionWindow);

	// inline function  to assign image to image buffer
	virtual void OnImageReceived(ImageData &_imageData);
};

