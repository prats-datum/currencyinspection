#pragma once
#include "Globals.h"

enum ImageTrainingStatus
{
	NotTrained = 3,
	PartiallyTrained = 4,
	CompletelyTrained = 5
};


class ExtendedCameraTrainingData
{

public:
	UINT cameraID;
	HImage image;
	HRegion inspectionWindow;
	bool isCompleteImageLearned;
	std::map<UINT, DefectData> learnedMajorBlobs;
	std::map<UINT, DefectData> learnedDominantBlobs;
	HHomMat2D regionTransformationMatrix;

	ExtendedCameraTrainingData();
	ExtendedCameraTrainingData(const HImage &_imageData, const HRegion &_inspectionWindow, UINT _cameraID);
	~ExtendedCameraTrainingData();

	void LearnMajorDefectData(DefectData &_majorDefectData);
	void LearnDominantDefectData(DefectData &_dominantDefectData);
	void LearnCompleteImage();
	std::list<int> GetLearnedMajorDefectDataIDs();
	std::list<int> GetLearnedDominantDefectDataIDs();
	int GetTotalLearningsCount();
	HImage GetDisplayDetails(int defectIndex, HRegion &defectRegion, double &defectValue, double &defectSize, LearningType &learningType);
	bool RemoveTrainingData(int defectIndex);
	TrainingImageData GetTrainingData();
};

class ExtendedTrainingData
{
public:
	ULONG imgNumber;
	std::map<UINT, ExtendedCameraTrainingData> eachCameraExtendedData;

	ExtendedTrainingData();
	~ExtendedTrainingData();
	ExtendedTrainingData(ULONG _imgNumber);
	void AddCameraTrainingData(const HImage &_imageData, const HRegion _inspectionWindow, UINT _cameraID);
	HImage GetDisplayDetails(int defectIndex, HRegion &defectRegion, double &defectValue, double &defectSize, LearningType &learningType, int &cameraID);
	bool RemoveTrainingData(int defectIndex);
	int GetTotalLearningsCount();
	std::map<UINT, TrainingImageData> GetTrainingData();
	ImageTrainingStatus GetTrainingStatus();
};

