#include "stdafx.h"
#include "GoldenGenerator.h"


GoldenGenerator::GoldenGenerator()
{
	goldenData = NULL;
	imgGrabberStopEvent = CreateEventW(NULL, true, FALSE, NULL);
	ResetEvent(imgGrabberStopEvent);
	for (int index = 0; index < MAX_NUM_OF_CAMERAS; index++)
	{
		imgGrabberExitEvent[index] = CreateEventW(NULL, true, FALSE, NULL);
		cameraModelBuilderExitEvent[index] = CreateEventW(NULL, true, FALSE, NULL);

	}
	buildStopEvent = CreateEventW(NULL, true, FALSE, NULL);
	ResetEvent(buildStopEvent);
	trainingSetStausReceiver = NULL;
}

GoldenGenerator::~GoldenGenerator()
{
}

bool GoldenGenerator::GrabTrainingSet(int _cameraID, ImageSourceType _sourceType, std::string _configFileName, int _imageCount, iImageReceiver *_receiver)
{
	bool returnValue = true;
	ResetEvent(imgGrabberStopEvent);
	ResetEvent(imgGrabberExitEvent[_cameraID - 1]);
	imagesToGrab[_cameraID - 1] = _imageCount;
	CString log;
	imgGrabber[_cameraID - 1] = NULL;
	if (_sourceType == ImageSourceType::File)
	{
		imgGrabber[_cameraID - 1] = (GrabFromFile*)AfxBeginThread(RUNTIME_CLASS(GrabFromFile),
			THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
		log.Format(_T("Camera%d: configured to grab from File"), _cameraID);

	}
	else if (_sourceType == ImageSourceType::Camera)
	{
		imgGrabber[_cameraID - 1] = (GrabFromCamera*)AfxBeginThread(RUNTIME_CLASS(GrabFromCamera),
			THREAD_PRIORITY_TIME_CRITICAL, 0, CREATE_SUSPENDED);
		log.Format(_T("Camera%d: configured to grab from camera"), _cameraID);
	}

	if (imgGrabber[_cameraID - 1] != NULL)
	{
		returnValue &= imgGrabber[_cameraID - 1]->SetImageSource(_cameraID, _configFileName);
		returnValue &= imgGrabber[_cameraID - 1]->SetStopEvent(imgGrabberStopEvent, imgGrabberExitEvent[_cameraID - 1]);
		returnValue &= imgGrabber[_cameraID - 1]->AddImageReceiver(this);
		returnValue &= imgGrabber[_cameraID - 1]->AddImageReceiver(_receiver);
		if (returnValue)
		{
			imgGrabber[_cameraID - 1]->ResumeThread();
		}
		LOGINFO(log);
	}
	else
	{
		returnValue = false;
		LOGERROR(_T("Failed to Configure Image Grabber"));
	}
	return returnValue;
}
void GoldenGenerator::StopGrabbingTrainingSet(int _cameraID)
{
	if (imgGrabber[_cameraID - 1] != NULL)
	{
		SetEvent(imgGrabberStopEvent);
		CString log;
		if (WAIT_OBJECT_0 != WaitForSingleObject(imgGrabberExitEvent[_cameraID - 1], SAFE_EXIT_TIME_DELAY))
		{
			log.Format(_T("Camera%d: Image Acquistion thread not terminated!!"), _cameraID);
			LOGERROR(log);
		}
		else
		{
			log.Format(_T("Camera%d: Image Acquistion thread terminated safely"), _cameraID);
			LOGINFO(log);
		}
	}
}

void GoldenGenerator::OnImageReceived(ImageData &_imageData)
{
	if (goldenData != NULL)
	{
		goldenData->AddTrainingSet(_imageData.cameraID, _imageData, BasicTrainingSet);
	}
	if (_imageData.imageNumber >= imagesToGrab[_imageData.cameraID - 1])
	{
		StopGrabbingTrainingSet(_imageData.cameraID);
	}
}


void GoldenGenerator::SetMasterSet(int _cameraID, HImage &_masterImage, HImage &_irMasterImage)
{
	if (goldenData != NULL)
	{
		goldenData->SetMaster(_cameraID, _masterImage, _irMasterImage);
	}
}


void GoldenGenerator::OnModelBuidingExceptionReceived(UINT cameraID, UINT trainingSetNumber, UINT taskID, IPAException *exception)
{
	if (trainingSetStausReceiver != NULL)
	{
		char *errorMessage = new char[500];
		//sprintf_s(errorMessage, 500, "Error: Camera ID : %d; Task Name: %S; Message: %S", cameraID, goldenData->allCameraData[cameraID].inspectionTasks[taskID]->taskName.c_str(), exception->errorMessage);
		//sprintf(errorMessage, "Error: Camera ID : %d; Task Name: %s; Message: %s", cameraID, goldenData->allCameraData[cameraID].inspectionTasks[taskID]->taskName.c_str(), exception->errorMessage.c_str());
		sprintf(errorMessage, "Task Name: %s; Message: %s", goldenData->allCameraData[cameraID].inspectionTasks[taskID]->taskName.c_str(), exception->errorMessage.c_str());
		delete exception;
		trainingSetStausReceiver->OnTrainingSetExceptionReceived(trainingSetNumber, errorMessage);
	}
}

void GoldenGenerator::OnModelBuidingCompletedForImage(UINT cameraID, UINT trainingSetNumber, bool isSuccessfull)
{
	if (trainingSetStausReceiver != NULL)
	{
		trainingSetStausReceiver->OnTrainingSetBuildStaus(trainingSetNumber, isSuccessfull);
	}
}


void GoldenGenerator::OnExtendedTrainingSetReceived(UINT cameraID, TrainingImageData _trainingSetData)
{
	if (goldenData != NULL)
	{
		goldenData->AddTrainingSet(cameraID, _trainingSetData);
	}
}

void GoldenGenerator::SetTrainingSetStausReceiver(iTrainingSetStatusReceiver  *_trainingSetStatusReceiver)
{
	trainingSetStausReceiver = _trainingSetStatusReceiver;
}

void GoldenGenerator::ExtendGolden()
{
	ResetEvent(buildStopEvent);

	for (auto &e : goldenData->allCameraData)
	{
		cameraModelGeneratorList[e.first] = (CameraModelGenerator *)AfxBeginThread(RUNTIME_CLASS(CameraModelGenerator),
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		if (cameraModelGeneratorList[e.first] != NULL)
		{
			ResetEvent(cameraModelBuilderExitEvent[e.first - 1]);
			cameraModelGeneratorList[e.first]->SetEvents(buildStopEvent, cameraModelBuilderExitEvent[e.first - 1]);
			cameraModelGeneratorList[e.first]->SetGPUList(*gpuList);
			cameraModelGeneratorList[e.first]->InitCameraProcessor(e.second);
			cameraModelGeneratorList[e.first]->AddModelBuildingExceptionReceiver(this);
		}
		else
		{
			//InspectionThreadException *exc;
			//exc = new InspectionThreadException(e.first, EX1025);
			//exc->SetThreadName(("InspectionTask"));
			//throw exc;
			LOGERROR(_T("Failed to create Camera Model Generator Thread!! Camera ID: ") << e.first);
		}
	}
	for (auto &e : goldenData->allCameraData)
	{
		if (cameraModelGeneratorList[e.first] != NULL)
		{
			cameraModelGeneratorList[e.first]->ResumeThread();
		}
	}

}


bool GoldenGenerator::EndGoldenExtension()
{
	bool returnValue = false;
	SetEvent(buildStopEvent);
	if (WAIT_OBJECT_0 == WaitForMultipleObjects(cameraModelGeneratorList.size(), cameraModelBuilderExitEvent, TRUE, SAFE_EXIT_TIME_DELAY))
	{
		LOGDEBUG(_T("All Camera Generator thread terminated safely"));
		returnValue = true;
	}
	//for (auto &e : cameraModelGeneratorList)
	//{
	//	delete e.second;
	//}
	cameraModelGeneratorList.clear();
	return returnValue;
}