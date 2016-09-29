#pragma once
#include "Globals.h"

class InspectionParametersConfigReader
{

	static char *CONFIG_PATH, *CONFIG_FOLDER, *REGION_PARAMETERS_CONFIG, *NUMBER_OF_SENSITIVITY_LEVELS, *LEVEL,
		*TOLERANCE, *GAIN, *LIMIT, *BLOB_PARAMETERS_CONFIG, *NUMBER_OF_BLOB_PARAMETERS_GROUP,
		*GROUP, *GLOBAL_TOLERANCE, *MAJOR_BLOB_THRESHOLD, *DOMINANT_BLOB_THRESHOLD, *GROUP_OF_BLOB_THRESHOLD;


	static InspectionParametersConfigReader *thisInstance;
	void ReadConfiguration();


public:
	InspectionParametersConfigReader();
	~InspectionParametersConfigReader();
	static InspectionParametersConfigReader * GetReader();
	std::map<SensitivityLevels, std::string> SensitivityLevelStringMap;
	InspectionToleranceParametersLookup parametersLookup;
	void WriteConfiguration();
};

