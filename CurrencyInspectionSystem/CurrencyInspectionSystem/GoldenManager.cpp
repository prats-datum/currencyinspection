#include "stdafx.h"
#include "GoldenManager.h"


char *GoldenManager::APP_NAME = "GoldenDetails";
char *GoldenManager::CONFIG_NAME = "GoldenDetails.ini";
char *GoldenManager::AVAILABLE_GOLDEN_COUNT_KEY = "AvailableGoldensCount";
char *GoldenManager::GOLDEN_NAME = "GoldenName";
char *GoldenManager::GOLDEN_LOCATION = "GoldenLocation";


GoldenManager::GoldenManager()
{
}


GoldenManager::~GoldenManager()
{
}

void GoldenManager::ReadGoldenDetails(std::string _goldenRootDirectory)
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", _goldenRootDirectory.c_str(), CONFIG_NAME);
	int numberOfAvailableGolden = GetPrivateProfileIntA(APP_NAME, AVAILABLE_GOLDEN_COUNT_KEY, 0, configFileName);
	goldenNameLocationMap.clear();
	for (int index = 1; index <= numberOfAvailableGolden; index++)
	{
		std::string GOLDEN_APP_NAME = "GOLDEN_" + std::to_string(index);
		char tempGoldenName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(GOLDEN_APP_NAME.c_str(), GOLDEN_NAME, NULL, tempGoldenName, MAX_PATH_LENGTH, configFileName);
		char tempGoldenLocation[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(GOLDEN_APP_NAME.c_str(), GOLDEN_LOCATION, NULL, tempGoldenLocation, MAX_PATH_LENGTH, configFileName);
		goldenNameLocationMap[std::string(tempGoldenName)] = std::string(tempGoldenLocation);
	}
}

void GoldenManager::WriteGoldenDetails(std::string _goldenRootDirectory)
{
	DWORD ftyp = GetFileAttributesA(_goldenRootDirectory.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(_goldenRootDirectory.c_str(), NULL);
	}
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", _goldenRootDirectory.c_str(), CONFIG_NAME);

	ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}
	//GoldenName
	WritePrivateProfileStringA(APP_NAME, AVAILABLE_GOLDEN_COUNT_KEY, std::to_string(goldenNameLocationMap.size()).c_str(), configFileName);
	
	int index = 1;
	for (auto &e : goldenNameLocationMap)
	{
		std::string GOLDEN_APP_NAME = "GOLDEN_" + std::to_string(index);
		WritePrivateProfileStringA(GOLDEN_APP_NAME.c_str(), GOLDEN_NAME, e.first.c_str(), configFileName);
		WritePrivateProfileStringA(GOLDEN_APP_NAME.c_str(), GOLDEN_LOCATION, e.second.c_str(), configFileName);
		index++;
	}
}


bool GoldenManager::SetGoldenDirectory(std::string _goldenRootDirectory)
{
	bool returnValue = true;
	goldenRootDirectory = _goldenRootDirectory;

	// Trying to Create Directory
	DWORD ftyp = GetFileAttributesA(goldenRootDirectory.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		returnValue = CreateDirectoryA(goldenRootDirectory.c_str(), NULL);
	}
	ReadGoldenDetails(goldenRootDirectory);
	return returnValue;
}

void GoldenManager::AddGolden(std::string _goldenName)
{
	std::string tempGoldenLocation = goldenRootDirectory + "\\Golden_" + _goldenName;
	DWORD ftyp = GetFileAttributesA(tempGoldenLocation.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(tempGoldenLocation.c_str(), NULL);
	}
	goldenNameLocationMap[_goldenName] = tempGoldenLocation;
	WriteGoldenDetails(goldenRootDirectory);
}

void GoldenManager::DeleteGolden(std::string _goldenName)
{
	std::string tempGoldenLocation = goldenRootDirectory + "\\Golden_" + _goldenName;
	if (goldenNameLocationMap.find(_goldenName) != goldenNameLocationMap.end())
	{
		goldenNameLocationMap.erase(_goldenName);
		//TO-DO Delete all files in golden directory
	}
	WriteGoldenDetails(goldenRootDirectory);
}

std::vector<std::string> GoldenManager::GetAvailableGoldenList()
{
	std::vector<std::string> availableGoldenList;
	for (auto &e : goldenNameLocationMap)
	{
		availableGoldenList.push_back(e.first);
	}
	return availableGoldenList;
}


std::map <std::string, std::string> GoldenManager::GetGoldenNameLocationMap()
{
	return goldenNameLocationMap;
}

std::string GoldenManager::GetGoldenLocation(std::string _goldenName)
{
	std::string tempGoldenLocation = "";
	if (goldenNameLocationMap.find(_goldenName) != goldenNameLocationMap.end())
	{
		tempGoldenLocation = goldenRootDirectory + "\\Golden_" + _goldenName;
	}
	return tempGoldenLocation;
}