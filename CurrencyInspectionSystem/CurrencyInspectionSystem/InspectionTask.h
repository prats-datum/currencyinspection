#pragma once
#include "Halconcpp.h"
#include "InterTaskCommunicator.h"
#include "Logger.h"
#include "Globals.h"
#include "GoldenData.h"
#include "ResultData.h"
#include "GPUProvider.h"
#include "ImagePreprocessor.h"
#include "LayerBuildingAssistThread.h"
#include "LayerProcessingAssistThread.h"

using namespace HalconCpp;

class InspectionAlgo
{
protected:
	iInterTaskResultProvider  *interAlgoResultProvider;
public:
	int inspectionItemID;

public:
	// Initializes an instance of InspectionAlgo class.
	InspectionAlgo(void);
	InspectionAlgo(iInterTaskResultProvider *_printInspectionResultProvider);
	// Releases the memory allocated for InspectionAlgo class instance. 
	~InspectionAlgo(void);

	virtual InspectionData* GetParameters() { return NULL; }
	virtual int SetParameters(InspectionData *inspectionData) { return 1; }
	// Function that process image and find corners of the document
	virtual ResultData *ProcessImage(const PreprocessedImageData &_image, ULONG &imageNumber) { return new ResultData(); };
	virtual ResultData *ExtendGolden(const PreprocessedTrainingImageData &_image, const HRegion &_maskRegion, ULONG &_imageNumber) { return NULL; }
	virtual string GetTimeLog() { return ""; }
	virtual string GetTimeLogHeader() { return ""; }
};


class InspectionTask :
	public CWinThread, public iPreprocessedImageReceiver
{

	DECLARE_DYNCREATE(InspectionTask)
private:
	std::list<std::string> resultsLog;
	std::vector<GPUProvider> *gpuList;
protected:
	iInterTaskResultProvider  *interTaskResultProvider;
	DWORD_PTR	affinityMask;
public:
	int                               inspectionItemID;                     // inspection item ID
	std::string						  inspectionName;
	InspectionTypes                   inspectionType;                       // inspection type
	InspectionAlgo                    *inspectionAlgo;                      // inspection input parameters
	std::list<ResultData *>			  resultDataList;                       // result data list
	std::list<PreprocessedImageData>  imgDataList;                          // image list
	ResultData *resultData;

	CRITICAL_SECTION                 imageMutex;                            // critical section to access image data
	CRITICAL_SECTION                 resultMutex;                           // critical section to access result
	HANDLE                           newImageEvent;                         // event from image acquisition
	HANDLE                           resultEvent;                           // event to result collator
	HANDLE                           inspectionStopEvent;                   // event to stop processing  
	HANDLE                           inspectionExitEvent;                   // event raised by inspection thread on exit
	HANDLE							 pauseInspectionEvent;					// event to pause processing
	HANDLE							 inspectionPausedEvent;					// event raised by inspection thread on pause
	HANDLE							 resumeInspectionEvent;					// event to resume processing
	HANDLE							 inspectionResumedEvent;				// event raised by inspection thread on resume
	HANDLE							 assistThreadStopEvent;
	HANDLE							 assistThreadExitEvent;

	LayerProcessingAssistThread		 *assitThread;

	int                              modelLoaded;                           // sets if inspection model loaded successfully  
public:
	// Initializes an instance of InspectionTask class.       
	InspectionTask(void);
	// Releases the memory allocated for InspectionTask class instance. 
	~InspectionTask(void);
	// to set processing stop event
	void SetStopEvent(HANDLE &_inspectionStopEvent, HANDLE &_inspectionExitEvent);
	// to set processing pause & resume event
	void SetUpdateEvent(HANDLE &_pauseInspectionEvent, HANDLE &_inspectionPausedEvent, HANDLE &_resumeInspectionEvent, HANDLE &_inspectionResumedEvent);
	// Set inspection algorithm for an inspection task thread
	virtual int SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType, InspectionData *_inspectionData, iInterTaskResultProvider *_inspectionTaskResultProvider);
	// Set inspection algorithm for an inspection task thread

	virtual int SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType, DWORD_PTR _affinityMask, InspectionData *_inspectionData, iInterTaskResultProvider *_inspectionTaskResultProvider);

	virtual int UpdateInspectionModel(InspectionData *_inspectionData);
#pragma endregion
	// virtual function override from base class
	virtual BOOL InitInstance(void);
	// virtual function override from base class
	virtual int Run(void);
#pragma region inline functions
	// inline function  to assign image to image buffer
	virtual void OnPreprocessedImageReceived(PreprocessedImageData &imageData);

	// inline Function to ass result to inspection result buffer
	void AddToResultDataList(ResultData *_resultData);

	// inline function to get inspection result
	ResultData * GetInspectionResult()
	{
		ResultData *_inspectionResult=NULL;
		EnterCriticalSection(&resultMutex);
		if (resultDataList.size() > 0)
		{
			_inspectionResult = resultDataList.front();
			resultDataList.pop_front();
		}
		LeaveCriticalSection(&resultMutex);
		return _inspectionResult;
	}
	// inline function to clear image and inspection results buffers
	void ClearInspectionResultsBuffer()
	{
		EnterCriticalSection(&resultMutex);
		resultDataList.clear();
		LeaveCriticalSection(&resultMutex);

		EnterCriticalSection(&imageMutex);
		imgDataList.clear();
		LeaveCriticalSection(&imageMutex);

	}

	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}
#pragma endregion

};

