#include "stdafx.h"
#include "GrabFromFile.h"
#include "ApplicationLogsCollector.h"


IMPLEMENT_DYNCREATE(GrabFromFile, ImageGrabber)

GrabFromFile::GrabFromFile()
{
	imageCount = 1;
}


GrabFromFile::~GrabFromFile()
{
}

bool GrabFromFile::SetImageSource(UINT _cameraID, string _configFileLocation)
{
	bool returnValue = true;
	this->cameraID = _cameraID;
	this->sourceType = ImageSourceType::File;
	this->configFileLocation = _configFileLocation;
	//LOGINFO(_T("CameraID: ") << cameraID << _T(", Configured to grab images from File with Config File: ") << configFileLocation.c_str());
	try
	{
		frameGrabber.OpenFramegrabber("File", 1, 1, 0, 0, 0, 0, "default", -1, "default", -1, "false", configFileLocation.c_str(), "", 1, 2);
	}
	catch (HException &ex)
	{
		if (ex.ErrorCode() == 5200)
		{
			ApplicationLogsCollector::GetLogger()->AppendLog("Failed to grab Images; Images folder is not found", error);
			LOGERROR(_T("Image folder is not found"));
		}
		else if (ex.ErrorCode() == 5304)
		{
			ApplicationLogsCollector::GetLogger()->AppendLog("Failed to grab Images; Images folder is Empty", error);
			LOGERROR(_T("Image folder is Empty"));
		}
		else
		{
			ApplicationLogsCollector::GetLogger()->AppendLog("Failed to grab Images", error);
		}
		returnValue = false;
	}
	return returnValue;
}

bool GrabFromFile::RestartGrab()
{
	imageCount = 1;
	LOGINFO(_T("CameraID: ") << cameraID << _T("Image Count Reset"));
	return true;
}

BOOL GrabFromFile::InitInstance()
{
	return TRUE;
}

int GrabFromFile::Run()
{
	ImageData imageData;

	frameGrabber.GrabImageStart(-1);
	for (int i = 0; i < 5; i++)
	{
		imageData.image = frameGrabber.GrabImageAsync(-1);
		imageData.irImage = imageData.image.Rgb1ToGray();
		imageData.cameraID = cameraID;
		images.push_back(imageData);

	}

	while (WAIT_OBJECT_0 != WaitForSingleObject(IGStopEvent, 0))
	{
		imageData = images[imageCount % 5];
		imageData.imageNumber = imageCountOffset + imageCount++;
		imageData.timeStamp = HSystem::CountSeconds();
		std::list<iImageReceiver*>::iterator iter;
		for (iter = this->imageReceiversList.begin(); iter != this->imageReceiversList.end(); ++iter)
		{
			(*iter)->OnImageReceived(imageData);
		}
		HSystem::WaitSeconds(1);
	}
	LOGINFO(_T("GrabFromFile Thread Exit"));
	SetEvent(ImageAcqExitEvent);
	::PostQuitMessage(0);               // quit thread safely
	return 1;
}