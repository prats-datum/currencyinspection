#pragma once
#include"Globals.h"

class GoldenManager
{
	static char *APP_NAME, *CONFIG_NAME, *AVAILABLE_GOLDEN_COUNT_KEY, *GOLDEN_NAME, *GOLDEN_LOCATION;

	std::string goldenRootDirectory;
	std::map <std::string, std::string> goldenNameLocationMap;

	void ReadGoldenDetails(std::string _goldenRootDirectory);
	void WriteGoldenDetails(std::string _goldenRootDirectory);

public:
	GoldenManager();
	~GoldenManager();

	bool SetGoldenDirectory(std::string _goldenRootDirectory);
	void AddGolden(std::string _goldenName);
	void DeleteGolden(std::string _goldenName);
	std::vector<std::string> GetAvailableGoldenList();
	std::map <std::string, std::string>GetGoldenNameLocationMap();
	std::string GetGoldenLocation(std::string _goldenName);
};

