#pragma once
#include "Globals.h"

class ApplicationLogsCollector
{
	CRITICAL_SECTION logsCriticalSection;
	CWnd *logsViewer;
	static ApplicationLogsCollector *thisInstance;
	std::string GetSeverityString(Severity severity);
public:
	ApplicationLogsCollector();
	~ApplicationLogsCollector();
	void AppendLog(std::string logMessage, Severity severity);
	void SetMachineState(bool _state);
	void SetPrintingState(bool _state);
	static ApplicationLogsCollector *GetLogger();
	void SetLogViewer(CWnd *_logViewer);
};

