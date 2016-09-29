#pragma once
#include "afxwin.h"
#include "ResultData.h"
#include "MachineCommunicator.h"




class OverallDocResult
{
public:
	bool isDocumentFit;
	ULONG imgNumber;
	double timeOfTriggerArriavlTimeStamp;
	OverallDocResult()
	{

	}
	OverallDocResult(ULONG _imgNumber, double _timeOfTriggerArriavlTimeStamp, bool _isDocumentFit)
	{
		imgNumber = _imgNumber;
		timeOfTriggerArriavlTimeStamp = _timeOfTriggerArriavlTimeStamp;
		isDocumentFit = _isDocumentFit;
	}
	~OverallDocResult()
	{

	}

};

class DocumentResultBuffer
{
	enum BufferType
	{
		Primary = 0,
		Secondary = 1
	};
	std::vector<DocumentResult> primaryDocumentResultList, secondaryDocumentResultList, incompleteDocumentResultList;
	std::vector<DocumentResult> *activeDocumentResultList;
	BufferType activeBufferType;
	CRITICAL_SECTION incompleteDocumentResultListMutex, activeDocumentResultListMutex;
public:
	DocumentResultBuffer();	
	~DocumentResultBuffer();

	CRITICAL_SECTION overallDocumentResultMutex;
	std::vector<OverallDocResult> overAllDocumentResultList;
	void InsertDocumentResultData(ULONG _imgNumber, double _timeOfTriggerArriavlTimeStamp, unsigned short _numberOfCameras);
	void AddCameraResultData(weak_ptr<CameraResultData>_camResultData);
	std::vector<DocumentResult> *GetActiveBuffer();
	void ReleaseLockedMemory();
	void ClearAllMemory();
};


class DocumentResultCollator :
	public CWinThread,
	public iCameraResultReceiver,
	public DIONotificationReceiver
{
	CRITICAL_SECTION CameraResultCriticalSection;
	CRITICAL_SECTION LoggerCriticalSection;
	OperationMode modeOfOperation;

public:
	DocumentResultCollator();
	~DocumentResultCollator();
	DocumentResultBuffer documentResultBuffer;
	ULONG imageNumber;
	ULONG lastResultSentImageNumber;
	int consecutiveNoResultSheetsCount;
	FILE* fp;
	virtual void OnCameraResultReceived(ULONG _imageNumber, weak_ptr<CameraResultData>_camResultData);

	virtual void OnDIONotificationReceived(SignalName dioSignalName);

	void ResetImageCounter();
	void FetchAndSendResult(ULONG _encoderCount);
	void SetModeOfOperation(OperationMode _modeOfOperation);

	void LogDocumentResultCollatorEvents(std::string resultCollatorLog)
	{
		EnterCriticalSection(&LoggerCriticalSection);
		//char fileName[MAX_PATH_LENGTH];
		//sprintf(fileName, "%s\\Result Collator Log.txt", IPA_LOGS_DIRECTORY);
		//FILE* fp = fopen(fileName, "a");
		if (fp != NULL)
		{
			CTime time = CTime::GetCurrentTime();
			fprintf(fp, "\n%d-%d-%d %d:%d:%d\t\t", time.GetDay(), time.GetMonth(), time.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
			fprintf(fp, "%s", resultCollatorLog.c_str());
		}
		//fclose(fp);
		LeaveCriticalSection(&LoggerCriticalSection);
	}

//#define LOG(...) {FILE* fp = fopen(".\\Logs\\MCA Log.txt", "a"); CTime time = CTime::GetCurrentTime(); fprintf(fp,"\n%d-%d-%d %d:%d:%d\t\t", time.GetDay(), time.GetMonth(), time.GetYear(),time.GetHour(), time.GetMinute(), time.GetSecond()); fprintf(fp,__VA_ARGS__); fclose(fp);}
};

