#include "stdafx.h"
#include "ImageGrabber.h"


IMPLEMENT_DYNCREATE(ImageGrabber, CWinThread)

ImageGrabber::ImageGrabber()
{
	cameraID = 0;
	imageReceiversList.clear();
}


ImageGrabber::~ImageGrabber()
{
}

bool ImageGrabber::AddImageReceiver(iImageReceiver *imageReceiver)
{
	bool returnType = false;
	if (imageReceiver != NULL)
	{
		imageReceiversList.push_back(imageReceiver);
		returnType = true;
	}
	return returnType;
}

bool ImageGrabber::SetStopEvent(HANDLE &_IGStopEvent, HANDLE &_exitEvent)
{

	if (_IGStopEvent != NULL)
	{
		this->IGStopEvent = _IGStopEvent;
	}
	else
	{
		// ToDo Raise Excption;
		LOGERROR(_T("ERROR: ImageGrabber Stop Event not initilaized correctrly"));
		return false;
	}
	if (_exitEvent != NULL)
	{
		this->ImageAcqExitEvent = _exitEvent;
	}
	else
	{
		// ToDo Raise Excption;
		LOGERROR(_T("ERROR: ImageGrabber Image Exit Event not initilaized correctrly"));
		return false;
	}
	return true;
}



