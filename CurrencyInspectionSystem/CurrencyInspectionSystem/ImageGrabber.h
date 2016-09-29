#pragma once
#include "afxwin.h"
#include <list>
#include "Globals.h"
#include "Logger.h"


using namespace HalconCpp;

class iImageReceiver
{
public:
	virtual void OnImageReceived(ImageData &imageData)
	{}
};


class ImageGrabber :
	public CWinThread
{
	DECLARE_DYNCREATE(ImageGrabber)
protected:
	int							cameraID;                                   // Camera ID
	std::list<iImageReceiver*>	imageReceiversList;                         // List to hold imageReceivers objects
	HANDLE						IGStopEvent;                                // image grab stop event
	HANDLE						ImageAcqExitEvent;                          // Image acquistion thread exit event
	ImageSourceType				sourceType;
	string						configFileLocation;
	
	HFramegrabber				frameGrabber;
public:
	ImageGrabber();
	~ImageGrabber();
	ULONG	imageCountOffset;
	ULONG	imageCount;
	bool AddImageReceiver(iImageReceiver *imgReceiver);
	bool SetStopEvent(HANDLE &_IGStopEvent, HANDLE &_exitEvent);
#pragma region inline functions
	virtual bool SetImageSource(UINT _cameraID, string _configFileLocation)
	{
		return false;
	}
	virtual bool SetImageSource(UINT _cameraID, std::list<HImage> buffer)
	{
		return false;
	}
	virtual bool RestartGrab()
	{
		return false;
	}
	virtual BOOL InitInstance()
	{
		return 0;
	}
	virtual int Run()
	{
		return 0;
	}
#pragma endregion
};

