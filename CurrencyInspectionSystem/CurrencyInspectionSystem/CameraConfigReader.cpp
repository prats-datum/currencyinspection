#include "stdafx.h"
#include "CameraConfigReader.h"


CameraConfigReader::CameraConfigReader()
{
}


CameraConfigReader::~CameraConfigReader()
{
}


char* CameraConfigReader::CONFIG_NAME = "Camera Config.ini";
char* CameraConfigReader::APP_NAME = "CameraConfig";
char* CameraConfigReader::NUMBER_OF_CAMERAS = "NumberOfCameras";
char* CameraConfigReader::CAMERA = "Camera";
char* CameraConfigReader::CAMERA_NAME = "CameraName";
char* CameraConfigReader::CAMERA_ID = "CameraID";
char* CameraConfigReader::CAMERA_TYPE = "CameraType";
char* CameraConfigReader::FG_INDEX = "FramegrabberIndex";
char* CameraConfigReader::DMA_INDEX = "DMAIndex";
char* CameraConfigReader::BYTES_PER_PIXEL = "BytesPerPixal";
char* CameraConfigReader::IMAGE_WIDTH = "ImageWidth";
char* CameraConfigReader::IMAGE_HEIGHT = "ImageHeight";
char* CameraConfigReader::BUFFER_COUNT = "BufferCount";
char* CameraConfigReader::ALLOWED_BUFFERED_IMAGE_COUNT = "AllowedBufferedImageCount";
char* CameraConfigReader::TIME_OUT = "Timeout";
char* CameraConfigReader::NUMBER_OF_LIGHT_STICKS = "NumberOfLightSticks";
char* CameraConfigReader::NUMBER_OF_FFC_GAINS = "NumberOfFFCGains";
char* CameraConfigReader::FFC_GAIN = "FFCGain";

CameraConfigReader* CameraConfigReader::thisInstance = NULL;

void CameraConfigReader::ReadConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, ".\\Configuration Files\\%s", CONFIG_NAME);
	// Number Of Cameras
	NumberOfCameras = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_CAMERAS, 0, configFileName);
	allCameraConfig.clear();
	for (int camIndex = 1; camIndex <= NumberOfCameras; camIndex++)
	{
		CameraConfig tempCameraConfig;
		std::string cameraAppName = std::string(CAMERA) + std::to_string(camIndex);
		// Camera Name
		char camName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(cameraAppName.c_str(), CAMERA_NAME, NULL, camName, MAX_PATH_LENGTH, configFileName);
		tempCameraConfig.cameraName = std::string(camName);
		// Camera ID
		tempCameraConfig.cameraID = GetPrivateProfileIntA(cameraAppName.c_str(), CAMERA_ID, 0, configFileName);
		// Camera Type
		tempCameraConfig.cameraType = (CameraType) GetPrivateProfileIntA(cameraAppName.c_str(), CAMERA_TYPE, 0, configFileName);
		// FG Index
		tempCameraConfig.fgIndex = GetPrivateProfileIntA(cameraAppName.c_str(), FG_INDEX, 0, configFileName);
		// DMA Index
		tempCameraConfig.dmaIndex = GetPrivateProfileIntA(cameraAppName.c_str(), DMA_INDEX, 0, configFileName);
		// Bytes Per Pixel
		tempCameraConfig.bytesPerPixel = GetPrivateProfileIntA(cameraAppName.c_str(), BYTES_PER_PIXEL, 0, configFileName);
		// Image Width
		tempCameraConfig.imageWidth = GetPrivateProfileIntA(cameraAppName.c_str(), IMAGE_WIDTH, 0, configFileName);
		// Image Height
		tempCameraConfig.imageHeight = GetPrivateProfileIntA(cameraAppName.c_str(), IMAGE_HEIGHT, 0, configFileName);
		// Buffer Count
		tempCameraConfig.imageBufferCount = GetPrivateProfileIntA(cameraAppName.c_str(), BUFFER_COUNT, 0, configFileName);
		// Allowed Buffered Images Count
		tempCameraConfig.allowedBufferedImageCount = GetPrivateProfileIntA(cameraAppName.c_str(), ALLOWED_BUFFERED_IMAGE_COUNT, 0, configFileName);
		// Time out
		tempCameraConfig.timeout = GetPrivateProfileIntA(cameraAppName.c_str(), TIME_OUT, 0, configFileName);
		// Number Of Light Sticks
		tempCameraConfig.numberOfLightSticks = GetPrivateProfileIntA(cameraAppName.c_str(), NUMBER_OF_LIGHT_STICKS, 0, configFileName);
		tempCameraConfig.lightSticksLevel.clear();
		for (int lightStickIndex = 1; lightStickIndex <= tempCameraConfig.numberOfLightSticks; lightStickIndex++)
		{
			std::string lightStickValueKey = "LightStick" + std::to_string(lightStickIndex) + "Level";
			tempCameraConfig.lightSticksLevel.push_back (GetPrivateProfileIntA(cameraAppName.c_str(), lightStickValueKey.c_str(), 0, configFileName));
		}

		// Number Of FFC Gains
		tempCameraConfig.numberOfFFCGains = GetPrivateProfileIntA(cameraAppName.c_str(), NUMBER_OF_FFC_GAINS, 0, configFileName);
		tempCameraConfig.ffcGain.clear();
		for (int ffcGainIndex = 1; ffcGainIndex <= tempCameraConfig.numberOfFFCGains; ffcGainIndex++)
		{
			std::string ffcGainValueKey = std::string(FFC_GAIN) + std::to_string(ffcGainIndex);
			tempCameraConfig.ffcGain.push_back(GetPrivateProfileIntA(cameraAppName.c_str(), ffcGainValueKey.c_str(), 0, configFileName));
		}
		allCameraConfig[tempCameraConfig.cameraID] = tempCameraConfig;
	}
}



CameraConfigReader *CameraConfigReader::GetInstance()
{
	if (thisInstance == NULL)
	{
		thisInstance = new CameraConfigReader();
		thisInstance->ReadConfiguration();
	}
	return thisInstance;
}