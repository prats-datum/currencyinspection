#include "stdafx.h"
#include "GoldenProcessor.h"


GoldenProcessor::GoldenProcessor()
{
	goldenData = NULL;
}


GoldenProcessor::~GoldenProcessor()
{
	if (goldenData != NULL)
	{
		delete goldenData;
	}
	for (auto &e : cameraProcessorsList)
	{
		delete e.second;
	}
	cameraProcessorsList.clear();
}

// Start Inspection
int GoldenProcessor::StartCameraProcessors(void)
{
	for (auto &e : cameraProcessorsList)
	{
		e.second->StartCameraProcessors();
	}
	return 1;
}

// Stop Inspection
int GoldenProcessor::StopCameraProcessors(void)
{
	for (auto &e : cameraProcessorsList)
	{
		e.second->StopCameraProcessors();
	}
	//docResultCollator.documentResultBuffer.ClearAllMemory();
	delete goldenData;
	goldenData = NULL;
	return 1;

}

// initialize model interpretor
bool GoldenProcessor::InitGoldenProcessor(std::string _modelLocation, std::map<UINT, iCameraResultReceiver *> camResultReceiversList, iStatusUpdateReceiver *_statusUpdateReceiver,ULONG _imageNumber)
{
	bool returnValue = true;
	_statusUpdateReceiver->UpdateStatus("Clearing old Golden details..", false);
	if (goldenData != NULL)
	{
		delete goldenData;
	}
	for (auto &e : cameraProcessorsList)
	{
		delete e.second;
	}
	cameraProcessorsList.clear();
	_statusUpdateReceiver->UpdateStatus("Old Golden details cleared successfully!", false);	
	_statusUpdateReceiver->UpdateStatus("Copying the selected Golden details..", false);
	// Read Model and share it with camera
	goldenData = new GoldenData();
	goldenData->ReadConfiguration(_modelLocation, false);
	_statusUpdateReceiver->UpdateStatus("Selected Golden details copied successfully!", false);

	_statusUpdateReceiver->UpdateStatus("Starting Inspection threads..", false);
	for (auto &e : goldenData->allCameraData)
	{
		cameraProcessorsList[e.first] = new CameraProcessor();
		std::vector<iCameraResultReceiver *> resultReceiversListForCamera;
		if (camResultReceiversList[e.first] != NULL)
		{
			resultReceiversListForCamera.push_back(camResultReceiversList[e.first]);
		}
		resultReceiversListForCamera.push_back(&docResultCollator);
		//Add Reject Image Viewer & DocumentResult Collator
		cameraProcessorsList[e.first]->SetCameraResultReceiver(resultReceiversListForCamera);
		cameraProcessorsList[e.first]->SetGPUList(*gpuList);
		returnValue &= cameraProcessorsList[e.first]->InitCameraProcessor(e.second,_imageNumber);
	}
	_statusUpdateReceiver->UpdateStatus("Inspection threads started successfully!", false);
	docResultCollator.ResetImageCounter();
	return returnValue;
}



bool GoldenProcessor::UpdateGoldenData(std::string _modelLocation, iStatusUpdateReceiver *_statusUpdateReceiver, int _imageNumber)
{
	// Copying golden details
	_statusUpdateReceiver->UpdateStatus("Copying the Golden updates..", false);
	GoldenData *tempGoldenData = new GoldenData();
	tempGoldenData->ReadConfiguration(_modelLocation, false);
	_statusUpdateReceiver->UpdateStatus("Golden updates copied successfully!", false);
	
	// Pausing the inspection threads
	bool isAllInpectionThreadsPaused = true;
	_statusUpdateReceiver->UpdateStatus("Pausing all Inspection Threads..", false);
	for (auto &e : cameraProcessorsList)
	{
		isAllInpectionThreadsPaused &= e.second->PauseCameraProcessor();
	}
	if(!isAllInpectionThreadsPaused)
	{
		_statusUpdateReceiver->UpdateStatus("Pausing all Inspection Threads failed!!", true);
		for (auto &e : cameraProcessorsList)
		{
			e.second->ResumeCameraProcessor();
		}
		delete tempGoldenData;
		_statusUpdateReceiver->UpdateStatus(("Updating Golden to Live Inspection failed!!"), true);
		return false;
	}
	_statusUpdateReceiver->UpdateStatus("All Inspection Threads paused successfully!", false);

	// Updating Golden Details 
	if (goldenData != NULL)
	{
		delete goldenData;
	}
	goldenData = tempGoldenData;

	_statusUpdateReceiver->UpdateStatus("Updating all Inspection Threads..", false);
	for (auto &e : cameraProcessorsList)
	{
		e.second->UpdateCameraProcessor(goldenData->allCameraData[e.first]);
	}
	_statusUpdateReceiver->UpdateStatus("All Inspection Threads updated successfully!", false);
	
	// Resuming the inspection threads 
	bool isAllInpectionThreadsResumed = true;
	_statusUpdateReceiver->UpdateStatus("Resuming all Inspection Threads..", false);
	for (auto &e : cameraProcessorsList)
	{
		isAllInpectionThreadsResumed &= e.second->ResumeCameraProcessor();
	}
	if (!isAllInpectionThreadsResumed)
	{
		_statusUpdateReceiver->UpdateStatus("Resuming all Inspection Threads failed!", true);
		// here restart the inspection
		_statusUpdateReceiver->UpdateStatus("Trying to recreate inspection threads..", true);
		std::map<UINT, iCameraResultReceiver *> tempList;
		StopCameraProcessors();
		InitGoldenProcessor(_modelLocation, tempList, _statusUpdateReceiver, _imageNumber);
		StartCameraProcessors();
		_statusUpdateReceiver->UpdateStatus("Recreated the inspection threads..", false);
		return true;
	}
	_statusUpdateReceiver->UpdateStatus("All Inspection Threads resumed successfully!", false);
	_statusUpdateReceiver->UpdateStatus(("Updating Golden to Live Inspection succeeded!"), false);
	return true;
}


std::vector<DocumentResult> *GoldenProcessor::GetActiveResultBuffer()
{
	docResultCollator.documentResultBuffer.ReleaseLockedMemory();
	return docResultCollator.documentResultBuffer.GetActiveBuffer();
}


void GoldenProcessor::SetModeOfOperation(OperationMode _operationMode)
{
	docResultCollator.SetModeOfOperation(_operationMode);
}
