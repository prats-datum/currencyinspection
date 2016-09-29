#include "stdafx.h"
#include "InspectionTask.h"
#include "LayerInspectionAlgo.h"
#include "ThreadInspectionAlgo.h"
#include "BlobAnalyzerAlgo.h"
#include "MeasurementAlgo.h"

#include "Advantech.h"

InspectionAlgo::InspectionAlgo(void)
{
	inspectionItemID = 0;
}
InspectionAlgo::InspectionAlgo(iInterTaskResultProvider *_interAlgoResultProvider)
{
	inspectionItemID = 0;
	this->interAlgoResultProvider = _interAlgoResultProvider;

}
/*------------------------------------------------------------------------------------------------------------------
FUNCTION: ~InspectionAlgo(void)

PURPOSE:
Releases the memory allocated for InspectionAlgo class instance.
PARAMETERS:
None.
RETURN VALUE:
None.
------------------------------------------------------------------------------------------------------------------*/
InspectionAlgo::~InspectionAlgo(void)
{

}
#pragma endregion

#pragma region Inspetion Task methods
IMPLEMENT_DYNCREATE(InspectionTask, CWinThread)
/*-----------------------------------------------------------------------------------------------------------------
FUNCTION: InspectionTask(void)

PURPOSE:
Initializes an instance of InspectionTask class.
PARAMETERS:
None.
RETURN VALUE:
None.
------------------------------------------------------------------------------------------------------------------*/

InspectionTask::InspectionTask(void)
{
	newImageEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	resultEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	assistThreadStopEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	assistThreadExitEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&imageMutex);
	InitializeCriticalSection(&resultMutex);
	ResetEvent(newImageEvent);
	ResetEvent(resultEvent);
	inspectionAlgo = NULL;
	modelLoaded = false;
}
/*------------------------------------------------------------------------------------------------------------------
FUNCTION: ~InspectionAlgo(void)

PURPOSE:
Releases the memory allocated for InspectionTask class instance.
PARAMETERS:
None.
RETURN VALUE:
None.
------------------------------------------------------------------------------------------------------------------*/
InspectionTask::~InspectionTask(void)
{
	DeleteCriticalSection(&imageMutex);
	DeleteCriticalSection(&resultMutex);
	if (inspectionAlgo != NULL)
	{
		delete inspectionAlgo;
	}
}
/*------------------------------------------------------------------------------------------------------------------
FUNCTION: SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType,CString _parameterFile)
PURPOSE:
Set inspection algorithm for an inspection task thread
PARAMETERS:
_inspectionItemID   - inspection ID
_inspectionType     - inspection type
_parameterFile      - parameter file
RETURN VALUE:
Returns 1 if inspection algorithm set successfully, returns 0 otherwise
------------------------------------------------------------------------------------------------------------------*/
int InspectionTask::SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType, InspectionData *_inspectionData, iInterTaskResultProvider *_interAlgoResultProvider)
{
	this->inspectionItemID = _inspectionItemID;
	this->inspectionType = _inspectionType;
	this->interTaskResultProvider = _interAlgoResultProvider;
	this->inspectionName = _inspectionData->taskName;
	int retVal;
	switch (_inspectionType)
	{
	case inspection_type_None:
		inspectionAlgo = new InspectionAlgo(_interAlgoResultProvider);
		break;

	case inspection_type_LayerInspection:
	case inspection_type_SpecialLayerInspection:
		inspectionAlgo = new LayerInspectionAlgo(_interAlgoResultProvider);
		break;
	case inspection_type_ThreadDetection:
		inspectionAlgo = new ThreadInspectionAlgo(_interAlgoResultProvider);
		break;
	case inspection_type_Measurement:
		inspectionAlgo = new MeasurementAlgo(_interAlgoResultProvider);
		break;
	case inspection_type_BlobAnalyser:
		inspectionAlgo = new BlobAnalyzerAlgo(_interAlgoResultProvider);
		break;
	default:
		inspectionAlgo = new InspectionAlgo(_interAlgoResultProvider);
		LOGERROR(_T("Undefined Inspection Type ") << _inspectionType << _T(" for InspectionID ") << _inspectionItemID);
	}
	retVal = inspectionAlgo->SetParameters(_inspectionData);
	modelLoaded = retVal;
	return retVal;
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType,CString _parameterFile)
PURPOSE:
Set inspection algorithm for an inspection task thread
PARAMETERS:
_inspectionItemID   - inspection ID
_inspectionType     - inspection type
_parameterFile      - parameter file
RETURN VALUE:
Returns 1 if inspection algorithm set successfully, returns 0 otherwise
------------------------------------------------------------------------------------------------------------------*/
int InspectionTask::SetInspectionModel(int _inspectionItemID, InspectionTypes _inspectionType, DWORD_PTR _affinityMask, InspectionData *_inspectionData, iInterTaskResultProvider *_interAlgoResultProvider)
{
	affinityMask = _affinityMask;
	return SetInspectionModel(_inspectionItemID, _inspectionType, _inspectionData, _interAlgoResultProvider);
}


int InspectionTask::UpdateInspectionModel(InspectionData *_inspectionData)
{
	return inspectionAlgo->SetParameters(_inspectionData);
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: SetStopEvent(HANDLE& _inspectionStopEvent,  HANDLE &_inspectionExitEvent))

PURPOSE:
Set stop event so that camera processor can stop inspection
PARAMETERS:
_inspectionStopEvent    - event to stop inspection
_inspectionExitEvent    - event raised by inspection thread on exit of run function
RETURN VALUE:
Returns void
------------------------------------------------------------------------------------------------------------------*/
void InspectionTask::SetStopEvent(HANDLE& _inspectionStopEvent, HANDLE &_inspectionExitEvent)
{
	this->inspectionStopEvent = _inspectionStopEvent;
	this->inspectionExitEvent = _inspectionExitEvent;
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: SetUpdateEvent(HANDLE &_pauseInspectionEvent, HANDLE &_inspectionPausedEvent, HANDLE &_resumeInspectionEvent, HANDLE &_inspectionResumedEvent)

PURPOSE:
Set update event so that camera processor can stop inspection
PARAMETERS:
_pauseInspectionEvent	- event to pause processing
_inspectionPausedEvent	- event raised by inspection thread on pause
_resumeInspectionEvent	- event to resume processing
_inspectionResumedEvent - event raised by inspection thread on resume
RETURN VALUE:
Returns void
------------------------------------------------------------------------------------------------------------------*/
void InspectionTask::SetUpdateEvent(HANDLE &_pauseInspectionEvent, HANDLE &_inspectionPausedEvent, HANDLE &_resumeInspectionEvent, HANDLE &_inspectionResumedEvent)
{
	this->pauseInspectionEvent = _pauseInspectionEvent;
	this->inspectionPausedEvent = _inspectionPausedEvent;
	this->resumeInspectionEvent = _resumeInspectionEvent;
	this->inspectionResumedEvent = _inspectionResumedEvent;
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: InitInstance(void)

PURPOSE:
on initialization of thread
PARAMETERS:
None
RETURN VALUE:
Returns true if successful. Otherwise, returns false.
------------------------------------------------------------------------------------------------------------------*/
BOOL InspectionTask::InitInstance(void)
{
	return TRUE;
}



void InspectionTask::OnPreprocessedImageReceived(PreprocessedImageData &_imageData)
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
		LOGERROR(_T("Image Buffer overloaded for inspection item") << inspectionItemID);
		// ToDo raise exception buffer overloaded

	}
	SetEvent(newImageEvent);
	//CString Log;
	//Log.Format(_T("Image Buffer Size =  %d"), buffSize);
	//LOGDEBUG(Log);
}


void InspectionTask::AddToResultDataList(ResultData *_resultData)
{
	EnterCriticalSection(&resultMutex);
	int buffSize = resultDataList.size();
	LeaveCriticalSection(&resultMutex);


	if (buffSize < RESULT_BUFFER_SIZE)
	{
		EnterCriticalSection(&resultMutex);
		resultDataList.push_back(_resultData);
		LeaveCriticalSection(&resultMutex);
	}
	else
	{
		EnterCriticalSection(&resultMutex);
		resultDataList.clear();
		resultDataList.push_back(_resultData);        // push last result to result data list
		LeaveCriticalSection(&resultMutex);
		/*           InspectionTaskException *exception;
		exception = new InspectionTaskException(inspectionItemID,inspectionType,_T("AddToResultDataList"),EX1012);
		throw exception;   */
		LOGERROR(_T("Inspection Task Result Buffer overflow Inspection Result dumped"));          

	}
	SetEvent(resultEvent);

	//LOGDEBUG(_T("Result Buffer Size = ")<<buffSize);
}

#include <time.h>
double GetTimeStamp()
{
	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	return difftime(timer, mktime(&y2k));
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: Run(void)

PURPOSE:
Thread function to process image as per inspection algo

PARAMETERS:
None

RETURN VALUE:
Returns 1 if successful. Otherwise, returns 0.
------------------------------------------------------------------------------------------------------------------*/
int InspectionTask::Run(void)
{
	HANDLE          eventHandle[3];                                         // Event Handle array
	double          timeTaken;                                              // Total time taken for processing
	PreprocessedImageData       _imageData;                                             // Image Data Structure
	double			t1, t2, t3, t4;											// Processing Time Stamps

	int             imageBufSize;
	int             result;                                                 // variable to hold inspection result
	TCHAR           errorMessage[MAX_ERROR_MESSAGE_LENGTH];
	if (modelLoaded)
	{
		LOGINFO(_T("Inspection Task") << inspectionItemID << _T(" Thread started"));
	}
	else
	{
		LOGERROR(_T("Inspection Task") << inspectionItemID << _T(" Thread Exited [Model Not loaded]"));
		return 0;
	}

#ifdef SAVE_IMAGE_TO_HD
	HImage imageBuffer[MAX_IMAGE_BUFFER_SIZE];        // image buffer
	int tempCount = 0;
	int imageNo = 0;
	std::string imageFileName;
#endif


	eventHandle[0] = newImageEvent;                                         // event for new image
	eventHandle[1] = inspectionStopEvent;                                   // event to stop inspection
	eventHandle[2] = pauseInspectionEvent;
	if (inspectionType == inspection_type_LayerInspection || inspectionType == inspection_type_SpecialLayerInspection)
	{

		assitThread = (LayerProcessingAssistThread *)AfxBeginThread(RUNTIME_CLASS(LayerProcessingAssistThread),
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		if (assitThread != NULL)
		{
			assitThread->SetInspectionID(inspectionItemID);
			assitThread->SetStopEvent(assistThreadStopEvent, assistThreadExitEvent);
			assitThread->SetGPUList(*gpuList);
			((LayerInspectionAlgo *)inspectionAlgo)->SetProcessingAssistThread(*assitThread);
			assitThread->ResumeThread();
		}

	}
	

	while (WAIT_OBJECT_0 != WaitForSingleObject(inspectionStopEvent, 0))
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(pauseInspectionEvent, 0))
		{
			SetEvent(inspectionPausedEvent);
			LOGDEBUG(_T("Inspection Thread Paused ") << inspectionItemID);
			WaitForSingleObject(resumeInspectionEvent, INFINITE);
			LOGDEBUG(_T("Inspection Thread Resumed ") << inspectionItemID);
			SetEvent(inspectionResumedEvent);
		}
		else if (WAIT_OBJECT_0 == WaitForMultipleObjects(3, eventHandle,
			FALSE, 1000))
		{

			t1 = HSystem::CountSeconds();
			// pop images from image buffer               
			EnterCriticalSection(&imageMutex);
			if (imgDataList.size() > 0)
			{
				_imageData = imgDataList.front();
				imgDataList.pop_front();
			}
			else
			{
				LeaveCriticalSection(&imageMutex);
				continue;
			}
			LeaveCriticalSection(&imageMutex);
			t2 = HSystem::CountSeconds();
			LOGDEBUG(_T("Processing Started ") << inspectionItemID);
			// reset inspection results variables
			result = (int)Error;
#ifdef SAVE_IMAGE_TO_HD
			if (tempCount < MAX_IMAGE_BUFFER_SIZE)
			{
				imageBuffer[tempCount++] = _imageData.image;        // copy to image buffer
			}
#endif

			// process image as per inspection algo
			resultData = inspectionAlgo->ProcessImage(_imageData, _imageData.originalImageData.imageNumber);
			resultData->imageNumber = _imageData.originalImageData.imageNumber;
			resultData->imageTimeStamp = _imageData.originalImageData.timeStamp;
			resultData->typeOfInspection = inspectionType;
			resultData->taskID = inspectionItemID;

			t3 = HSystem::CountSeconds();
			try
			{
				AddToResultDataList(resultData);
			}
			catch (IPAException *e)
			{
				LOGDEBUG(CString(e->GetErrorMessage().c_str()).GetBuffer());
			}
			catch (HException &exp)
			{
				LOGDEBUG(_T("InspectionTask Exception") << exp.ErrorMessage().Text());
			}
			// push result to result buffer and raise event
			t4 = HSystem::CountSeconds();
			timeTaken = (t4 - t1) * 1000;     // time taken in ms
														  // copy inspection results


#ifdef RESULTS_LOG_NEEDED

			std::string comma = ",";
			std::string mainLog = std::to_string(_imageData.originalImageData.imageNumber) + comma + std::to_string(t1) + comma + std::to_string(t4) + comma + std::to_string(timeTaken) +
				comma + std::to_string((t2 - t1) * 1000) + comma + std::to_string((t3 - t2) * 1000) + comma + std::to_string((t4 - t3) * 1000) + comma + inspectionAlgo->GetTimeLog() +"\n";
			if (resultsLog.size() > MAX_RESULT_LOG_COUNT)
			{
				resultsLog.pop_front();
			}
			resultsLog.push_back(mainLog);

#endif
			LOGDEBUG(_T("Processing Finished ") << inspectionItemID);
			// check if more images are available to process
			EnterCriticalSection(&imageMutex);
			imageBufSize = imgDataList.size();
			LeaveCriticalSection(&imageMutex);
			if (imageBufSize > 0)
			{
				SetEvent(newImageEvent);
			}
			else
			{
				continue;
			}


		}
	}
#if GPU_INSPECTION
	if (inspectionType == inspection_type_LayerInspection || inspectionType == inspection_type_SpecialLayerInspection)
	{
		//inspectionAlgo->CloseGPU();
		//GPUProviderSingleton::GetGPU()->DeActivateGPU();
	}
	//if (inspectionItemID == 1)
	//{
	//	inspectionAlgo->CloseGPU();
	//}
#endif

	if (inspectionType == inspection_type_LayerInspection || inspectionType == inspection_type_SpecialLayerInspection)
	{
		SetEvent(assistThreadStopEvent);
		WaitForSingleObject(assistThreadExitEvent, INFINITE);
	}

#ifdef SAVE_IMAGE_TO_HD
	// save images in buffer to hard disk
	for (register int i = 0; i<tempCount; i++)
	{
		sprintf_s(imageFileName, "./SavedImages/Image%d.bmp", i);
		try
		{
			imageBuffer[i].WriteImage("bmp", 0, imageFileName);
		}
		catch (HException &except)
		{


			LOGERROR(_T("Write image exception ") << except.message);


		}
	}
	CTextGraphics::PrintError(_T("Images Saved!      "));

#endif
#ifdef INSPECTION_DISPLAY_ON
	displayWindow.CloseWindow();
#endif
#ifdef RESULTS_LOG_NEEDED
	std::string fileName;
	fileName = std::string(IPA_LOGS_DIRECTORY) + "\\Online Processing "+ inspectionName + std::to_string(inspectionItemID) + " Results.csv";
	FILE *fpProc = fopen(fileName.c_str(), "w");
	if (fpProc != NULL)
	{

		fprintf(fpProc, "ImageCnt,startTime,FinishTime,Overall Processing Time, Image Acquring Time, Processing Time, Result Publishing time,");
		fprintf(fpProc, inspectionAlgo->GetTimeLogHeader().c_str());
		fprintf(fpProc, "\n");
		for (std::list<std::string>::iterator iter = this->resultsLog.begin(); iter != this->resultsLog.end(); iter++)
		{
			fprintf(fpProc, "%s", (*iter).c_str());
		}
		fclose(fpProc);
	}
	resultsLog.clear();
#endif

#ifdef RESULTS_LOG_NEEDED
	if (fpProc != NULL)
	{
		fclose(fpProc);
	}
#endif
	LOGDEBUG(_T("Inspection Task Thread exited ") << inspectionItemID);
	SetEvent(inspectionExitEvent);
	::PostQuitMessage(0);
	return 1;

}
#pragma endregion

