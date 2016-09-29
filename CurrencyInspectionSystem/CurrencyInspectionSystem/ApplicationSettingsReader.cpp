#include "stdafx.h"
#include "ApplicationSettingsReader.h"


ApplicationSettingsReader::ApplicationSettingsReader()
{
}


ApplicationSettingsReader::~ApplicationSettingsReader()
{
}

char* ApplicationSettingsReader::CONFIG_NAME = "Application Settings.ini";
char* ApplicationSettingsReader::APP_NAME = "ApplicationSettings";
char* ApplicationSettingsReader::NUMBER_OF_CAMERAS = "NumberOfCameras";
char* ApplicationSettingsReader::INSPECTION_WINDOW_EROSION_SIZE = "InspectionWindowErosionSize";
char* ApplicationSettingsReader::NUMBER_OF_COLOR_CHANNELS = "NumberOfColorChannels";
char* ApplicationSettingsReader::COLOR_CHANNEL_NAME = "ColorChannelName";
char* ApplicationSettingsReader::COLOR_CHANNEL_TYPE = "ColorChannelType";
char* ApplicationSettingsReader::GOLDEN_DIRECTORY = "GoldenDirectory";
char* ApplicationSettingsReader::GPU_NAME = "GPUName";
char* ApplicationSettingsReader::APPLY_WINDOWED_THREAD_MASK = "ApplyWindowedThreadMask";
char* ApplicationSettingsReader::DEFAULT_GOLDEN_LOCATION = "DefaultGoldenLocation";
char* ApplicationSettingsReader::NUMBER_OF_SHIFTS = "NumberOfShifts";
char* ApplicationSettingsReader::SHIFT_NAME = "ShiftName";
char* ApplicationSettingsReader::SHIFT_STARTING_HOUR = "ShiftStartHour";
char* ApplicationSettingsReader::TOTAL_SHIFT_HOURS = "TotalShifHours";
char* ApplicationSettingsReader::PER_HOUR_TARGET = "PerHourTarget";
char* ApplicationSettingsReader::VERTICAL_RESOLUTION = "VerticalResolution";
char* ApplicationSettingsReader::HORIZONTAL_RESOLUTION = "HorizontalResolution";
char* ApplicationSettingsReader::MACHINE_ID = "MachineID";
char* ApplicationSettingsReader::MAX_NUMBER_OF_LAYERS_ALLOWED = "MaxNumberOfLayersAllowed";
char* ApplicationSettingsReader::SHEET_MINIMUM_LIFETIME = "SheetMinimumLifeTime";
char* ApplicationSettingsReader::SHEET_MAXIMUM_LIFETIME = "SheetMaximumLifeTime";
char* ApplicationSettingsReader::MAX_ALLOWED_CONSECUTIVE_NORESULTS_AVAILABLE = "MaxAllowedConsecutiveNoResultsAvailable";
char* ApplicationSettingsReader::SHIFT_DATA_LOCATION = "ShiftDataLocation";
char* ApplicationSettingsReader::THREAD_MASK_WIDTH = "ThreadMaskWidth";
char* ApplicationSettingsReader::USE_THREE_CHANNEL_IMAGE_FOR_THREAD = "UseThreeChannelImageForThread";


ApplicationSettingsReader *ApplicationSettingsReader::thisInstance = NULL;

ApplicationSettingsReader *ApplicationSettingsReader::GetInstance()
{
	if (thisInstance == NULL)
	{
		thisInstance = new ApplicationSettingsReader();
		thisInstance->ReadConfiguration();
	}
	return thisInstance;
}

void ApplicationSettingsReader::ReadConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, ".\\Configuration Files\\%s", CONFIG_NAME);
	//Number Of Cameras
	NumberOfCameras = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_CAMERAS, 0, configFileName);

	//Inspection Window Erosion Size
	inspectionWindowErosionSize = GetPrivateProfileIntA(APP_NAME, INSPECTION_WINDOW_EROSION_SIZE, 0, configFileName);

	//Golden Directory
	char goldenDir[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, GOLDEN_DIRECTORY, NULL, goldenDir, MAX_PATH_LENGTH, configFileName);
	GoldenRootDirectory = std::string(goldenDir);

	//GPU Name
	char GPUNameChar[MAX_GPU_NAME_LENGTH];
	GetPrivateProfileStringA(APP_NAME, GPU_NAME, NULL, GPUNameChar, MAX_GPU_NAME_LENGTH, configFileName);
	GPUNameStr = std::string(GPUNameChar);

	//Default Golden Directory
	char defaultGoldenDir[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, DEFAULT_GOLDEN_LOCATION, NULL, defaultGoldenDir, MAX_PATH_LENGTH, configFileName);
	DefaultGoldenLocation = std::string(defaultGoldenDir);

	//Vertical Resolution
	char resolutionStr[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, VERTICAL_RESOLUTION, NULL, resolutionStr, MAX_PATH_LENGTH, configFileName);
	verticalResolution = atof(resolutionStr);

	//Horizontal Resolution
	GetPrivateProfileStringA(APP_NAME, HORIZONTAL_RESOLUTION, NULL, resolutionStr, MAX_PATH_LENGTH, configFileName);
	horizontalResolution = atof(resolutionStr);

	// Sheet Minimum Life Time
	sheetMinimumLifetime = GetPrivateProfileIntA(APP_NAME, SHEET_MINIMUM_LIFETIME, 0, configFileName);

	// Sheet Maximum Life Time
	sheetMaximumLifeTime = GetPrivateProfileIntA(APP_NAME, SHEET_MAXIMUM_LIFETIME, 0, configFileName);

	// Max Allowed Consecutive No Results Available
	maxAllowedConsecutiveNoResultsAvailableEvents = GetPrivateProfileIntA(APP_NAME, MAX_ALLOWED_CONSECUTIVE_NORESULTS_AVAILABLE, 0, configFileName);

	//MachineID
	char machineIDStr[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MACHINE_ID, NULL, machineIDStr, MAX_PATH_LENGTH, configFileName);
	MachineID = std::string(machineIDStr);

	//Max Number of layers allowed
	MaxNumberOfLayersAllowed = GetPrivateProfileIntA(APP_NAME, MAX_NUMBER_OF_LAYERS_ALLOWED, 3, configFileName);

	char shiftDataDir[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, SHIFT_DATA_LOCATION, NULL, shiftDataDir, MAX_PATH_LENGTH, configFileName);
	ShiftDataLocation = std::string(shiftDataDir);

	//Apply windowed Thread Mask
	ApplyWindowedThreadMask = GetPrivateProfileIntA(APP_NAME, APPLY_WINDOWED_THREAD_MASK, 0, configFileName);

	// Thread Mask Width
	ThreadMaskWidth = GetPrivateProfileIntA(APP_NAME, THREAD_MASK_WIDTH, 0, configFileName);
	
	// UseThreeChannelImageForThread
	UseThreeChannelImageForThread = GetPrivateProfileIntA(APP_NAME, USE_THREE_CHANNEL_IMAGE_FOR_THREAD, 0, configFileName);



	allCameraColorChannelConfig.clear();
	for (int camID = 1; camID <= NumberOfCameras; camID++)
	{
		//Number Of Color Channel for Camera
		ColorChannelConfig tempColorChannelConfig;
		std::string numberOfColorChannelCamera = std::string(NUMBER_OF_COLOR_CHANNELS) + "Cam" + std::to_string(camID);
		tempColorChannelConfig.numOfColorChannels = GetPrivateProfileIntA(APP_NAME, numberOfColorChannelCamera.c_str(), 0, configFileName);

		//Color Channel
		for (int index = 1; index <= tempColorChannelConfig.numOfColorChannels; index++)
		{
			std::string COLOR_CHANNEL_APP_NAME = "Cam" + std::to_string(camID) + "ColorChannel" + std::to_string(index);
			ColorChannel tempColorChennel;

			//Color Channel Type
			tempColorChennel.type = (ColorChannelType)GetPrivateProfileIntA(COLOR_CHANNEL_APP_NAME.c_str(), COLOR_CHANNEL_TYPE, 0, configFileName);

			//Color Channel Name
			char colorChannelName[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(COLOR_CHANNEL_APP_NAME.c_str(), COLOR_CHANNEL_NAME, NULL, colorChannelName, MAX_PATH_LENGTH, configFileName);
			tempColorChennel.name = std::string(colorChannelName);
			tempColorChannelConfig.DefaultColorChannels.push_back(tempColorChennel);
		}
		allCameraColorChannelConfig.push_back(tempColorChannelConfig);
	}
	

	//Shift Count
	int shiftCount = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_SHIFTS, 0, configFileName);
	shifConfig.clear();
	for (int index = 1; index <= shiftCount; index++)
	{
		std::string SHIFT_APP_NAME = "SHIFT" + std::to_string(index);
		ShiftTypes tempShifConfig;
		//Shift Name
		char shiftName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(SHIFT_APP_NAME.c_str(), SHIFT_NAME, NULL, shiftName, MAX_PATH_LENGTH, configFileName);
		tempShifConfig.shiftName = std::string(shiftName);
		//Shift Start Hour
		tempShifConfig.shiftStartHour = GetPrivateProfileIntA(SHIFT_APP_NAME.c_str(), SHIFT_STARTING_HOUR, 0, configFileName);
		//Total Shift Hours
		tempShifConfig.totalShiftHours = GetPrivateProfileIntA(SHIFT_APP_NAME.c_str(), TOTAL_SHIFT_HOURS, 0, configFileName);
		//Per Hour Target
		tempShifConfig.perHourTarget = GetPrivateProfileIntA(SHIFT_APP_NAME.c_str(), PER_HOUR_TARGET, 0, configFileName);
		shifConfig.push_back(tempShifConfig);
	}
}

int ApplicationSettingsReader::GetNumOfColorChennelforCamera(int camID)
{
	int returnValue = 0;
	if (camID <= NumberOfCameras)
	{
		returnValue = allCameraColorChannelConfig[camID - 1].numOfColorChannels;
	}
	return returnValue;
}

ColorChannel ApplicationSettingsReader::GetColorChannelConfigforCamera(int camID, int channelID)
{
	ColorChannel returnValue;
	if (camID <= NumberOfCameras)
	{
		if (channelID < allCameraColorChannelConfig[camID - 1].numOfColorChannels)
		{
			returnValue = allCameraColorChannelConfig[camID - 1].DefaultColorChannels[channelID];
		}
	}
	return returnValue;
}