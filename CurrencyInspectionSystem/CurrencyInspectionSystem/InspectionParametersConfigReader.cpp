#include "stdafx.h"
#include "InspectionParametersConfigReader.h"


InspectionParametersConfigReader::InspectionParametersConfigReader()
{
	SensitivityLevelStringMap[Level1] = "Level1";
	SensitivityLevelStringMap[Level2] = "Level2";
	SensitivityLevelStringMap[Level3] = "Level3";
	SensitivityLevelStringMap[Level4] = "Level4";
	SensitivityLevelStringMap[Level5] = "Level5";
	SensitivityLevelStringMap[Custom1] = "Custom1";
	SensitivityLevelStringMap[Custom2] = "Custom2";
}


InspectionParametersConfigReader::~InspectionParametersConfigReader()
{
}


InspectionParametersConfigReader *InspectionParametersConfigReader::thisInstance = NULL;


InspectionParametersConfigReader *InspectionParametersConfigReader::GetReader()
{
	if (thisInstance == NULL)
	{
		thisInstance = new InspectionParametersConfigReader();
		thisInstance->ReadConfiguration();
	}
	return thisInstance;
}



void InspectionParametersConfigReader::ReadConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s", CONFIG_PATH);

	int numberOfSensitivityLevels = GetPrivateProfileIntA(REGION_PARAMETERS_CONFIG, NUMBER_OF_SENSITIVITY_LEVELS, 0, configFileName);

	for (int levelID = 1; levelID <= numberOfSensitivityLevels; levelID++)
	{
		char LevelIDAppName[MAX_PATH_LENGTH];
		sprintf_s(LevelIDAppName, MAX_PATH_LENGTH, "%s%d", LEVEL, levelID);
		char toleranceLocationString[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(LevelIDAppName, TOLERANCE, NULL, toleranceLocationString, MAX_PATH_LENGTH, configFileName);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].tolerance = HTuple::ReadTuple(toleranceLocationString);
		char gainLocationString[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(LevelIDAppName, GAIN, NULL, gainLocationString, MAX_PATH_LENGTH, configFileName);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].gain = HTuple::ReadTuple(gainLocationString);
		char limitLocationString[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(LevelIDAppName, LIMIT, NULL, limitLocationString, MAX_PATH_LENGTH, configFileName);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].limit = HTuple::ReadTuple(limitLocationString);
	}

	int numberOfBlobParametersGroups = GetPrivateProfileIntA(BLOB_PARAMETERS_CONFIG, NUMBER_OF_BLOB_PARAMETERS_GROUP, 0, configFileName);
	for (int groupID = 1; groupID <= numberOfBlobParametersGroups; groupID++)
	{
		char GroupIDAppName[MAX_PATH_LENGTH];
		sprintf_s(GroupIDAppName, MAX_PATH_LENGTH, "%s%d", GROUP, groupID);
		parametersLookup.blobParameterLookup[groupID - 1].globalTolerance = GetPrivateProfileIntA(GroupIDAppName, GLOBAL_TOLERANCE, 0, configFileName);
		parametersLookup.blobParameterLookup[groupID - 1].majorBlobThreshold = GetPrivateProfileIntA(GroupIDAppName, MAJOR_BLOB_THRESHOLD, 0, configFileName);
		parametersLookup.blobParameterLookup[groupID - 1].dominantBlobThreshold = GetPrivateProfileIntA(GroupIDAppName, DOMINANT_BLOB_THRESHOLD, 0, configFileName);
		parametersLookup.blobParameterLookup[groupID - 1].groupOfBlobThreshold = GetPrivateProfileIntA(GroupIDAppName, GROUP_OF_BLOB_THRESHOLD, 0, configFileName);
	}
}


void InspectionParametersConfigReader::WriteConfiguration()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s", CONFIG_PATH);

	int numberOfSensitivityLevels = GetPrivateProfileIntA(REGION_PARAMETERS_CONFIG, NUMBER_OF_SENSITIVITY_LEVELS, 0, configFileName);
	for (int levelID = 1; levelID <= numberOfSensitivityLevels; levelID++)
	{
		char toleranceLocationString[MAX_PATH_LENGTH];
		sprintf_s(toleranceLocationString, "%s/%s%d_%s.tup", CONFIG_FOLDER, LEVEL, levelID, TOLERANCE);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].tolerance.WriteTuple(toleranceLocationString);

		char gainLocationString[MAX_PATH_LENGTH];
		sprintf_s(gainLocationString, "%s/%s%d_%s.tup", CONFIG_FOLDER, LEVEL, levelID, GAIN);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].gain.WriteTuple(gainLocationString);

		char limitLocationString[MAX_PATH_LENGTH];
		sprintf_s(limitLocationString, "%s/%s%d_%s.tup", CONFIG_FOLDER, LEVEL, levelID, LIMIT);
		parametersLookup.sensitivityLevelParameterLookup[levelID - 1].limit.WriteTuple(limitLocationString);
	}

	int numberOfBlobParametersGroups = GetPrivateProfileIntA(BLOB_PARAMETERS_CONFIG, NUMBER_OF_BLOB_PARAMETERS_GROUP, 0, configFileName);
	for (int groupID = 1; groupID <= numberOfBlobParametersGroups; groupID++)
	{
		char GroupIDAppName[MAX_PATH_LENGTH];
		sprintf_s(GroupIDAppName, MAX_PATH_LENGTH, "%s%d", GROUP, groupID);
		WritePrivateProfileStringA(GroupIDAppName, GLOBAL_TOLERANCE, std::to_string(parametersLookup.blobParameterLookup[groupID - 1].globalTolerance).c_str(), configFileName);
		WritePrivateProfileStringA(GroupIDAppName, MAJOR_BLOB_THRESHOLD, std::to_string(parametersLookup.blobParameterLookup[groupID - 1].majorBlobThreshold).c_str(), configFileName);
		WritePrivateProfileStringA(GroupIDAppName, DOMINANT_BLOB_THRESHOLD, std::to_string(parametersLookup.blobParameterLookup[groupID - 1].dominantBlobThreshold).c_str(), configFileName);
		WritePrivateProfileStringA(GroupIDAppName, GROUP_OF_BLOB_THRESHOLD, std::to_string(parametersLookup.blobParameterLookup[groupID - 1].groupOfBlobThreshold).c_str(), configFileName);
	}
}


char * InspectionParametersConfigReader::CONFIG_PATH = "./Configuration Files/Inspection Parameters/InspectionParameterConfig.ini";
char * InspectionParametersConfigReader::CONFIG_FOLDER = "./Configuration Files/Inspection Parameters";
char * InspectionParametersConfigReader::REGION_PARAMETERS_CONFIG = "RegionParametersConfig";
char * InspectionParametersConfigReader::NUMBER_OF_SENSITIVITY_LEVELS = "NumberOfSensitivityLevels";
char * InspectionParametersConfigReader::LEVEL = "Level";
char * InspectionParametersConfigReader::TOLERANCE = "Tolerance";
char * InspectionParametersConfigReader::GAIN = "Gain";
char * InspectionParametersConfigReader::LIMIT = "Limit";
char * InspectionParametersConfigReader::BLOB_PARAMETERS_CONFIG = "BlobParametersConfig";
char * InspectionParametersConfigReader::NUMBER_OF_BLOB_PARAMETERS_GROUP = "NumberOfBlobParameterGroups";
char * InspectionParametersConfigReader::GROUP = "Group";
char * InspectionParametersConfigReader::GLOBAL_TOLERANCE = "GlobalTolerance";
char * InspectionParametersConfigReader::MAJOR_BLOB_THRESHOLD = "MajorBlobThreshold";
char * InspectionParametersConfigReader::DOMINANT_BLOB_THRESHOLD = "DominantBlobThreshold";
char * InspectionParametersConfigReader::GROUP_OF_BLOB_THRESHOLD = "GroupOfBlobThreshold";


