#pragma once
#include "Globals.h"




class CameraConfigReader
{
	void ReadConfiguration();
	static CameraConfigReader *thisInstance;


	static char *CONFIG_NAME, *APP_NAME, *NUMBER_OF_CAMERAS, *CAMERA, *CAMERA_NAME, *CAMERA_ID, *CAMERA_TYPE,
		*FG_INDEX, *NUMBER_OF_LIGHT_STICKS, *NUMBER_OF_FFC_GAINS, *FFC_GAIN, *BYTES_PER_PIXEL, *DMA_INDEX, 
		*IMAGE_WIDTH, *IMAGE_HEIGHT, *BUFFER_COUNT, *ALLOWED_BUFFERED_IMAGE_COUNT, *TIME_OUT;

public:
	CameraConfigReader();
	~CameraConfigReader();

	static CameraConfigReader *GetInstance();

	int NumberOfCameras;
	std::map<UINT, CameraConfig> allCameraConfig;
};

