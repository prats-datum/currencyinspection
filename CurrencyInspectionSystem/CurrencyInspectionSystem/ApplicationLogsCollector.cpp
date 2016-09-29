#include "stdafx.h"
#include "ApplicationLogsCollector.h"


ApplicationLogsCollector::ApplicationLogsCollector()
{
	InitializeCriticalSection(&logsCriticalSection);
}


ApplicationLogsCollector::~ApplicationLogsCollector()
{
	DeleteCriticalSection(&logsCriticalSection);
}
ApplicationLogsCollector * ApplicationLogsCollector::thisInstance = NULL;

void ApplicationLogsCollector::AppendLog(std::string logMessage, Severity severity)
{
	EnterCriticalSection(&logsCriticalSection);
	char *log = new char[500];
	sprintf(log, "%s: %s", GetSeverityString(severity).c_str(), logMessage.c_str());
	if (logsViewer != NULL)
	{
		logsViewer->PostMessageW(UWM_LOG_MESSAGE, (WPARAM)log, severity);
	}
	LeaveCriticalSection(&logsCriticalSection);
}

void ApplicationLogsCollector::SetMachineState(bool _state)
{
	EnterCriticalSection(&logsCriticalSection);
	if (logsViewer != NULL)
	{
		logsViewer->PostMessageW(UWM_MACHINE_STATE_CHANGED, (WPARAM)_state, NULL);
	}
	LeaveCriticalSection(&logsCriticalSection);
}

void ApplicationLogsCollector::SetPrintingState(bool _state)
{
	EnterCriticalSection(&logsCriticalSection);
	if (logsViewer != NULL)
	{
		logsViewer->PostMessageW(UWM_PRINTING_STATE_CHANGED, (WPARAM)_state, NULL);
	}
	LeaveCriticalSection(&logsCriticalSection);
}

ApplicationLogsCollector *ApplicationLogsCollector::GetLogger()
{
	if (thisInstance == NULL)
	{
		thisInstance = new ApplicationLogsCollector();
	}
	return thisInstance;
}


void ApplicationLogsCollector::SetLogViewer(CWnd *_logViewer)
{
	logsViewer = _logViewer;
}


std::string ApplicationLogsCollector::GetSeverityString(Severity severity)
{
	std::string severityString;
	switch (severity)
	{
	case none:
		severityString = "";
		break;
	case info:
		severityString = "Info";
		break;
	case warning:
		severityString = "Warning";
		break;
	case error:
		severityString = "Error";
		break;
	default:
		severityString = "";
		break;
	}
	return severityString;
}