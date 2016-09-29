#include "stdafx.h"
#include "DocumentResultCollator.h"
#include "ApplicationSettingsReader.h"
#include "ApplicationLogsCollector.h"
#include "SiSoInterfaceProvider.h"

DocumentResultBuffer::DocumentResultBuffer()
{
	InitializeCriticalSection(&incompleteDocumentResultListMutex);
	InitializeCriticalSection(&activeDocumentResultListMutex);
	InitializeCriticalSection(&overallDocumentResultMutex);
	activeDocumentResultList = &primaryDocumentResultList;
	activeBufferType = Primary;
}

DocumentResultBuffer::~DocumentResultBuffer()
{
	DeleteCriticalSection(&incompleteDocumentResultListMutex);
	DeleteCriticalSection(&activeDocumentResultListMutex);
	DeleteCriticalSection(&overallDocumentResultMutex);
	primaryDocumentResultList.clear();
	secondaryDocumentResultList.clear();
}

void DocumentResultBuffer::InsertDocumentResultData(ULONG _imgNumber, double _timeOfTriggerArriavlTimeStamp, unsigned short _numberOfCameras)
{
	DocumentResult tempDocumentResult(_imgNumber, _timeOfTriggerArriavlTimeStamp, _numberOfCameras);
	EnterCriticalSection(&incompleteDocumentResultListMutex);
	incompleteDocumentResultList.push_back(tempDocumentResult);
	LeaveCriticalSection(&incompleteDocumentResultListMutex);

}

void DocumentResultBuffer::AddCameraResultData(weak_ptr<CameraResultData>w_camResultData)
{
	EnterCriticalSection(&incompleteDocumentResultListMutex);
	int index = 0;
	shared_ptr<CameraResultData> _camResultData;
	if (!w_camResultData.expired())
		_camResultData = w_camResultData.lock();
	for (auto &e : incompleteDocumentResultList)
	{
		if (e.imgNumber == _camResultData->imageNumber)
		{
			e.AddCameraResult(_camResultData);
			if (e.IsDocumentResultCompleted())
			{
				EnterCriticalSection(&activeDocumentResultListMutex);
				OverallDocResult newDocumentResult(e.imgNumber, e.timeOfTriggerArriavlTimeStamp, e.overallDocResult == Pass);
				EnterCriticalSection(&overallDocumentResultMutex);
				overAllDocumentResultList.push_back(newDocumentResult);
				LeaveCriticalSection(&overallDocumentResultMutex);
				activeDocumentResultList->push_back(e);
				while (activeDocumentResultList->size() > MAX_DOCUMENT_RESULTS_COUNT)
				{
					activeDocumentResultList->front().ClearMemory();
					activeDocumentResultList->erase(activeDocumentResultList->begin());
				}
				LeaveCriticalSection(&activeDocumentResultListMutex);
				incompleteDocumentResultList.erase(incompleteDocumentResultList.begin() + index);
			}
			break;
		}
		index++;
	}
	LeaveCriticalSection(&incompleteDocumentResultListMutex);
}

std::vector<DocumentResult> *DocumentResultBuffer::GetActiveBuffer()
{
	EnterCriticalSection(&activeDocumentResultListMutex);
	std::vector<DocumentResult> *returnValue = activeDocumentResultList;
	if (activeBufferType == Primary)
	{
		activeDocumentResultList = &secondaryDocumentResultList;
		activeBufferType = Secondary;
	}
	else
	{
		activeDocumentResultList = &primaryDocumentResultList;
		activeBufferType = Primary;
	}
	LeaveCriticalSection(&activeDocumentResultListMutex);
	return returnValue;
}

void DocumentResultBuffer::ReleaseLockedMemory()
{
	EnterCriticalSection(&activeDocumentResultListMutex);
	std::vector<DocumentResult> *tempValue = (activeBufferType == Secondary) ? &primaryDocumentResultList : &secondaryDocumentResultList;
	for (auto &e : *tempValue)
	{
		e.ClearMemory();
	}
	tempValue->clear();
	LeaveCriticalSection(&activeDocumentResultListMutex);
}

void DocumentResultBuffer::ClearAllMemory()
{
	EnterCriticalSection(&activeDocumentResultListMutex);
	for (auto &e : primaryDocumentResultList)
	{
		e.ClearMemory();
	}
	primaryDocumentResultList.clear();
	for (auto &e : secondaryDocumentResultList)
	{
		e.ClearMemory();
	}
	secondaryDocumentResultList.clear();
	overAllDocumentResultList.clear();
	LeaveCriticalSection(&activeDocumentResultListMutex);
}

DocumentResultCollator::DocumentResultCollator()
{
	InitializeCriticalSection(&CameraResultCriticalSection);
	InitializeCriticalSection(&LoggerCriticalSection);

#ifdef DIOENABLED
	MachineCommunicator::GetInstance()->AddEjectorSignalListener(this);
	MachineCommunicator::GetInstance()->AddImageTriggerListener(this);
	MachineCommunicator::GetInstance()->AddMachineStateStatusChangeListener(this);
	MachineCommunicator::GetInstance()->AddStartInspectionStatusChangeListener(this);
#endif
	imageNumber = 1;
	lastResultSentImageNumber = 0;
	char fileName[MAX_PATH_LENGTH];
	sprintf(fileName, "%s\\Result Collator Log.txt", IPA_LOGS_DIRECTORY);
	fp = fopen(fileName, "a");
}

DocumentResultCollator::~DocumentResultCollator()
{
	DeleteCriticalSection(&CameraResultCriticalSection);
	DeleteCriticalSection(&LoggerCriticalSection);
	if (fp != NULL)
	{
		fclose(fp);
	}
}

void DocumentResultCollator::OnCameraResultReceived(ULONG _imageNumber, weak_ptr<CameraResultData>_camResultData)
{
	EnterCriticalSection(&CameraResultCriticalSection);
	documentResultBuffer.InsertDocumentResultData(_imageNumber, 0.0, 1);
	if(!_camResultData.expired())
		documentResultBuffer.AddCameraResultData(_camResultData);
	LeaveCriticalSection(&CameraResultCriticalSection);
}


void DocumentResultCollator::ResetImageCounter()
{
	imageNumber = 1;
	lastResultSentImageNumber = 0;
}

void DocumentResultCollator::OnDIONotificationReceived(SignalName dioSignalName)
{
	bool machineState = false;
	bool inspectionState = false;
	double encoderCount = 0.0;
	std::string log;
	switch (dioSignalName)
	{
	case DebouncedImageTrigger:
#ifdef DIOENABLED
		encoderCount = MachineCommunicator::GetInstance()->GetEncoderCount();
#endif
		if (modeOfOperation == OperationMode::InspectionMode)
		{
			documentResultBuffer.InsertDocumentResultData(imageNumber, encoderCount, 1);
		}
		LOGDEBUG(_T("Image Trigger Received! Image Number: ") << imageNumber <<_T(". Encoder Count: ") << encoderCount);
		log = "Image Trigger Received! Image Number: " + std::to_string(imageNumber) + ". Encoder Count: " + std::to_string(encoderCount);
		LogDocumentResultCollatorEvents(log);
		imageNumber++;
		break;
	case MachineStateSignal:
#ifdef DIOENABLED
		machineState = MachineCommunicator::GetInstance()->GetMachineState();
#endif
		LOGDEBUG(_T("Machine State Changed! State: ") << machineState);
		ApplicationLogsCollector::GetLogger()->AppendLog("Machine State Changed! State: " + std::to_string(machineState), Severity::info);
		break;
	case StartInspectionSignal:
#ifdef DIOENABLED
		inspectionState = MachineCommunicator::GetInstance()->GetStartInspectionSignalState();
#endif
		LOGDEBUG(_T("Start Inspection Signal State Changed! State: ") << inspectionState);
		ApplicationLogsCollector::GetLogger()->AppendLog("Start Inspection Signal State Changed! State: " + std::to_string(inspectionState), Severity::info);

#ifdef DIOENABLED
		MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(inspectionState);
		MachineCommunicator::GetInstance()->SetTowerLampRedSignal(false);
		MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(!inspectionState);
#endif
		break;
	case EjectorSensorEvent:
#ifdef DIOENABLED
		encoderCount = MachineCommunicator::GetInstance()->GetEncoderCount();
#endif
		if (modeOfOperation == OperationMode::InspectionMode)
		{
			FetchAndSendResult(encoderCount);
		}
		if (SiSoInterfaceProvider::GetInstance()->sisoInterface != NULL)
		{
			SiSoInterfaceProvider::GetInstance()->sisoInterface->SnoozeWatchDog();
		}
		log = "Ejector Trigger Received! Image Number: " + std::to_string(lastResultSentImageNumber) + ". Encoder Count: " + std::to_string(encoderCount);
		LogDocumentResultCollatorEvents(log);
		break;
	default:
		break;
	}
}


void DocumentResultCollator::FetchAndSendResult(ULONG _encoderCount)
{
	ULONG currentEjectorSheetImageNumber = lastResultSentImageNumber + 1;
	double currentEncoderCount = 0.0;
#ifdef DIOENABLED
	currentEncoderCount = _encoderCount;
#endif

	EnterCriticalSection(&documentResultBuffer.overallDocumentResultMutex);
	bool isResultSent = false;
	for (auto &e : documentResultBuffer.overAllDocumentResultList)
	{
		if (e.imgNumber < currentEjectorSheetImageNumber)
		{
			documentResultBuffer.overAllDocumentResultList.erase(documentResultBuffer.overAllDocumentResultList.begin());
			continue;
		}
		else if (e.imgNumber > currentEjectorSheetImageNumber)
		{
			LOGERROR(_T("Documnet Result is missing! Image Number: ") << currentEjectorSheetImageNumber);
			LogDocumentResultCollatorEvents("Documnet Result is missing! Image Number: : " + std::to_string(currentEjectorSheetImageNumber) + ". Sending To Reject Pile");
			ApplicationLogsCollector::GetLogger()->AppendLog("Documnet Result is missing! Image Number: : " + std::to_string(currentEjectorSheetImageNumber) + ". Sending To Reject Pile", Severity::warning);
#ifdef DIOENABLED
			MachineCommunicator::GetInstance()->SetInspectionResultSignal(false);
			MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(false);
			MachineCommunicator::GetInstance()->SetTowerLampRedSignal(true);
			MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(false);
#endif
		}
		else
		{
			double docLifeTime = currentEncoderCount - e.timeOfTriggerArriavlTimeStamp;
			if(docLifeTime > ApplicationSettingsReader::GetInstance()->sheetMinimumLifetime && docLifeTime < ApplicationSettingsReader::GetInstance()->sheetMaximumLifeTime)
			{
#ifdef DIOENABLED
				MachineCommunicator::GetInstance()->SetInspectionResultSignal(e.isDocumentFit);
				MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(false);
				MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(e.isDocumentFit);
				MachineCommunicator::GetInstance()->SetTowerLampRedSignal(!e.isDocumentFit);
				Sleep(50);
				MachineCommunicator::GetInstance()->SetInspectionResultSignal(false);
#endif
				consecutiveNoResultSheetsCount = 0;
				LOGDEBUG(_T("Result Sent For Sheet : ") << currentEjectorSheetImageNumber << _T(". Result ") << e.isDocumentFit);
				LogDocumentResultCollatorEvents("Result Sent For Sheet! Image Number: " + std::to_string(currentEjectorSheetImageNumber) + ". Result: " + std::to_string(e.isDocumentFit));
				documentResultBuffer.overAllDocumentResultList.erase(documentResultBuffer.overAllDocumentResultList.begin());
			}
			else
			{
				LOGERROR(_T("Sheet Life Time is out of Range! Life Time: ") << docLifeTime << _T(". Image Number: ") << currentEjectorSheetImageNumber  << _T(". Possible MisSync Event"));
				LogDocumentResultCollatorEvents("Sheet Life Time is out of Range! Life Time: " + std::to_string(docLifeTime) + ". Image Number: " + std::to_string(currentEjectorSheetImageNumber) + ". Possible MisSync Event");
				ApplicationLogsCollector::GetLogger()->AppendLog("Sheet Life Time is out of Range! Life Time: " + std::to_string(docLifeTime) + ". Image Number: " + std::to_string(currentEjectorSheetImageNumber) + ". Possible MisSync Event", Severity::error);

#ifdef DIOENABLED
				MachineCommunicator::GetInstance()->SetInspectionResultSignal(false);
				MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(false);
				MachineCommunicator::GetInstance()->SetTowerLampRedSignal(true);
				MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(false);
				MachineCommunicator::GetInstance()->SetSystemAbnormalSignal(true);
				MachineCommunicator::GetInstance()->SetInspectionAvailableSignal(false);
#endif
			}
		}
		bool isResultSent = true;
		break;
	}
	LeaveCriticalSection(&documentResultBuffer.overallDocumentResultMutex);
	if (!isResultSent)
	{
		 
		LOGERROR(_T("No Result is available for the sheet! Image Number: ") << currentEjectorSheetImageNumber);

		LogDocumentResultCollatorEvents("No Result is available for the sheet! Image Number: " + std::to_string(currentEjectorSheetImageNumber));
		ApplicationLogsCollector::GetLogger()->AppendLog("No Result is available for the sheet! Image Number: " + std::to_string(currentEjectorSheetImageNumber), Severity::warning);

		consecutiveNoResultSheetsCount++;

#ifdef DIOENABLED
		MachineCommunicator::GetInstance()->SetInspectionResultSignal(false);
		MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(false);
		MachineCommunicator::GetInstance()->SetTowerLampRedSignal(true);
		MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(false);
#endif
		if (consecutiveNoResultSheetsCount >= ApplicationSettingsReader::GetInstance()->maxAllowedConsecutiveNoResultsAvailableEvents)
		{

#ifdef DIOENABLED
			MachineCommunicator::GetInstance()->SetSystemAbnormalSignal(true);
			MachineCommunicator::GetInstance()->SetInspectionAvailableSignal(false);
#endif
			LOGERROR(_T("Maximum Allowed Consecutive No Result Available Event Reached!! Stopping Inspection"));
			LogDocumentResultCollatorEvents("Maximum Allowed Consecutive No Result Available Event Reached");
			ApplicationLogsCollector::GetLogger()->AppendLog("Maximum Allowed Consecutive No Result Available Event Reached", Severity::error);
		}
	}
	lastResultSentImageNumber = currentEjectorSheetImageNumber;
}


void DocumentResultCollator::SetModeOfOperation(OperationMode _modeOfOperation)
{
	modeOfOperation = _modeOfOperation;
}
