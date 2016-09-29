#include "stdafx.h"
#include "GrabFromCamera.h"
#include "SiSoInterfaceProvider.h"

IMPLEMENT_DYNCREATE(GrabFromCamera, ImageGrabber)

GrabFromCamera::GrabFromCamera()
{
	char fileName[MAX_PATH_LENGTH];
	sprintf(fileName, "%s\\IA Error Log.txt", IPA_LOGS_DIRECTORY);
	fp = fopen(fileName, "a");
}


GrabFromCamera::~GrabFromCamera()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}



bool GrabFromCamera::SetImageSource(UINT _cameraID, string _configFileLocation)
{
	this->cameraID = _cameraID;
	this->sourceType = ImageSourceType::Camera;
	this->configFileLocation = _configFileLocation;

	if (!sisoImgAcquisition.InitializeBoard(_cameraID, _configFileLocation))
	{
		LOGERROR(_T("Failed to initialize the framegrabber for Camera ID: ") << cameraID);
		LogIAEvents("Failed to initialize the framegrabber for Camera ID: " + std::to_string(cameraID));
		return false;
	}
	if (!sisoImgAcquisition.AllocateMemory())
	{
		LOGERROR(_T("Failed to Allocate memory for Camera: ") << cameraID);
		LogIAEvents("Failed to Allocate memory for Camera: " + std::to_string(cameraID));
		return false;
	}

	if (sisoImgAcquisition.StartAcquisition() != ACQ_START_SUCCESS)
	{
		LOGERROR(_T("Failed to Start Image Acquisition For the Camera") << cameraID);
		LogIAEvents("Failed to Start Image Acquisition For the Camera: " + std::to_string(cameraID));
		return false;
	}

	SiSoInterfaceProvider::GetInstance()->SetSiSoInterface(&sisoImgAcquisition);
	//LOGINFO(_T("CameraID: ") << cameraID << _T(", Configured to grab images from Camera with Config File: ") << configFileLocation.c_str());
	return true;
}

bool GrabFromCamera::RestartGrab()
{
	imageCount = 1;
	LOGINFO(_T("CameraID: ") << cameraID << _T(", Image Count Reset"));
	return true;
}

BOOL GrabFromCamera::InitInstance()
{
	return TRUE;
}

int GrabFromCamera::Run()
{
	ImageData imageData;
	double t1, t2, t3;
	if (!sisoImgAcquisition.EnableGate())
	{
		LOGERROR(_T("Failed to Enable Trigger gate For the Camera ID: ") << cameraID);
		LogIAEvents("Failed to Enable Trigger gate For the Camera ID: " + std::to_string(cameraID));
		if (sisoImgAcquisition.StopAcquisition() != ACQ_STOP_SUCCESS)
		{
			LOGERROR(_T("Failed to Stop Image Acquisition For the Camera ID: ") << cameraID);
			LogIAEvents("Failed to Stop Image Acquisition For the Camera ID: " + std::to_string(cameraID));
		}

		if (!sisoImgAcquisition.DeallocateMemory())
		{
			LOGERROR(_T("Failed to DeAllocate memory for Camera ID: ") << cameraID);
			LogIAEvents("Failed to DeAllocate memory for Camera ID: " + std::to_string(cameraID));
		}

		if (!sisoImgAcquisition.ReleaseBoard())
		{
			LOGERROR(_T("Failed to release the framegrabber for Camera ID: ") << cameraID);
			LogIAEvents("Failed to release the framegrabber for Camera ID: " + std::to_string(cameraID));
		}
		LOGINFO(_T("GrabFromFile Thread Exit"));
		SetEvent(ImageAcqExitEvent);
		::PostQuitMessage(0);               // quit thread safely
		return 1;
	}

	while (WAIT_OBJECT_0 != WaitForSingleObject(IGStopEvent, 0))
	{
		t1 = HSystem::CountSeconds();
		if (sisoImgAcquisition.GrabImage(imageData.image, imageData.irImage, imageCount))
		{
			imageData.cameraID = cameraID;
			imageData.imageNumber = imageCount + imageCountOffset;
			imageData.timeStamp = HSystem::CountSeconds();
			std::list<iImageReceiver*>::iterator iter;
			for (iter = this->imageReceiversList.begin(); iter != this->imageReceiversList.end(); ++iter)
			{
				(*iter)->OnImageReceived(imageData);
			}
			t2 = HSystem::CountSeconds();
			string log = std::to_string(imageCount + imageCountOffset) + "," + std::to_string(imageData.timeStamp) + "," + std::to_string((imageData.timeStamp - t1) * 1000) + "," + std::to_string((t2 - imageData.timeStamp) * 1000);
			
			if (imagesLog.size() > MAX_RESULT_LOG_COUNT)
			{
				imagesLog.pop_front();
			}
			imagesLog.push_back(log);
		}
	}

	if (!sisoImgAcquisition.DisableGate())
	{
		LOGERROR(_T("Failed to Disable Trigger gate For the Camera ID: ") << cameraID);
		LogIAEvents("Failed to Disable Trigger gate For the Camera ID: " + std::to_string(cameraID));
	}

	if (sisoImgAcquisition.StopAcquisition() != ACQ_STOP_SUCCESS)
	{
		LOGERROR(_T("Failed to Stop Image Acquisition For the Camera ID: ") << cameraID);
		LogIAEvents("Failed to Stop Image Acquisition For the Camera ID: " + std::to_string(cameraID));
	}

	if (!sisoImgAcquisition.DeallocateMemory())
	{
		LOGERROR(_T("Failed to DeAllocate memory for Camera ID: ") << cameraID);
		LogIAEvents("Failed to DeAllocate memory for Camera ID: " + std::to_string(cameraID));
	}

	if (!sisoImgAcquisition.ReleaseBoard())
	{
		LOGERROR(_T("Failed to release the framegrabber for Camera ID: ") << cameraID);
		LogIAEvents("Failed to release the framegrabber for Camera ID: " + std::to_string(cameraID));
	}

#ifdef RESULTS_LOG_NEEDED
	FILE            *fp;
	std::string fileName;
	fileName = std::string(IPA_LOGS_DIRECTORY) + "//Image Acqusition " + std::to_string(cameraID) + " Logs.csv";

	fp = fopen(fileName.c_str(), "w");
	if (fp != NULL)
	{
		fprintf(fp, "ImageCount, Image Time Stamp, Grabbing Time, Image Publish Time\n");
		for (std::list<std::string>::iterator iter = this->imagesLog.begin(); iter != this->imagesLog.end(); iter++)
		{
			fprintf(fp, "%s", (*iter).c_str());
		}
		fclose(fp);
	}
	imagesLog.clear();
#endif

	LOGINFO(_T("GrabFromFile Thread Exit"));
	SetEvent(ImageAcqExitEvent);
	::PostQuitMessage(0);               // quit thread safely
	return 1;
}

void GrabFromCamera::LogIAEvents(std::string iaLog)
{
	//char fileName[MAX_PATH_LENGTH];
	//sprintf(fileName, "%s\\Result Collator Log.txt", IPA_LOGS_DIRECTORY);
	//FILE* fp = fopen(fileName, "a");
	if (fp != NULL)
	{
		CTime time = CTime::GetCurrentTime();
		fprintf(fp, "\n%d-%d-%d %d:%d:%d\t\t", time.GetDay(), time.GetMonth(), time.GetYear(), time.GetHour(), time.GetMinute(), time.GetSecond());
		fprintf(fp, "%s", iaLog.c_str());
	}
	//fclose(fp);
}