#include "stdafx.h"
#include "CameraProcessor.h"
#include "GrabFromFile.h"
#include "GrabFromCamera.h"
#include "ApplicationLogsCollector.h"


CameraProcessor::CameraProcessor()
{
	imageGrabber = NULL;
	exitEventForInspectionTasks = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(exitEventForInspectionTasks);
	exitEventForImageGrabber = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(exitEventForImageGrabber);
	imgGrabberExitedEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(imgGrabberExitedEvent);
	exitEventForResultCollator = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(exitEventForResultCollator);
	resultCollatorExitedEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(resultCollatorExitedEvent);
	exitEventForImagePreprocessor = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(exitEventForImagePreprocessor);
	imagePreprocessorExitedEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(imagePreprocessorExitedEvent);

	pauseEventforInspectionTasks = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(pauseEventforInspectionTasks);
	resumeEventforInspectionTasks = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(resumeEventforInspectionTasks);

	for (register int inspIndex = 0; inspIndex < MAX_NO_OF_INSPECTION_TASKS; inspIndex++)
	{
		allInspectionTaskExitedEvents[inspIndex] = CreateEventW(NULL, TRUE, FALSE, NULL);
		ResetEvent(allInspectionTaskExitedEvents[inspIndex]);
		allInspectionTaskPausedEvents[inspIndex] = CreateEventW(NULL, TRUE, FALSE, NULL);
		ResetEvent(allInspectionTaskPausedEvents[inspIndex]);
		allInspectionTaskResumedEvents[inspIndex] = CreateEventW(NULL, TRUE, FALSE, NULL);
		ResetEvent(allInspectionTaskResumedEvents[inspIndex]);
	}

	camResultCollator = NULL;
	imageGrabber = NULL;
	imagePreprocessor = NULL;
}


CameraProcessor::~CameraProcessor()
{

}



// Start Inspection
int CameraProcessor::StartCameraProcessors(void)
{
	for (auto &e : inspectionTasksList)
	{
		e.second->ResumeThread();
	}
	camResultCollator->ResumeThread();
	imagePreprocessor->ResumeThread();
	imageGrabber->ResumeThread();
	return 1;
}

// Stop Inspection
int CameraProcessor::StopCameraProcessors(void)
{
	SetEvent(exitEventForImageGrabber);
	if (WAIT_OBJECT_0 != WaitForSingleObject(imgGrabberExitedEvent, SAFE_EXIT_TIME_DELAY))
	{
		LOGERROR(_T("Failed to terminate Image Grabber thread"));
	}
	else
	{
		LOGDEBUG(_T("Image Grabber thread terminated safely"));
	}

	SetEvent(exitEventForImagePreprocessor);
	if (WAIT_OBJECT_0 != WaitForSingleObject(imagePreprocessorExitedEvent, SAFE_EXIT_TIME_DELAY))
	{
		LOGERROR(_T("Failed to terminate Image Preprocessor thread"));
	}
	else
	{
		LOGDEBUG(_T("Image Preprocessor thread terminated safely"));
	}


	SetEvent(exitEventForResultCollator);
	if (WAIT_OBJECT_0 != WaitForSingleObject(resultCollatorExitedEvent, SAFE_EXIT_TIME_DELAY))
	{
		LOGERROR(_T("Failed to terminate Result Collator thread"));
	}
	else
	{
		LOGDEBUG(_T("Result Collator thread terminated safely"));
	}


	SetEvent(exitEventForInspectionTasks);
	if (WAIT_OBJECT_0 != WaitForMultipleObjects(inspectionTasksList.size(), allInspectionTaskExitedEvents, TRUE, SAFE_EXIT_TIME_DELAY))
	{
		LOGERROR(_T("Failed to terminate Inspection Task thread"));
	}
	else
	{
		LOGDEBUG(_T("All inspection Tasks thread terminated safely"));
	}


	return 1;
}

// initialize model interpretor
bool CameraProcessor::InitCameraProcessor(CameraData &_cameraData, ULONG _imageNumber)
{
	bool returnValue = true;
	cameraData = _cameraData;
	if (imageGrabber != NULL)
	{
		delete imageGrabber;
	}
	if (imagePreprocessor != NULL)
	{
		delete imagePreprocessor;
	}
	if (camResultCollator != NULL)
	{
		delete camResultCollator;
	}
	for (auto &e : inspectionTasksList)
	{
		delete e.second;
	}
	inspectionTasksList.clear();
	interTaskCommunicator.UnRegisterAllEvents();
	ResetEvent(pauseEventforInspectionTasks);
	ResetEvent(resumeEventforInspectionTasks);
	ResetEvent(exitEventForInspectionTasks);	
	int inspectionTaskIndex = 0;
	for (auto &e : cameraData.inspectionTasks)
	{
		inspectionTasksList[e.first] = (InspectionTask *)AfxBeginThread(RUNTIME_CLASS(InspectionTask),
			THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
		if (inspectionTasksList[e.first] != NULL)
		{
			inspectionTasksList[e.first]->SetInspectionModel(e.second->taskID, e.second->typeOfInspectionTask, e.second, &interTaskCommunicator);
			ResetEvent(allInspectionTaskExitedEvents[inspectionTaskIndex]);
			inspectionTasksList[e.first]->SetStopEvent(exitEventForInspectionTasks, allInspectionTaskExitedEvents[inspectionTaskIndex]);
			ResetEvent(allInspectionTaskPausedEvents[inspectionTaskIndex]);
			ResetEvent(allInspectionTaskResumedEvents[inspectionTaskIndex]);
			inspectionTasksList[e.first]->SetUpdateEvent(pauseEventforInspectionTasks, allInspectionTaskPausedEvents[inspectionTaskIndex], resumeEventforInspectionTasks, allInspectionTaskResumedEvents[inspectionTaskIndex]);
			inspectionTasksList[e.first]->SetGPUList(*gpuList);
		}
		else
		{
			LOGERROR(_T("Failed to create inspection thread for task!! Task ID: ") << e.first);
			ApplicationLogsCollector::GetLogger()->AppendLog("Failed to create inspection thread for task!! Task ID: " + std::to_string(e.first), error);
			returnValue &= false;
		}
		inspectionTaskIndex++;
	}

	ResetEvent(exitEventForResultCollator);
	ResetEvent(resultCollatorExitedEvent);
	camResultCollator = (CameraResultCollator *)AfxBeginThread(RUNTIME_CLASS(CameraResultCollator),
		THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
	if (camResultCollator != NULL)
	{
		camResultCollator->InitCameraResultCollator(cameraData.cameraID);
		camResultCollator->SetStopEvent(exitEventForResultCollator, resultCollatorExitedEvent);
		camResultCollator->SetInspectionTask(&inspectionTasksList);
		camResultCollator->SetInspectionWindow(cameraData.InspectionWindow);
		for (auto &e : cameraResultReceiversList)
		{
			camResultCollator->RegisterForCameraResult(e);
		}
	}
	else
	{
		LOGERROR(_T("Failed to create Camera Result Collator thread!!"));
		ApplicationLogsCollector::GetLogger()->AppendLog("Failed to create Camera Result Collator thread!!", error);
		returnValue &= false;
	}

	ResetEvent(exitEventForImagePreprocessor);
	ResetEvent(imagePreprocessorExitedEvent);
	imagePreprocessor = (ImagePreprocessor*)AfxBeginThread(RUNTIME_CLASS(ImagePreprocessor),
		THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
	if (imagePreprocessor != NULL)
	{
		imagePreprocessor->SetStopEvent(exitEventForImagePreprocessor, imagePreprocessorExitedEvent);
		imagePreprocessor->inspectionWindow = cameraData.InspectionWindow;
		for (auto &e : inspectionTasksList)
		{
			imagePreprocessor->AddImageReceiver(e.second);
		}
		imagePreprocessor->SetGPUList(*gpuList);
	}
	else
	{
		LOGERROR(_T("Failed to create Image Preprocessor thread!!"));
		ApplicationLogsCollector::GetLogger()->AppendLog("Failed to create Image Preprocessor thread!!", error);
		returnValue &= false;
	}

	ResetEvent(exitEventForImageGrabber);
	ResetEvent(imgGrabberExitedEvent);
	imageGrabber = NULL;
	if (ImageSourceSettingsReader::GetReader()->imageSourceSettingsList[_cameraData.cameraID].imageSourceType == ImageSourceType::File)
	{
		imageGrabber = (GrabFromFile*)AfxBeginThread(RUNTIME_CLASS(GrabFromFile),
			THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
		LOGINFO(_T("Camera ") << cameraData.cameraID << _T(" configured to grab from File"));
	}
	else if (ImageSourceSettingsReader::GetReader()->imageSourceSettingsList[_cameraData.cameraID].imageSourceType == ImageSourceType::Camera)
	{
		imageGrabber = (GrabFromCamera*)AfxBeginThread(RUNTIME_CLASS(GrabFromCamera),
			THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
		LOGINFO(_T("Camera ") << cameraData.cameraID << _T(" configured to grab from Camera"));
	}
	if (imageGrabber != NULL)
	{
		imageGrabber->imageCountOffset = _imageNumber;
		returnValue &= imageGrabber->SetImageSource(cameraData.cameraID, ImageSourceSettingsReader::GetReader()->imageSourceSettingsList[_cameraData.cameraID].GetConfiguration() /* "Images/100/" */);
		returnValue &= imageGrabber->SetStopEvent(exitEventForImageGrabber, imgGrabberExitedEvent);
		returnValue &= imageGrabber->AddImageReceiver(imagePreprocessor);
		returnValue &= imageGrabber->AddImageReceiver(camResultCollator);
	}
	else
	{
		LOGERROR(_T("Failed to create Image grabber thread!!"));
		ApplicationLogsCollector::GetLogger()->AppendLog("Failed to create Image grabber thread!!", error);
		returnValue &= false;
	}
	return returnValue;
}


void CameraProcessor::SetCameraResultReceiver(std::vector<iCameraResultReceiver *> _cameraResultReceiversList)
{
	cameraResultReceiversList = _cameraResultReceiversList;
}

bool CameraProcessor::UpdateCameraProcessor(CameraData &_cameraData)
{
	interTaskCommunicator.UnRegisterAllEvents();
	for (auto &e : _cameraData.inspectionTasks)
	{
			inspectionTasksList[e.first]->UpdateInspectionModel(e.second);
	}
	return true;
}

bool CameraProcessor::PauseCameraProcessor()
{
	bool returnValue = true;
	SetEvent(pauseEventforInspectionTasks);
	if (WAIT_OBJECT_0 != WaitForMultipleObjects(inspectionTasksList.size(), allInspectionTaskPausedEvents, TRUE, SAFE_EXIT_TIME_DELAY))
	{
		returnValue = false;
	}
	ResetEvent(pauseEventforInspectionTasks);
	for (register int inspIndex = 0; inspIndex < inspectionTasksList.size(); inspIndex++)
	{
		ResetEvent(allInspectionTaskPausedEvents[inspIndex]);
	}
	return returnValue;
}

bool CameraProcessor::ResumeCameraProcessor()
{
	bool returnValue = true;
	SetEvent(resumeEventforInspectionTasks);
	if (WAIT_OBJECT_0 != WaitForMultipleObjects(inspectionTasksList.size(), allInspectionTaskResumedEvents, TRUE, SAFE_EXIT_TIME_DELAY))
	{
		returnValue = false;
	}
	ResetEvent(resumeEventforInspectionTasks);
	for (register int inspIndex = 0; inspIndex < inspectionTasksList.size(); inspIndex++)
	{
		ResetEvent(allInspectionTaskResumedEvents[inspIndex]);
	}
	return returnValue;
}