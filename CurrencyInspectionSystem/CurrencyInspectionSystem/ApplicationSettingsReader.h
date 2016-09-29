#pragma once
#include "Globals.h"



class ApplicationSettingsReader
{

	void ReadConfiguration();
	static ApplicationSettingsReader *thisInstance;


	static char *CONFIG_NAME, *APP_NAME, *NUMBER_OF_CAMERAS, *INSPECTION_WINDOW_EROSION_SIZE, *NUMBER_OF_COLOR_CHANNELS,
		*GOLDEN_DIRECTORY, *COLOR_CHANNEL_NAME, *COLOR_CHANNEL_TYPE, *DEFAULT_GOLDEN_LOCATION, *GPU_NAME, *APPLY_WINDOWED_THREAD_MASK,
		*NUMBER_OF_SHIFTS, *SHIFT_NAME, *SHIFT_STARTING_HOUR, *TOTAL_SHIFT_HOURS, *PER_HOUR_TARGET, *VERTICAL_RESOLUTION, *HORIZONTAL_RESOLUTION,
		*MACHINE_ID, *MAX_NUMBER_OF_LAYERS_ALLOWED, *SHEET_MINIMUM_LIFETIME, *SHEET_MAXIMUM_LIFETIME, *MAX_ALLOWED_CONSECUTIVE_NORESULTS_AVAILABLE,
		*SHIFT_DATA_LOCATION, *THREAD_MASK_WIDTH, *USE_THREE_CHANNEL_IMAGE_FOR_THREAD;

public:
	ApplicationSettingsReader();
	~ApplicationSettingsReader();

	static ApplicationSettingsReader *GetInstance();

	int NumberOfCameras;
	std::vector<ColorChannelConfig> allCameraColorChannelConfig;
	std::vector<ShiftTypes> shifConfig;
	std::string GoldenRootDirectory;
	std::string DefaultGoldenLocation;
	std::string GPUNameStr;
	std::string MachineID;
	std::string ShiftDataLocation;
	int MaxNumberOfLayersAllowed;
	bool ApplyWindowedThreadMask;
	double verticalResolution, horizontalResolution;
	int inspectionWindowErosionSize;
	int sheetMinimumLifetime, sheetMaximumLifeTime;
	int maxAllowedConsecutiveNoResultsAvailableEvents;
	int ThreadMaskWidth;
	bool UseThreeChannelImageForThread;

	int GetNumOfColorChennelforCamera(int camID);
	ColorChannel GetColorChannelConfigforCamera(int camID, int channelID);
};

