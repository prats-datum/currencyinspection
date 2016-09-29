#include "stdafx.h"
#include "CameraModelGenerator.h"


IMPLEMENT_DYNCREATE(CameraModelGenerator, CWinThread)

CameraModelGenerator::CameraModelGenerator()
{
	exitEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
	ResetEvent(exitEvent);
	for (register int inspIndex = 0; inspIndex < MAX_NO_OF_INSPECTION_TASKS; inspIndex++)
	{
		allBuiderTaskExitedEvents[inspIndex] = CreateEventW(NULL, TRUE, FALSE, NULL);
		ResetEvent(allBuiderTaskExitedEvents[inspIndex]);
		imageExtensionCompletedEvent[inspIndex] = CreateEventW(NULL, TRUE, FALSE, NULL);
		ResetEvent(imageExtensionCompletedEvent[inspIndex]);
	}
}


CameraModelGenerator::~CameraModelGenerator()
{
}

// initialize model interpretor
int CameraModelGenerator::InitCameraProcessor(CameraData &_camData)
{
	cameraID = _camData.cameraID;
	cameraModelData = &_camData;
	int inspectionTaskIndex = 0;
	for (auto &e : cameraModelData->inspectionTasks)
	{
		modelBuildersList[e.first] = (ModelBuidingTask *)AfxBeginThread(RUNTIME_CLASS(ModelBuidingTask),
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		if (modelBuildersList[e.first] != NULL)
		{
			modelBuildersList[e.first]->SetInspectionModel(e.second->taskID, e.second->typeOfInspectionTask, e.second, &interTaskCommunicator);

			modelBuildersList[e.first]->SetStopEvent(exitEvent, allBuiderTaskExitedEvents[inspectionTaskIndex], imageExtensionCompletedEvent[inspectionTaskIndex]);
			modelBuildersList[e.first]->AddModelBuildingEventReceiver(this);
			modelBuildersList[e.first]->SetGPUList(*gpuList);
		}
		else
		{
			//InspectionThreadException *exc;
			//exc = new InspectionThreadException(e.first, EX1025);
			//exc->SetThreadName(("InspectionTask"));
			//throw exc;
			LOGERROR(_T("Model Buider Task Creation Failed! Task ID: ") << e.first);
		}
		inspectionTaskIndex++;
	}

	return 1;
}
void CameraModelGenerator::OnModelBuidingExceptionReceived(UINT trainingSetNumber, UINT taskID, IPAException *exception)
{
	for (auto &e : modelBuildiingEventReceiverList)
	{
		e->OnModelBuidingExceptionReceived(cameraID, trainingSetNumber, taskID, exception);
	}
}

BOOL CameraModelGenerator::InitInstance()
{
	return TRUE;
}

int CameraModelGenerator::Run()
{
	for (auto &e : modelBuildersList)
	{
		e.second->ResumeThread();
	}
	//gpuList->at(0).InitAndActivateGPU();
	//GPUProviderSingleton::GetGPU()->InitAndActivateGPU();
	//OpenGPU();
	//InitAndActivateGPU();
	for (auto &iter : cameraModelData->thisCameraTrainingSet)
	{
		if (WAIT_OBJECT_0 != WaitForSingleObject(modelBuildCancelEvent, 0))
		{
			if (!iter.isTrained)
			{
			for (register int inspIndex = 0; inspIndex < MAX_NO_OF_INSPECTION_TASKS; inspIndex++)
			{
				ResetEvent(imageExtensionCompletedEvent[inspIndex]);
			}
			PreprocessedTrainingImageData preprocessedTrainingImageData(iter, cameraModelData->InspectionWindow);
			for (auto &e : modelBuildersList)
			{
				e.second->SetImage(preprocessedTrainingImageData);
			}
			if (WAIT_OBJECT_0 != WaitForMultipleObjects(modelBuildersList.size(), imageExtensionCompletedEvent, TRUE, SAFE_EXIT_TIME_DELAY))
			{
				LOGERROR(_T("One of the task failed to Extend the image"));
				IPAException *ex = new InspectionItemException(cameraModelData->GetBlobAnalyzer()->taskID, inspection_type_BlobAnalyser, std::string("Timeout Occured while waiting for layer results"));
				OnModelBuidingExceptionReceived(iter.imgNumber, cameraModelData->GetBlobAnalyzer()->taskID, ex);
				iter.isTrained = false;
			}
			else
			{
				iter.isTrained = true;
				for (auto &e : modelBuildersList)
				{
					iter.isTrained &= e.second->isLastImageTrainedSuccessfully;
				}
			}
			}
			for (auto &e : modelBuildiingEventReceiverList)
			{
				e->OnModelBuidingCompletedForImage(cameraID, iter.imgNumber, iter.isTrained);
			}
		}
		else
		{
			break;
		}
	}
	
	SetEvent(exitEvent);
	Sleep(1000);
	if (WAIT_OBJECT_0 != WaitForMultipleObjects(modelBuildersList.size(), allBuiderTaskExitedEvents, TRUE, SAFE_EXIT_TIME_DELAY))
	{
		//ThreadException *exc;
		//exc = new ThreadException("Inspection Task", EX1027);
		//throw exc;
		LOGERROR(_T("Failed To Terminate all Model Builder Threads"));
	}
	else
	{
		LOGDEBUG(_T("All inspection Tasks thread terminated safely"));
	}
	//for (auto &e : modelBuildersList)
	//{
	//	delete e.second;
	//}
	//gpuList->at(0).DeactivateGPU();

	//GPUProviderSingleton::GetGPU()->DeActivateGPU();
	//CloseGPU();
	modelBuildersList.clear();
	SetEvent(threadExitEvent);
	::PostQuitMessage(0);
	return 1;
}

int CameraModelGenerator::OpenGPU()
{
	GPUProvider::OpenGPU();
	return 1;
}

int CameraModelGenerator::CloseGPU()
{
	GPUProvider::CloseGPU();
	return 1;
}

int CameraModelGenerator::InitAndActivateGPU()
{
	try
	{
		//AfxMessageBox(_T("1"));
		GPUHandle.InitComputeDevice("trans_from_rgb");
		//AfxMessageBox(_T("5"));
		GPUHandle.InitComputeDevice("rgb1_to_gray");
		//AfxMessageBox(_T("6"));
		GPUHandle.InitComputeDevice("crop_domain");
		//AfxMessageBox(_T("7"));
		GPUHandle.InitComputeDevice("reduce_domain");
		//AfxMessageBox(_T("14"));
		GPUHandle.InitComputeDevice("convert_image_type");
		//AfxMessageBox(_T("15"));
		GPUHandle.InitComputeDevice("gray_erosion_rect");
		//AfxMessageBox(_T("16"));
		GPUHandle.InitComputeDevice("gray_dilation_rect");
		//AfxMessageBox(_T("19"));
		GPUHandle.InitComputeDevice("abs_diff_image");
		//AfxMessageBox(_T("20"));
		GPUHandle.InitComputeDevice("decompose3");
		//AfxMessageBox(_T("22"));
		GPUHandle.ActivateComputeDevice();
		return 1;
	}
	catch (HException &e)
	{
		return 0;
	}
	return 1;
}
