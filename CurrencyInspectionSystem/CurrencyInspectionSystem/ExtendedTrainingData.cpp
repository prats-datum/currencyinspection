#include "stdafx.h"
#include "ExtendedTrainingData.h"


ExtendedTrainingData::ExtendedTrainingData()
{
	imgNumber = 0;
}


ExtendedTrainingData::ExtendedTrainingData(ULONG _imgNumber)
{
	imgNumber = _imgNumber;
}

ExtendedTrainingData::~ExtendedTrainingData()
{
	eachCameraExtendedData.clear();
}

void ExtendedTrainingData::AddCameraTrainingData(const HImage &_imageData, const HRegion _inspectionWindow, UINT _cameraID)
{
	eachCameraExtendedData[_cameraID] = ExtendedCameraTrainingData(_imageData, _inspectionWindow, _cameraID);
}


HImage ExtendedTrainingData::GetDisplayDetails(int defectIndex, HRegion &defectRegion, double &defectValue, double &defectSize, LearningType &learningType, int &cameraID)
{
	HImage returnImage;
	for (auto &camera : eachCameraExtendedData)
	{
		if (defectIndex < camera.second.GetTotalLearningsCount())
		{
			returnImage = camera.second.GetDisplayDetails(defectIndex, defectRegion, defectValue, defectSize, learningType);
			cameraID = camera.first;
		}
		defectIndex -= camera.second.GetTotalLearningsCount();
	}
	return returnImage;
}


bool ExtendedTrainingData::RemoveTrainingData(int defectIndex)
{
	bool returnValue;
	for (auto &camera : eachCameraExtendedData)
	{
		if (defectIndex < camera.second.GetTotalLearningsCount())
		{
			returnValue = camera.second.RemoveTrainingData(defectIndex);

		}
		defectIndex -= camera.second.GetTotalLearningsCount();
	}
	return returnValue;
}

int ExtendedTrainingData::GetTotalLearningsCount()
{
	int returnValue = 0;
	for (auto &e : eachCameraExtendedData)
	{
		returnValue += e.second.GetTotalLearningsCount();
	}
	return returnValue;
}

std::map<UINT, TrainingImageData> ExtendedTrainingData::GetTrainingData()
{
	std::map<UINT, TrainingImageData > allCameraTrainingData;
	for (auto &e : eachCameraExtendedData)
	{
		allCameraTrainingData[e.first] =  e.second.GetTrainingData();
	}
	return allCameraTrainingData;
}


ImageTrainingStatus ExtendedTrainingData::GetTrainingStatus()
{
	ImageTrainingStatus returnValue;
	bool isCompleteImageTrained = true;
	for (auto &e : eachCameraExtendedData)
	{
		isCompleteImageTrained &= e.second.isCompleteImageLearned;
	}
	if (isCompleteImageTrained)
	{
		returnValue = CompletelyTrained;
	}
	else if (GetTotalLearningsCount())
	{
		returnValue = PartiallyTrained;
	}
	else
	{
		returnValue = NotTrained;
	}
	return returnValue;
}


ExtendedCameraTrainingData::ExtendedCameraTrainingData()
{
	cameraID = 0;
	learnedMajorBlobs.clear();
	learnedDominantBlobs.clear();
	isCompleteImageLearned = false;
}

ExtendedCameraTrainingData::ExtendedCameraTrainingData(const HImage &_imageData, const HRegion &_inspectionWindow, UINT _cameraID)
{
	image = _imageData.CopyImage();
	inspectionWindow = _inspectionWindow.CopyObj(1, -1);
	cameraID = _cameraID;
	learnedMajorBlobs.clear();
	learnedDominantBlobs.clear();
	isCompleteImageLearned = false;

	HTuple row1, column1, row2, column2;
	inspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
	regionTransformationMatrix.VectorAngleToRigid(0.0, 0.0, 0.0, row1[0].D(), column1[0].D(), 0.0);
}

ExtendedCameraTrainingData::~ExtendedCameraTrainingData()
{
	image.Clear();
	learnedMajorBlobs.clear();
	learnedDominantBlobs.clear();
}

void ExtendedCameraTrainingData::LearnMajorDefectData(DefectData &_majorDefectData)
{
	DefectData tempDefectData;
	tempDefectData.defectID = _majorDefectData.defectID;
	tempDefectData.defectRegion = _majorDefectData.defectRegion.CopyObj(1, -1);
	tempDefectData.highlightingRegion = _majorDefectData.highlightingRegion.CopyObj(1, -1);
	tempDefectData.zoomWindowRegion = _majorDefectData.zoomWindowRegion.CopyObj(1, -1);
	tempDefectData.defectValue = _majorDefectData.defectValue;
	tempDefectData.defectSize = _majorDefectData.defectSize;
	learnedMajorBlobs[tempDefectData.defectID] = tempDefectData;
}
void ExtendedCameraTrainingData::LearnDominantDefectData(DefectData &_dominantDefectData)
{
	DefectData tempDefectData;
	tempDefectData.defectID = _dominantDefectData.defectID;
	tempDefectData.defectRegion = _dominantDefectData.defectRegion.CopyObj(1, -1);
	tempDefectData.highlightingRegion = _dominantDefectData.highlightingRegion.CopyObj(1, -1);
	tempDefectData.zoomWindowRegion = _dominantDefectData.zoomWindowRegion.CopyObj(1, -1);
	tempDefectData.defectValue = _dominantDefectData.defectValue;
	tempDefectData.defectSize = _dominantDefectData.defectSize;
	learnedDominantBlobs[tempDefectData.defectID] = tempDefectData;
}
void ExtendedCameraTrainingData::LearnCompleteImage()
{
	isCompleteImageLearned = true;
}

std::list<int> ExtendedCameraTrainingData::GetLearnedMajorDefectDataIDs()
{
	std::list<int> returnValue;
	for (auto &e : learnedMajorBlobs)
	{
		returnValue.push_back(e.first);
	}
	return returnValue;
}

std::list<int> ExtendedCameraTrainingData::GetLearnedDominantDefectDataIDs()
{
	std::list<int> returnValue;
	for (auto &e : learnedDominantBlobs)
	{
		returnValue.push_back(e.first);
	}
	return returnValue;
}


int ExtendedCameraTrainingData::GetTotalLearningsCount()
{
	return learnedMajorBlobs.size() + learnedDominantBlobs.size() + isCompleteImageLearned;
}


HImage ExtendedCameraTrainingData::GetDisplayDetails(int defectIndex, HRegion &defectRegion, double &defectValue, double &defectSize, LearningType &learningType)
{
	HImage displayImage = image.ReduceDomain(inspectionWindow).CropDomain();
	if (defectIndex < learnedMajorBlobs.size())
	{
		std::map<UINT, DefectData>::iterator iter= learnedMajorBlobs.begin();
		std::advance(iter, defectIndex);
		displayImage = displayImage.ReduceDomain(iter->second.highlightingRegion).CropDomain();
		defectRegion = iter->second.zoomWindowRegion;
		defectValue = iter->second.defectValue;
		defectSize = iter->second.defectSize;
		learningType = LearningType::LearnMajorBlob;
	}
	else if (defectIndex < (learnedMajorBlobs.size() + learnedDominantBlobs.size()))
	{
		std::map<UINT, DefectData>::iterator iter = learnedDominantBlobs.begin();
		std::advance(iter, (defectIndex - learnedMajorBlobs.size()));
		displayImage = displayImage.ReduceDomain(iter->second.highlightingRegion).CropDomain();
		defectRegion = iter->second.zoomWindowRegion;
		defectValue = iter->second.defectValue;
		defectSize = iter->second.defectSize;
		learningType = LearningType::LearnDominantBlob;
	}
	else
	{
		defectRegion.GenEmptyRegion();
		defectValue = -1;
		defectSize = -1;
		learningType = LearningType::LearnCompleteImage;
	}
	return displayImage;
}

bool ExtendedCameraTrainingData::RemoveTrainingData(int defectIndex)
{
	bool isRemoved = false;
	if (defectIndex < learnedMajorBlobs.size())
	{
		std::map<UINT, DefectData>::iterator iter = learnedMajorBlobs.begin();
		std::advance(iter, defectIndex);
		learnedMajorBlobs.erase(iter);
		isRemoved = true;
	}
	else if (defectIndex < (learnedMajorBlobs.size() + learnedDominantBlobs.size()))
	{
		std::map<UINT, DefectData>::iterator iter = learnedDominantBlobs.begin();
		std::advance(iter, (defectIndex - learnedMajorBlobs.size()));
		learnedDominantBlobs.erase(iter);
		isRemoved = true;
	}
	else if(isCompleteImageLearned)
	{
		isCompleteImageLearned = false;
		isRemoved = true;
	}
	return isRemoved;
}

TrainingImageData ExtendedCameraTrainingData::GetTrainingData()
{
	HRegion maskRegion;

	if (isCompleteImageLearned)
	{
		maskRegion.GenEmptyRegion();
	}
	else
	{
		maskRegion = image.GetDomain();
		
		for (auto &e : learnedMajorBlobs)
		{
			maskRegion = maskRegion.Difference(e.second.defectRegion.AffineTransRegion(regionTransformationMatrix, "nearest_neighbor"));
		}
		for (auto &e : learnedDominantBlobs)
		{
			maskRegion = maskRegion.Difference(e.second.defectRegion.AffineTransRegion(regionTransformationMatrix, "nearest_neighbor"));
		}
	}

	return TrainingImageData(image, image.Rgb1ToGray(), maskRegion, 0, ExtensionTrainingSet); //Image Number should be updated at Golden Generator
}