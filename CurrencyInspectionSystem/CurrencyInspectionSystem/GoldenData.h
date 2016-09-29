#pragma once

#include "HalconCpp.h"
#include "Globals.h"
#include <list>
#include <vector>
#include <ctime>
#include <time.h>
#include <algorithm>

using namespace HalconCpp;


class InspectionData
{
public:
	UINT taskID;
	InspectionTypes typeOfInspectionTask;
	std::string taskName;
	virtual void ReadConfiguration(std::string folderName)
	{}
	virtual void WriteConfiguration(std::string folderName)
	{}
	virtual bool ResetMinMaxData()
	{
		return true;
	}
};

class LayerAnchorRegion : public InspectionData
{
	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME, *SEARCH_TYPE_KEY, *ANCHOR_COUNT_KEY, *ANCHOR_REG_KEY, 
		*NCC_COUNT_KEY, *NCC_MODEL_KEY, *SHAPE_COUNT_KEY, *SHAPE_MODEL_KEY, *SOURCE_ID_COUNT_KEY, *SOURCE_ID_KEY;
	//
public:

	std::vector<HRegion> regionList;
	SearchType searchType;
	UINT regID;
	RegionTypes regType;

	//hardcoded
	HTuple NumLevels = 4;
	double AngleStart = -0.39;
	double AngleExtent = 0.79;
	HTuple AngleStep = 0.1;
	HString Metric = "use_polarity";
	double MinScore = 0.5;
	double MaxOverlap = 0.5;
	Hlong NumMatches = 1;
	HTuple SubPixel_ShapeModel = "least_squares";
	HTuple SubPixel_NCCModel = "true";
	double Greediness = 0.9;
	HTuple Optimization = "auto";
	HTuple Contrast = "auto";
	HTuple MinContrast = "auto";
	//

	std::vector<HShapeModel> shapeModelList;
	std::vector<HNCCModel> nccModelList;
	std::vector<UINT> sourceTaskIDList;

	HRegion GetRemainingRegion(HRegion &tempRegion);
	void CreateModel(HImage masterImageReduced);
	virtual void ReadConfiguration(std::string folderName);
	virtual void WriteConfiguration(std::string folderName);
};

class LayerRegion
{
public:

	//ConfigDetails
	static char *LAYER_REGION_APP_NAME, *MASK_REGION_APP_NAME,
		*STATISTICS_REGION_APP_NAME,
		*LAYER_REGION_ID_KEY, *LAYER_REGION_NAME_KEY,
		*LAYER_REGION__KEY, *LAYER_REGION_REP_KEY, *LAYER_REGION_INSP_TYPE_KEY,
		*LAYER_REGION_COUNT_KEY;
	//

	UINT regionID;
	std::string regionName = "";
	std::vector<HRegion> regionList;
	std::vector<HRegion> repitingPortionList;
	RegionTypes insRegionType;
	HRegion GetRegion();
};

class LayerInspectionRegion : public LayerRegion
{
public:
	//ConfigDetails
	static char *INSP_REGION_APP_NAME,  *INSP_UNDER_INK_KEY, *INSP_OVER_INK_KEY;
	//

	SensitivityLevels underInkingSensitivity;
	SensitivityLevels overInkingSensitivity;
};

class LayerTransferMaskRegion
{
public:
	//ConfigDetails
	static char *TRANS_MASK_REGION_APP_NAME,
		*TRANS_MASK_REGION_SOURCE_ID_KEY;
	//

	int sourceTaskID;
};

struct LayerColorChannel
{
	//ConfigDetails
	static char *COLOR_CHANNEL_APP_NAME,
		*COLOR_CHANNEL_NAME_KEY, *COLOR_CHANNEL_TYPE_KEY;
	//

	bool isEnabled = true;
	std::string name = "";
	ColorChannelType typeOfChannel;
};

class  LayerData : public InspectionData
{

	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME,
		*INSPECTION_WINDOW_KEY, *RESOLUTION_FACTOR_KEY, *COLOR_CHANNEL_COUNT_KEY, *ANCHOR_REGION_DIR_KEY,
		*INSP_REG_COUNT_KEY, *MASK_REG_COUNT_KEY, *STATI_REG_COUNT_KEY, *TRANS_MASK_REG_COUNT_KEY,
		*MAX_IMAGE_KEY, *MIN_IMAGE_KEY, *RANK_IMAGE_KEY, *ROW_REF_KEY, *COLUMN_REF_KEY, *ANGLE_REF_KEY;
	//
public:
	HRegion inspectionWindow;
	double ResolutionFactorToProcess;

	bool isEnabled = true;
	LayerColorChannel colorChannel[MAX_NUM_OF_COLOR_CHANNELS];
	LayerAnchorRegion anchorRegions;

	std::map<UINT, LayerInspectionRegion> insRegions;
	std::map<UINT, LayerRegion> maskRegions;
	std::map<UINT, LayerRegion> statisticsRegions;
	std::vector<UINT> sourceMaskID;

	HImage maxImage, minImage, rankImage;
	HTuple rowRef;
	HTuple columnRef;
	HTuple angleRef;

	void UpdateAnchorRefLocations(HImage masterImage);

	virtual bool ResetMinMaxData();

	virtual void ReadConfiguration(std::string folderName);
	virtual void WriteConfiguration(std::string folderName);
};

class MeasurementPoint
{
public:
	LayerAnchorRegion tpData;
	HTuple row, column, rowRef, columnRef, angleRef;
	HRegion measurementPointRegion;

	void UpdateRefLocations(HTuple _rowRef, HTuple _columnRef, HTuple _angleRef)
	{
		rowRef = _rowRef;
		columnRef = _columnRef;
		angleRef = _angleRef;
	}
};

class MeasurementParam
{
public:
	double nominalDistance, lowerTolerance, upperTolerance;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			CEREAL_NVP(nominalDistance),
			CEREAL_NVP(lowerTolerance),
			CEREAL_NVP(upperTolerance)
		);
	}
};

class Measurement
{
	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME, *P1_ROW_KEY, *P1_COLUMN_KEY, *P1_ROW_REF_KEY, *P1_COLUMN_REF_KEY, *P1_ANGLE_REF_KEY, *P1_REGION, *P1_DIRECTORY_KEY,
		*P2_ROW_KEY, *P2_COLUMN_KEY, *P2_ROW_REF_KEY, *P2_COLUMN_REF_KEY, *P2_ANGLE_REF_KEY, *P2_REGION, *P2_DIRECTORY_KEY, *VERTICAL_NOMINAL_VALUE, *HORIZONTAL_NOMINAL_VALUE,
		*MEASURE_VERTICAL_LOW_TOL_KEY, *MEASURE_VERTICAL_UP_TOL_KEY,  *MEASURE_HORIZONTAL_LOW_TOL_KEY, *MEASURE_HORIZONTAL_UP_TOL_KEY;
public:
	//
	MeasurementPoint firstMeasurementPoint, secondMeasurementPoint;
	/*double horizontalNominalDistance, verticalNominalDistance;
	double verticalMeasureTollerance, horizontalMeasureTollerance;*/
	MeasurementParam vertical, horizontal;

	void UpdateMeasurementPointsRefLocation(HTuple _rowRef, HTuple _columnRef, HTuple _angleRef, UINT _sourceTaskID);

	void ReadConfiguration(std::string folderName);
	void WriteConfiguration(std::string folderName);

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			CEREAL_NVP(vertical),
			CEREAL_NVP(horizontal)
		);
	}


};

class  MeasurementData : public InspectionData
{
	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME, *NO_OF_MEASUREMENTS_KEY;
	//
public:
	//double horizontalMeasureTollerance, verticalMeasureTollerance;
	RegionTypes regType = MeasurementRegion;
	bool isEnabled = true;
	std::vector<Measurement> measurementList;
	virtual void ReadConfiguration(std::string folderName);
	virtual void WriteConfiguration(std::string folderName);
};

class  ThreadData : public InspectionData
{
	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME, *INSPECTION_WINDOW_KEY, *THREAD_PATTERN_REGION_COUNT_KEY, *THREAD_PATTERN_REGION_KEY,
		*THREAD_SEARCH_REGION_COUNT_KEY, *THREAD_SEARCH_REGION_KEY,  *IS_THREAD_WINDOWING_CHECK_REQUIRED, *THREAD_WINDOW_COUNT_PER_COLUMN_KEY,
		*DYNAMIC_THRESHOLD_VALUE_KEY, *IMAGE_SCALE_FACTOR_KEY;
	//
public:

	bool isEnabled = true;
	std::vector<HRegion> threadPatternRegions;
	std::vector<HRegion> threadSearchWindows;
	RegionTypes regType;
	HRegion inspectionWindow;
	int noOfThreadColumns;
	bool isThreadWindowingCheckRequired;
	int noOfThreadWindowsPerColumn;

	double dynamicThresholdValue;
	double imageScaleFactor;

	virtual void ReadConfiguration(std::string  folderName);
	virtual void WriteConfiguration(std::string folderName);
};

class  BlobAnalyzerData : public InspectionData
{
	//ConfigDetails
	static char *CONFIG_NAME, *APP_NAME, *BLOB_PARAMETERS_GROUP_ID, *NUMBER_OF_LAYER_TASKS, *SOURCE_LAYER_TASK_ID, *UP_WISE_PARTITION_REGION, *IMAGE_WIDTH, *IMAGE_HEIGHT;
	//
public:

	virtual void ReadConfiguration(std::string folderName);
	virtual void WriteConfiguration(std::string folderName);
	BlobParametersGroups blopParametersGroupID;
	vector<int> layerInspectionTaskID;
	HRegion UpWisePartation;
	UINT imageWidth, imageHeight;
};

class CameraData : public InspectionData
{
	static char *CONFIG_NAME, *APP_NAME, *CAMERA_ID, *MASTER_IMAGE_FILE, *MASTER_IR_IMAGE_FILE, *MASTER_IMAGE_REDUCED_FILE,
		*INSPECTION_WINDOW_FILE, *REP_ANCHOR_DIR_KEY, *NUMBER_OF_UPS, *NUMBER_OF_PANELS, *NUMBER_OF_TASKS, *TASK_FILE,
		*TASK_TYPE, *TASK_ID,*TASK_NAME, *TS_COUNT, *TS_NUMBER, *TS_ADDEDTIME, *TS_ISTRAINED, *TS_TYPE, *TS_FILE, *TS_MASK_FILE, *REP_ROW_REF_KEY,
		*REP_COLUMN_REF_KEY, *REP_ANGLE_REF_KEY, *REP_ROW_ALL_KEY, *REP_COLUMN_ALL_KEY, *REP_ANGLE_ALL_KEY;
public:
	CameraData();
	~CameraData();

	int cameraID;
	bool isMasterImageInitialized;
	HImage masterImage, masterImageReduced;
	HImage masterIRImage;
	HRegion InspectionWindow;
	int  numberOfUps, numberOfPanels;
	std::map < UINT, InspectionData *> inspectionTasks;
	std::vector<TrainingImageData> thisCameraTrainingSet;

	LayerAnchorRegion repAnchor;
	HTuple repRowRef;
	HTuple repColumnRef;
	HTuple repAngleRef;
	HTuple repRowAll;
	HTuple repColumnAll;
	HTuple repAngleAll;

	void SetSheetDetails(int _numberOfColumns, int _numberOfUps);

	LayerInspectionRegion AddInspectionRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType, SensitivityLevels underInkingSensitivity, SensitivityLevels overInkingSensitivity);
	LayerRegion AddMaskRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType);
	LayerRegion AddStatisticsRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType);
	bool DeleteRegion(UINT _layerID, UINT _regID);

	bool AddLayer(LayerData *layerData);
	bool RemoveLayer(UINT taskID);
	int GetLayersCount();
	UINT GetNextAvailableLayerID();
	void AddTransferMaskForLayers(UINT maskID);
	void RemoveTransferMaskForLayers(UINT maskID);

	LayerData *GetLayer(UINT taskID);
	ThreadData *GetThread();
	MeasurementData *GetMeasurement();
	BlobAnalyzerData *GetBlobAnalyzer();


	UINT GetNextAvailableInspectionRegionID(UINT _layerID);
	UINT GetNextAvailableMaskRegionID(UINT _layerID);
	UINT GetNextAvailableStatisticsRegionID(UINT _layerID);

	int GetInspectionRegionCount(UINT _layerID);
	int GetMaskRegionCount(UINT _layerID);
	int GetStatisticsRegionCount(UINT _layerID);

	int GetInspectionRegionIndex(UINT _layerID, UINT _regID);
	int GetMaskRegionIndex(UINT _layerID, UINT _regID);
	int GetStatisticsRegionIndex(UINT _layerID, UINT _regID);
	int GetAnyRegionIndex(UINT _layerID, RegionTypes regType, UINT _regID);

	RegionTypes GetRegionType(UINT _layerID, UINT _regID);

	void UpdatUnderInkingSensitivity(UINT _layerID, UINT _regID, SensitivityLevels _uiSensitivity);
	void UpdatOverInkingSensitivity(UINT _layerID, UINT _regID, SensitivityLevels _oiSensitivity);

	void SetInspectionWindowToLayers();
	void SetInspectionWindowToThreadInspection();
	void SetInspectionWindowToBlobAnalyzer();

	void ResetLayerImages();

	void ReadConfiguration(std::string folderName, bool ReadTrainingSet = true);
	void WriteConfiguration(std::string folderName);	
};

class GoldenData
{
	static char *CONFIG_NAME, *APP_NAME, *GOLDEN_NAME, *NUMBER_OF_UPS, *NUMBER_OF_PANELS, *TS_COUNT, *NUMBER_OF_CAMERAS, *CAMERA_FILE, *CAMERA_ID;
public:
	GoldenData();
	~GoldenData();


	std::string goldenName;
	int numberOfUps;
	int numberOfPanels;
	int trainingSetCount;
	int numberOfCameras;


	std::map < UINT, string> allCameraDataLocation;
	std::map < UINT, CameraData> allCameraData;


	GoldenData(std::string &_goldenName, int _numberOfUps, int _numberOfPanels, int _numberOfCameras);
	bool isMasterAssigned(UINT _cameraID);
	bool SetMaster(UINT _cameraID, HImage &masterNote, HImage &irImage);
	bool RemoveMaster(UINT _cameraID);	
	void SetGoldenData(std::string &_goldenName, int _numberOfUps, int _numberOfPanels, int _numberOfCameras);


	void AddTrainingSet(UINT _cameraID, ImageData &_imageData, TrainingSetType _type);
	void AddTrainingSet(UINT _cameraID, TrainingImageData &_imageData);
	int GetTrainingSetCount(UINT _cameraID);
	HImage GetTraingSetImage(UINT _cameraID, UINT _imageIndex, HImage &_irTrainingImage);
	int RemoveTrainingSet(UINT _cameraID, UINT _imageIndex);

	bool ResetTrainingData(UINT _cameraID);

	void ReadConfiguration(std::string _folderName, bool ReadTrainingSet = true);
	void WriteConfiguration(std::string _folderName);
};

class NewGoldenDetails
{
public:
	std::string goldenName;
	UINT numberOfUps, numberOfPanels;
	NewGoldenDetails();
	~NewGoldenDetails();
};

