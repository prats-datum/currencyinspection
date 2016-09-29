#include "stdafx.h"
#include "ImageSourceSettingsReader.h"


char * ImageSourceSettingsReader::CONFIG_PATH = "./Configuration Files/Image Source Settings.ini";
char * ImageSourceSettingsReader::APP_NAME = "ImageSourceSettings";
char * ImageSourceSettingsReader::NUMBER_OF_CAMERAS = "NumberOfCameras";
char * ImageSourceSettingsReader::CAMERA_APP_NAME = "Camera";
char * ImageSourceSettingsReader::CAMERA_NAME = "CameraName";
char * ImageSourceSettingsReader::IMAGE_SOURCE_TYPE = "ImageSourceType";
char * ImageSourceSettingsReader::IMAGE_FILE_PATH = "ImageFilePath";
char * ImageSourceSettingsReader::CONFIGURATION_FILE_PATH = "ConfigurationFilePath";


ImageSourceSettingsReader::ImageSourceSettingsReader()
{
}

ImageSourceSettingsReader::~ImageSourceSettingsReader()
{
}

ImageSourceSettingsReader *ImageSourceSettingsReader::thisInstance = NULL;

ImageSourceSettingsReader *ImageSourceSettingsReader::GetReader()
{
	if (thisInstance == NULL)
	{
		thisInstance = new ImageSourceSettingsReader();
		thisInstance->ReadConfiguration();
	}
	return thisInstance;
}

void ImageSourceSettingsReader::ReadConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s", CONFIG_PATH);

	int numberOfCameras = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_CAMERAS, 0, configFileName);
	imageSourceSettingsList.clear();
	for (int cameraID = 1; cameraID <= numberOfCameras; cameraID++)
	{
		ImageSourceSettings imgSourceSetting;
		char CameraIDAppName[MAX_PATH_LENGTH];
		sprintf_s(CameraIDAppName, MAX_PATH_LENGTH, "%s%d", CAMERA_APP_NAME, cameraID);
		char cameraName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(CameraIDAppName, CAMERA_NAME, NULL, cameraName, MAX_PATH_LENGTH, configFileName);
		imgSourceSetting.cameraName = std::string(cameraName);
		imgSourceSetting.imageSourceType = (ImageSourceType)GetPrivateProfileIntA(CameraIDAppName, IMAGE_SOURCE_TYPE, 0, configFileName);
		char imageFilesPath[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(CameraIDAppName, IMAGE_FILE_PATH, NULL, imageFilesPath, MAX_PATH_LENGTH, configFileName);
		imgSourceSetting.imageFilesPath = std::string(imageFilesPath);
		char configFilePath[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(CameraIDAppName, CONFIGURATION_FILE_PATH, NULL, configFilePath, MAX_PATH_LENGTH, configFileName);
		imgSourceSetting.configFilePath = std::string(configFilePath);
		imageSourceSettingsList[cameraID] = imgSourceSetting;		
	}
}

void ImageSourceSettingsReader::WriteConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s", CONFIG_PATH);
	int numberOfCameras = imageSourceSettingsList.size();
	for (int cameraID = 1; cameraID <= numberOfCameras; cameraID++)
	{
		char CameraIDAppName[MAX_PATH_LENGTH];
		sprintf_s(CameraIDAppName, MAX_PATH_LENGTH, "%s%d", CAMERA_APP_NAME, cameraID);
		WritePrivateProfileStringA(CameraIDAppName, IMAGE_SOURCE_TYPE, std::to_string(imageSourceSettingsList[cameraID].imageSourceType).c_str(), configFileName);
		WritePrivateProfileStringA(CameraIDAppName, IMAGE_FILE_PATH, imageSourceSettingsList[cameraID].imageFilesPath.c_str(), configFileName);
		WritePrivateProfileStringA(CameraIDAppName, CONFIGURATION_FILE_PATH, imageSourceSettingsList[cameraID].configFilePath.c_str(), configFileName);
	}
}