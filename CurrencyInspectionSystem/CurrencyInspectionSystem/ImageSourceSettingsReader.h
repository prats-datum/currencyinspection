#pragma once
#include "Globals.h"



class ImageSourceSettingsReader
{
	static char *CONFIG_PATH, *APP_NAME, *NUMBER_OF_CAMERAS, *CAMERA_APP_NAME, 
		*CAMERA_NAME, *IMAGE_SOURCE_TYPE, *IMAGE_FILE_PATH, *CONFIGURATION_FILE_PATH;
	static ImageSourceSettingsReader *thisInstance;
	void ReadConfiguration();
public:
	std::map<UINT, ImageSourceSettings> imageSourceSettingsList;
	ImageSourceSettingsReader();
	~ImageSourceSettingsReader();
	static ImageSourceSettingsReader * GetReader();
	void WriteConfiguration();
};

