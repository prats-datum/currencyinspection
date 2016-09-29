#include "stdafx.h"
#include "GoldenData.h"
#include "ApplicationSettingsReader.h"


char* LayerColorChannel::COLOR_CHANNEL_APP_NAME = "Layer_Color_Channel";
char* LayerColorChannel::COLOR_CHANNEL_NAME_KEY = "Channel_Name";
char* LayerColorChannel::COLOR_CHANNEL_TYPE_KEY = "Channel_Type";

char* LayerTransferMaskRegion::TRANS_MASK_REGION_APP_NAME = "Transfer_Mask_Region";
char* LayerTransferMaskRegion::TRANS_MASK_REGION_SOURCE_ID_KEY = "Source_Task_ID";

char* LayerRegion::LAYER_REGION_APP_NAME = "Layer_Region";
char* LayerRegion::LAYER_REGION_ID_KEY = "Region_ID";
char* LayerRegion::LAYER_REGION_NAME_KEY = "Region_Name";
char* LayerRegion::LAYER_REGION__KEY = "Region_File";
char* LayerRegion::LAYER_REGION_REP_KEY = "Region_Repiting_File";
char* LayerRegion::LAYER_REGION_INSP_TYPE_KEY = "Region_Type";
char* LayerRegion::LAYER_REGION_COUNT_KEY = "Region_Count";
char* LayerRegion::MASK_REGION_APP_NAME = "Layer_Mask_Region";
char* LayerRegion::STATISTICS_REGION_APP_NAME = "Layer_Statistics_Region";

char* LayerInspectionRegion::INSP_REGION_APP_NAME = "Layer_Inspection_Region";
char* LayerInspectionRegion::INSP_OVER_INK_KEY = "Over_Ink_Sensitivity";
char* LayerInspectionRegion::INSP_UNDER_INK_KEY = "Under_Ink_Sensitivity";

char* LayerAnchorRegion::CONFIG_NAME = "LayerAnchorRegion.ini";
char* LayerAnchorRegion::APP_NAME = "Layer_Anchor_Region_Details";
char* LayerAnchorRegion::SEARCH_TYPE_KEY = "Search_Type";
char* LayerAnchorRegion::ANCHOR_COUNT_KEY = "Anchor_Region_Count";
char* LayerAnchorRegion::ANCHOR_REG_KEY = "Anchor_Region";
char* LayerAnchorRegion::NCC_COUNT_KEY = "Ncc_Model_Count";
char* LayerAnchorRegion::NCC_MODEL_KEY = "Ncc_Model";
char* LayerAnchorRegion::SHAPE_COUNT_KEY = "Shape_Model_Count";
char* LayerAnchorRegion::SHAPE_MODEL_KEY = "Shape_Model";
char* LayerAnchorRegion::SOURCE_ID_COUNT_KEY = "Source_Task_Count";
char* LayerAnchorRegion::SOURCE_ID_KEY = "Source_Task_ID";

char* LayerData::CONFIG_NAME = "LayerData.ini";
char* LayerData::APP_NAME = "Layer_Data_Details";
char* LayerData::INSPECTION_WINDOW_KEY = "Layer_Inspection_Window_File";
char* LayerData::RESOLUTION_FACTOR_KEY = "Resolution_Factor";
char* LayerData::ANCHOR_REGION_DIR_KEY = "Anchor_Region_DIR";
char* LayerData::INSP_REG_COUNT_KEY = "Inspect_Region_Count";
char* LayerData::MASK_REG_COUNT_KEY = "Mask_Region_Count";
char* LayerData::STATI_REG_COUNT_KEY = "Statistic_Region_Count";
char* LayerData::TRANS_MASK_REG_COUNT_KEY = "Transfer_Mask_Region_Count";
char* LayerData::MAX_IMAGE_KEY = "Max_Image";
char* LayerData::MIN_IMAGE_KEY = "Min_Image";
char* LayerData::RANK_IMAGE_KEY = "Rank_Image";
char* LayerData::ROW_REF_KEY = "Row_Ref";
char* LayerData::COLUMN_REF_KEY = "Column_Ref";
char* LayerData::ANGLE_REF_KEY = "Angle_Ref";

char* MeasurementData::CONFIG_NAME = "MeasurementData.ini";
char* MeasurementData::APP_NAME = "Measurement_Data_Details";
char* MeasurementData::NO_OF_MEASUREMENTS_KEY = "No_Of_Measurements";

char* Measurement::CONFIG_NAME = "Measurement.ini";
char* Measurement::APP_NAME = "Measurement_Details";
char* Measurement::P1_ROW_KEY = "P1_Row";
char* Measurement::P1_COLUMN_KEY = "P1_Column";
char* Measurement::P1_ROW_REF_KEY = "P1_Row_Ref";
char* Measurement::P1_COLUMN_REF_KEY = "P1_Column_Ref";
char* Measurement::P1_DIRECTORY_KEY = "P1_Directory";
char* Measurement::P1_ANGLE_REF_KEY = "P1_Angle_Ref";
char* Measurement::P1_REGION = "P1_Region";
char* Measurement::P2_ROW_KEY = "P2_Row";
char* Measurement::P2_COLUMN_KEY = "P2_Column";
char* Measurement::P2_ROW_REF_KEY = "P2_Row_Ref";
char* Measurement::P2_COLUMN_REF_KEY = "P2_Column_Ref";
char* Measurement::P2_ANGLE_REF_KEY = "P2_Angle_Ref";
char* Measurement::P2_REGION = "P2_Region";
char* Measurement::P2_DIRECTORY_KEY = "P2_Directory";
char* Measurement::VERTICAL_NOMINAL_VALUE = "Vertical_Nominal_Value";
char* Measurement::HORIZONTAL_NOMINAL_VALUE = "Horizaontal_Nominal_Value";
char* Measurement::MEASURE_VERTICAL_LOW_TOL_KEY = "Vertical_Lower_Tolerance";
char* Measurement::MEASURE_VERTICAL_UP_TOL_KEY = "Vertical_Upper_Tolerance";
char* Measurement::MEASURE_HORIZONTAL_LOW_TOL_KEY = "Horizontal_Lower_Tolerance";
char* Measurement::MEASURE_HORIZONTAL_UP_TOL_KEY = "Horizontal_Upper_Tolerance";

char* ThreadData::CONFIG_NAME = "ThreadData.ini";
char* ThreadData::APP_NAME = "Thread_Data_Details";
char* ThreadData::INSPECTION_WINDOW_KEY = "Inspection_Window";
char* ThreadData::THREAD_PATTERN_REGION_COUNT_KEY = "Thread_Pattern_Region_Count";
char* ThreadData::THREAD_PATTERN_REGION_KEY = "Thread_Pattern_Region";
char* ThreadData::THREAD_SEARCH_REGION_COUNT_KEY = "Thread_Search_Region_Count";
char* ThreadData::THREAD_SEARCH_REGION_KEY = "Thread_Search_Region";
char* ThreadData::IS_THREAD_WINDOWING_CHECK_REQUIRED = "Is_Thread_Windowing_Check_Required";
char* ThreadData::THREAD_WINDOW_COUNT_PER_COLUMN_KEY = "Thread_Window_Count_Per_Column";
char* ThreadData::IMAGE_SCALE_FACTOR_KEY = "Image_Scale_Factor";
char* ThreadData::DYNAMIC_THRESHOLD_VALUE_KEY = "Dynamic_Threshold_Value";



char* BlobAnalyzerData::CONFIG_NAME = "BlobAnalyzerData.ini";
char* BlobAnalyzerData::APP_NAME = "Blob_Analyzer_Details";
char* BlobAnalyzerData::BLOB_PARAMETERS_GROUP_ID = "Blob_Parameters_Group_ID";
char* BlobAnalyzerData::NUMBER_OF_LAYER_TASKS = "Number_Of_Layer_Tasks";
char* BlobAnalyzerData::SOURCE_LAYER_TASK_ID = "Source_Layer_Task_ID";
char* BlobAnalyzerData::UP_WISE_PARTITION_REGION = "Up_Wise_Partition_Region";
char* BlobAnalyzerData::IMAGE_WIDTH = "Image_Width";
char* BlobAnalyzerData::IMAGE_HEIGHT = "Image_Height";



char* GoldenData::CONFIG_NAME = "GoldenData.ini";
char* GoldenData::APP_NAME = "GoldenDetails";
char* GoldenData::GOLDEN_NAME = "GoldenName";
char* GoldenData::NUMBER_OF_CAMERAS = "NumberOfCameras";
char* GoldenData::NUMBER_OF_UPS = "NumberOfUps";
char* GoldenData::NUMBER_OF_PANELS = "NumberOfPanels";
char* GoldenData::TS_COUNT = "TrainingSetCount";
char* GoldenData::CAMERA_FILE = "Camera_Folder";
char* GoldenData::CAMERA_ID = "Camera_ID";

char* CameraData::CONFIG_NAME = "CameraData.ini";
char* CameraData::APP_NAME = "CameraDetails";
char* CameraData::CAMERA_ID = "CameraID";
char* CameraData::MASTER_IMAGE_FILE = "MasterImageFile";
char* CameraData::MASTER_IR_IMAGE_FILE = "MasterIRImageFile";

char* CameraData::MASTER_IMAGE_REDUCED_FILE = "MasterImageReducedFile";
char* CameraData::INSPECTION_WINDOW_FILE = "InspectionWindowFile";
char* CameraData::REP_ANCHOR_DIR_KEY = "Rep_Anchor_DIR";
char* CameraData::REP_ROW_REF_KEY = "Rep_Row_Ref";
char* CameraData::REP_COLUMN_REF_KEY = "Rep_Column_Ref";
char* CameraData::REP_ANGLE_REF_KEY = "Rep_Angle_Ref";
char* CameraData::REP_ROW_ALL_KEY = "Rep_Row_All";
char* CameraData::REP_COLUMN_ALL_KEY = "Rep_Column_All";
char* CameraData::REP_ANGLE_ALL_KEY = "Rep_Angle_All";
char* CameraData::NUMBER_OF_UPS = "NumberOfUps";
char* CameraData::NUMBER_OF_PANELS = "NumberOfPanels";
char* CameraData::NUMBER_OF_TASKS = "NumberOfTasks";
char* CameraData::TASK_FILE = "TaskFile";
char* CameraData::TASK_TYPE = "TaskType";
char* CameraData::TASK_ID = "TaskID";
char* CameraData::TASK_NAME = "TaskName";
char* CameraData::TS_COUNT = "TrainingSetCount";
char* CameraData::TS_NUMBER = "TrainingSetNumber";
char* CameraData::TS_TYPE = "TrainingSetType";
char* CameraData::TS_ADDEDTIME = "TrainingSetAddedTime";
char* CameraData::TS_ISTRAINED = "TrainingSetIsTrained";
char* CameraData::TS_FILE = "TrainingSetFile";
char* CameraData::TS_MASK_FILE = "TrainingSetMaskFile";




HRegion LayerAnchorRegion::GetRemainingRegion(HRegion &tempRegion)
{
	HRegion remainingRegion;
	remainingRegion.GenEmptyObj();
	std::vector<HRegion>::iterator iter;
	for (iter = regionList.begin(); iter != regionList.end(); ++iter)
	{
		if (!(*iter).TestEqualObj(tempRegion))
		{
			remainingRegion = remainingRegion.ConcatObj((*iter));
		}
	}
	return remainingRegion;
}

void LayerAnchorRegion::CreateModel(HImage masterImageReduced)
{
	HImage fullImage = masterImageReduced;
	if (fullImage.CountChannels() == 3)
	{
		fullImage = fullImage.Rgb1ToGray();
	}
	if (searchType == ShapeBased)
	{
		shapeModelList.clear();
		int index = 0;
		for (auto &e : regionList)
		{
			HShapeModel tempShapeModel;
			HImage tempImage = fullImage.ReduceDomain(e);
			tempShapeModel.CreateShapeModel(tempImage, NumLevels, AngleStart, AngleExtent, AngleStep, Optimization, Metric, Contrast, MinContrast);
			shapeModelList.push_back(tempShapeModel);
			index++;
		}
	}
	else
	{
		nccModelList.clear();
		int index = 0;
		for (auto &e : regionList)
		{
			HNCCModel tempNCCModel;
			HImage tempImage = fullImage.ReduceDomain(e);
			tempNCCModel.CreateNccModel(tempImage, NumLevels, AngleStart, AngleExtent, AngleStep, Metric);
			nccModelList.push_back(tempNCCModel);
			index++;
		}
	}
}

void LayerAnchorRegion::ReadConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	//taskID
	regID = taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID_KEY, 0, configFileName);
	//taskType
	typeOfInspectionTask = (InspectionTypes)(GetPrivateProfileIntA(APP_NAME, TASK_TYPE_KEY, 0, configFileName));
	//regType
	regType = (RegionTypes)GetPrivateProfileIntA(APP_NAME, REGION_TYPE, 0, configFileName);
	//searchType
	int searchTypeValue = GetPrivateProfileIntA(APP_NAME, SEARCH_TYPE_KEY, 0, configFileName);
	searchType = (SearchType)searchTypeValue;
	//regionList
	regionList.clear();
	int anchorRegCount = GetPrivateProfileIntA(APP_NAME, ANCHOR_COUNT_KEY, 0, configFileName);
	if (anchorRegCount > 0)
	{
		for (int anchorID = 1; anchorID <= anchorRegCount; anchorID++)
		{
			std::string anchorRegKey = std::string(ANCHOR_REG_KEY) + std::to_string(anchorID);
			char anchorFileName[300];
			GetPrivateProfileStringA(APP_NAME, anchorRegKey.c_str(), NULL, anchorFileName, 300, configFileName);
			if (*anchorFileName != NULL)
			{
				std::string anchorFileNamePath = folderName + '\\' + anchorFileName;
				HRegion anchorReg;
				anchorReg.ReadRegion(anchorFileNamePath.c_str());
				regionList.push_back(anchorReg);
			}
		}
	}
	//nccModelList
	nccModelList.clear();
	int nccCount = GetPrivateProfileIntA(APP_NAME, NCC_COUNT_KEY, 0, configFileName);
	if (nccCount > 0)
	{
		for (int nccID = 1; nccID <= nccCount; nccID++)
		{
			std::string nccModelKey = std::string(NCC_MODEL_KEY) + std::to_string(nccID);
			char nccFileName[300];
			GetPrivateProfileStringA(APP_NAME, nccModelKey.c_str(), NULL, nccFileName, 300, configFileName);
			if (*nccFileName != NULL)
			{
				std::string nccFileNamePath = folderName + '\\' + nccFileName;
				HNCCModel nccModel;
				nccModel.ReadNccModel(nccFileNamePath.c_str());
				nccModelList.push_back(nccModel);
			}
		}
	}
	//shapeModelList
	shapeModelList.clear();
	int shapeCount = GetPrivateProfileIntA(APP_NAME, SHAPE_COUNT_KEY, 0, configFileName);
	if (shapeCount > 0)
	{
		for (int shapeID = 1; shapeID <= shapeCount; shapeID++)
		{
			std::string shapeModelKey = std::string(SHAPE_MODEL_KEY) + std::to_string(shapeID);
			char shapeFileName[300];
			GetPrivateProfileStringA(APP_NAME, shapeModelKey.c_str(), NULL, shapeFileName, 300, configFileName);
			if (*shapeFileName != NULL)
			{
				std::string shapeFileNamePath = folderName + '\\' + shapeFileName;
				HShapeModel shapeModel;
				shapeModel.ReadShapeModel(shapeFileNamePath.c_str());
				shapeModelList.push_back(shapeModel);
			}
		}
	}
	//SourceTaskList
	sourceTaskIDList.clear();
	int sourceTaskIDCount = GetPrivateProfileIntA(APP_NAME, SOURCE_ID_COUNT_KEY, 0, configFileName);
	if (sourceTaskIDCount > 0)
	{
		for (int sourceTaskIDIndex = 1; sourceTaskIDIndex <= sourceTaskIDCount; sourceTaskIDIndex++)
		{
			std::string sourceTaskIDKey = std::string(SOURCE_ID_KEY) + std::to_string(sourceTaskIDIndex);			
			sourceTaskIDList.push_back((UINT)(GetPrivateProfileIntA(APP_NAME, sourceTaskIDKey.c_str(), NULL, configFileName)));
		}
	}
}
void LayerAnchorRegion::WriteConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//taskID
	std::string taskIDValue = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID_KEY, taskIDValue.c_str(), configFileName);
	//taskType
	std::string taskTypeValue = std::to_string(typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE_KEY, taskTypeValue.c_str(), configFileName);
	//searchType
	std::string searchTypeValue = std::to_string((int)searchType);
	WritePrivateProfileStringA(APP_NAME, SEARCH_TYPE_KEY, searchTypeValue.c_str(), configFileName);
	//regType
	std::string regTypeString = std::to_string(regType);
	WritePrivateProfileStringA(APP_NAME, REGION_TYPE, regTypeString.c_str(), configFileName);
	//regionList
	int anchorRegCount = regionList.size();
	std::string anchorCountValue = std::to_string(anchorRegCount);
	WritePrivateProfileStringA(APP_NAME, ANCHOR_COUNT_KEY, anchorCountValue.c_str(), configFileName);
	if (anchorRegCount > 0)
	{
		for (int anchorID = 1; anchorID <= anchorRegCount; anchorID++)
		{
			if (regionList[anchorID - 1].IsInitialized())
			{
				std::string anchorFileName = "AnchorRegion_" + std::to_string(anchorID) + ".reg";
				std::string anchorRegKey = std::string(ANCHOR_REG_KEY) + std::to_string(anchorID);
				WritePrivateProfileStringA(APP_NAME, anchorRegKey.c_str(), anchorFileName.c_str(), configFileName);

				std::string anchorFileNamePath = folderName + '\\' + anchorFileName;
				regionList[anchorID - 1].WriteRegion(anchorFileNamePath.c_str());
			}
		}
	}
	//nccModelList
	int nccCount = nccModelList.size();
	std::string nccCountValue = std::to_string(nccCount);
	WritePrivateProfileStringA(APP_NAME, NCC_COUNT_KEY, nccCountValue.c_str(), configFileName);
	if (searchType == SearchType::GrayValueBased)
	{
		if (nccCount > 0)
		{
			for (int nccID = 1; nccID <= nccCount; nccID++)
			{
				if (nccModelList[nccID - 1].IsHandleValid())
				{
					std::string nccFileName = "NccModel_" + std::to_string(nccID);
					std::string nccModelKey = std::string(NCC_MODEL_KEY) + std::to_string(nccID);
					WritePrivateProfileStringA(APP_NAME, nccModelKey.c_str(), nccFileName.c_str(), configFileName);

					std::string nccFileNamePath = folderName + '\\' + nccFileName;
					nccModelList[nccID - 1].WriteNccModel(nccFileNamePath.c_str());
				}
			}
		}
	}
	//shapeModelList
	int shapeCount = shapeModelList.size();
	std::string shapeCountValue = std::to_string(shapeCount);
	WritePrivateProfileStringA(APP_NAME, SHAPE_COUNT_KEY, shapeCountValue.c_str(), configFileName);
	if (searchType == SearchType::ShapeBased)
	{
		if (shapeCount > 0)
		{
			for (int shapeID = 1; shapeID <= shapeCount; shapeID++)
			{
				if (shapeModelList[shapeID - 1].IsHandleValid())
				{
					std::string shapeFileName = "ShapeModel_" + std::to_string(shapeID);
					std::string shapeModelKey = std::string(SHAPE_MODEL_KEY) + std::to_string(shapeID);
					WritePrivateProfileStringA(APP_NAME, shapeModelKey.c_str(), shapeFileName.c_str(), configFileName);

					std::string shapeFileNamePath = folderName + '\\' + shapeFileName;
					shapeModelList[shapeID - 1].WriteShapeModel(shapeFileNamePath.c_str());
				}
			}
		}
	}
	//SourceTaskList
	int sourceTaskIDCount = sourceTaskIDList.size();
	WritePrivateProfileStringA(APP_NAME, SOURCE_ID_COUNT_KEY, std::to_string(sourceTaskIDCount).c_str(), configFileName);
	if (searchType == SearchType::SourceTaskBased)
	{
		if (sourceTaskIDCount > 0)
		{
			for (int sourceTaskIDIndex = 1; sourceTaskIDIndex <= sourceTaskIDCount; sourceTaskIDIndex++)
			{
					std::string sourceTaskIDKey = std::string(SOURCE_ID_KEY) + std::to_string(sourceTaskIDIndex);
					WritePrivateProfileStringA(APP_NAME, sourceTaskIDKey.c_str(), std::to_string(sourceTaskIDList[sourceTaskIDIndex - 1]).c_str(), configFileName);
			}
		}
	}
}

HRegion LayerRegion::GetRegion()
{
	HRegion tempRegion;
	tempRegion.GenEmptyObj();
	for (auto&e : regionList)
	{
		tempRegion = tempRegion.ConcatObj(e);
	}
	return tempRegion;
}

void LayerData::UpdateAnchorRefLocations(HImage masterImage)
{
	HImage temp = masterImage.ReduceDomain(inspectionWindow);
	temp = temp.CropDomain();
	if (temp.CountChannels() == 3)
	{
		temp = temp.Rgb1ToGray();
	}
	rowRef.Clear();
	columnRef.Clear();
	angleRef.Clear();
	if (anchorRegions.searchType == ShapeBased)
	{
		int index = 0;
		for (auto &e : anchorRegions.regionList)
		{
			HTuple tempRow, tempColumn, tempAngle, tempScore;
			temp.ReduceDomain(e).FindShapeModel(anchorRegions.shapeModelList[index], anchorRegions.AngleStart, anchorRegions.AngleExtent, anchorRegions.MinScore, anchorRegions.NumMatches,
				anchorRegions.MaxOverlap, anchorRegions.SubPixel_ShapeModel, anchorRegions.NumLevels, anchorRegions.Greediness, &tempRow, &tempColumn, &tempAngle, &tempScore);
			rowRef = rowRef.TupleConcat(tempRow);
			columnRef = columnRef.TupleConcat(tempColumn);
			angleRef = angleRef.TupleConcat(tempAngle);
			index++;
		}
	}
	else
	{
		int index = 0;
		for (auto &e : anchorRegions.regionList)
		{
			HTuple tempRow, tempColumn, tempAngle, tempScore;
			temp.ReduceDomain(e).FindNccModel(anchorRegions.nccModelList[index], anchorRegions.AngleStart, anchorRegions.AngleExtent, anchorRegions.MinScore, anchorRegions.NumMatches,
				anchorRegions.MaxOverlap, anchorRegions.SubPixel_NCCModel, anchorRegions.NumLevels, &tempRow, &tempColumn, &tempAngle, &tempScore);
			rowRef = rowRef.TupleConcat(tempRow);
			columnRef = columnRef.TupleConcat(tempColumn);
			angleRef = angleRef.TupleConcat(tempAngle);
			index++;
		}
	}
}

bool LayerData::ResetMinMaxData()
{
	Hlong row1, row2, column1, column2;
	HImage tempImage, goldenImageTemplate;
	int numberOfChannels = MAX_NUM_OF_COLOR_CHANNELS;
	inspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
	tempImage.GenImageConst("byte", (column2 - column1 + 1), (row2 - row1 + 1));
	tempImage = tempImage.ZoomImageFactor(ResolutionFactorToProcess, ResolutionFactorToProcess, "weighted");
	HImage darkImage = tempImage.GenImageProto(0.0);
	HImage brightImage = tempImage.GenImageProto(255.0);
	//minImage.SetGrayval(0, 0, minImage.GetGrayval(0, 0));
	//maxImage.SetGrayval(0, 0, maxImage.GetGrayval(0, 0));
	//rankImage.SetGrayval(0, 0, rankImage.GetGrayval(0, 0));

	maxImage = darkImage;
	rankImage = darkImage;
	minImage = brightImage;

	//for (int i = 1; i < numberOfChannels; i++)
	//{
	//	maxImage = maxImage.AppendChannel(darkImage.CopyImage());
	//	minImage = minImage.AppendChannel(brightImage.CopyImage());
	//}
	for (int i = 1; i < numberOfChannels; i++)
	{
		maxImage = maxImage.ConcatObj(darkImage.CopyImage());
		minImage = minImage.ConcatObj(brightImage.CopyImage());
	}
	return true;
}


void LayerData::ReadConfiguration(std::string folderName)
{

	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	HRegion tempReadRegion;

	//taskID
	taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID_KEY, 0, configFileName);
	//taskType
	typeOfInspectionTask = InspectionTypes(GetPrivateProfileIntA(APP_NAME, TASK_TYPE_KEY, 0, configFileName));
	//layerName
	char taskNameValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, TASK_NAME_KEY, NULL, taskNameValue, MAX_PATH_LENGTH, configFileName);
	taskName = taskNameValue;
	//isEnabled
	isEnabled = GetPrivateProfileIntA(APP_NAME, ENABLED_KEY, 0, configFileName);
	//ResolutionFactorToProcess
	char processResolutionValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, RESOLUTION_FACTOR_KEY, NULL, processResolutionValue, MAX_PATH_LENGTH, configFileName);
	ResolutionFactorToProcess = atof(processResolutionValue);

	char layerWindowRegionFile[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_KEY, NULL, layerWindowRegionFile, MAX_PATH_LENGTH, configFileName);
	if (*layerWindowRegionFile != NULL)
	{
		std::string layerRegFileNamePath = folderName + '\\' + layerWindowRegionFile;
		inspectionWindow.ReadRegion(layerRegFileNamePath.c_str());
	}

	//colorChannel
	for (int channelID = 1; channelID <= MAX_NUM_OF_COLOR_CHANNELS; channelID++)
	{
		std::string CHANNEL_APP_NAME = std::string(LayerColorChannel::COLOR_CHANNEL_APP_NAME) + std::to_string(channelID);

		//isEnabled
		colorChannel[channelID - 1].isEnabled = GetPrivateProfileIntA(CHANNEL_APP_NAME.c_str(), ENABLED_KEY, 0, configFileName);
		//name
		char channelNameValue[300];
		GetPrivateProfileStringA(CHANNEL_APP_NAME.c_str(), LayerColorChannel::COLOR_CHANNEL_NAME_KEY, NULL, channelNameValue, 300, configFileName);
		colorChannel[channelID - 1].name = channelNameValue;
		//typeOfChannel
		int channelType = GetPrivateProfileIntA(CHANNEL_APP_NAME.c_str(), LayerColorChannel::COLOR_CHANNEL_TYPE_KEY, 0, configFileName);
		colorChannel[channelID - 1].typeOfChannel = (ColorChannelType)channelType;
	}
	//anchorRegions
	char anchorRegDir[300];
	GetPrivateProfileStringA(APP_NAME, ANCHOR_REGION_DIR_KEY, NULL, anchorRegDir, 300, configFileName);
	if (*anchorRegDir != NULL)
	{
		std::string anchorRegDirPath = folderName + '\\' + anchorRegDir;
		anchorRegions.ReadConfiguration(anchorRegDirPath);
	}
	
	//insRegions
	int inspRegCount = GetPrivateProfileIntA(APP_NAME, INSP_REG_COUNT_KEY, 0, configFileName);
	if (inspRegCount > 0)
	{
		for (int inspRegID = 1; inspRegID <= inspRegCount; inspRegID++)
		{
			std::string INSP_REG_APP_NAME = std::string(LayerInspectionRegion::INSP_REGION_APP_NAME) + std::to_string(inspRegID);

			LayerInspectionRegion layerInpReg;
			//regionID
			layerInpReg.regionID = GetPrivateProfileIntA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, 0, configFileName);
			//insRegionType
			int inspType = GetPrivateProfileIntA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, 0, configFileName);
			layerInpReg.insRegionType = (RegionTypes)inspType;
			//regionName
			char layerRegNameValue[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, NULL, layerRegNameValue, MAX_PATH_LENGTH, configFileName);
			layerInpReg.regionName = layerRegNameValue;

			int regionCount = GetPrivateProfileIntA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, 0, configFileName);
			//region
			layerInpReg.regionList.clear();
			for (int index = 0; index < regionCount; index++)
			{
				std::string indexString = std::to_string(index);
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				char layerRegFileName[MAX_PATH_LENGTH];
				GetPrivateProfileStringA(INSP_REG_APP_NAME.c_str(), layerRegionKey.c_str(), NULL, layerRegFileName, MAX_PATH_LENGTH, configFileName);
				HRegion tempRegion;
				if (*layerRegFileName != NULL)
				{
					std::string layerRegFileFolderName = folderName + '\\' + std::string(layerRegFileName);
					tempRegion.ReadRegion(layerRegFileFolderName.c_str());
				}
				else
				{
					tempRegion.GenEmptyRegion();
				}
				layerInpReg.regionList.push_back(tempRegion);
			}

			layerInpReg.repitingPortionList.clear();
			//repitingPortion
			if (layerInpReg.insRegionType == RepititiveInspectionRegion)
			{
				for (int index = 0; index < regionCount; index++)
				{
					//region
					std::string indexString = std::to_string(index);
					std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
					char layerRepRegFileName[MAX_PATH_LENGTH];
					GetPrivateProfileStringA(INSP_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), NULL, layerRepRegFileName, MAX_PATH_LENGTH, configFileName);
					HRegion tempRegion;
					if (layerRepRegFileName != NULL)
					{
						std::string layerRepRegFileFolderName = folderName + '\\' + std::string(layerRepRegFileName);
						tempRegion.ReadRegion(layerRepRegFileFolderName.c_str());
					}
					else
					{
						tempRegion.GenEmptyRegion();
					}
					layerInpReg.repitingPortionList.push_back(tempRegion);
				}
			}
			//underInkingSensitivity
			int underInkValue = GetPrivateProfileIntA(INSP_REG_APP_NAME.c_str(), LayerInspectionRegion::INSP_UNDER_INK_KEY, 0, configFileName);
			layerInpReg.underInkingSensitivity = (SensitivityLevels)underInkValue;
			//overInkingSensitivity
			int overInkValue = GetPrivateProfileIntA(INSP_REG_APP_NAME.c_str(), LayerInspectionRegion::INSP_OVER_INK_KEY, 0, configFileName);
			layerInpReg.overInkingSensitivity = (SensitivityLevels)overInkValue;
			insRegions[layerInpReg.regionID] = layerInpReg;
		}
	}
	//maskRegions
	int maskRegCount = GetPrivateProfileIntA(APP_NAME, MASK_REG_COUNT_KEY, 0, configFileName);
	if (maskRegCount > 0)
	{
		for (int maskRegID = 1; maskRegID <= maskRegCount; maskRegID++)
		{
			std::string MASK_REG_APP_NAME = std::string(LayerRegion::MASK_REGION_APP_NAME) + std::to_string(maskRegID);
			LayerRegion layerReg;
			//regionID
			layerReg.regionID = GetPrivateProfileIntA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, 0, configFileName);
			//insRegionType
			int maskType = GetPrivateProfileIntA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, 0, configFileName);
			layerReg.insRegionType = (RegionTypes)maskType;
			//regionName
			char layerRegNameValue[100];
			GetPrivateProfileStringA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, NULL, layerRegNameValue, 100, configFileName);
			layerReg.regionName = layerRegNameValue;

			int regionCount = GetPrivateProfileIntA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, 0, configFileName);
			//region
			layerReg.regionList.clear();
			for (int index = 0; index < regionCount; index++)
			{
				std::string indexString = std::to_string(index);
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				char layerRegFileName[MAX_PATH_LENGTH];
				GetPrivateProfileStringA(MASK_REG_APP_NAME.c_str(), layerRegionKey.c_str(), NULL, layerRegFileName, MAX_PATH_LENGTH, configFileName);
				HRegion tempRegion;
				if (*layerRegFileName != NULL)
				{
					std::string layerRegFileFolderName = folderName + '\\' + std::string(layerRegFileName);
					tempRegion.ReadRegion(layerRegFileFolderName.c_str());
				}
				else
				{
					tempRegion.GenEmptyRegion();
				}
				layerReg.regionList.push_back(tempRegion);
			}

			layerReg.repitingPortionList.clear();
			//repitingPortion
			if (layerReg.insRegionType == RepititiveMaskRegion)
			{
				for (int index = 0; index < regionCount; index++)
				{
					//region
					std::string indexString = std::to_string(index);
					std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
					char layerRepRegFileName[MAX_PATH_LENGTH];
					GetPrivateProfileStringA(MASK_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), NULL, layerRepRegFileName, MAX_PATH_LENGTH, configFileName);
					HRegion tempRegion;
					if (*layerRepRegFileName != NULL)
					{
						std::string layerRepRegFileFolderName = folderName + '\\' + std::string(layerRepRegFileName);
						tempRegion.ReadRegion(layerRepRegFileFolderName.c_str());
					}
					else
					{
						tempRegion.GenEmptyRegion();
					}
					layerReg.repitingPortionList.push_back(tempRegion);
				}
			}
			maskRegions[layerReg.regionID] = layerReg;
		}
	}
	//statisticsRegions
	int statiRegCount = GetPrivateProfileIntA(APP_NAME, STATI_REG_COUNT_KEY, 0, configFileName);
	if (statiRegCount > 0)
	{
		for (int statiRegID = 1; statiRegID <= statiRegCount; statiRegID++)
		{
			std::string STATI_REG_APP_NAME = std::string(LayerRegion::STATISTICS_REGION_APP_NAME) + std::to_string(statiRegID);

			LayerRegion staticReg;
			//regionID
			staticReg.regionID = GetPrivateProfileIntA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, 0, configFileName);
			//regionName
			char layerRegNameValue[100];
			GetPrivateProfileStringA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, NULL, layerRegNameValue, 100, configFileName);
			staticReg.regionName = layerRegNameValue;
			//insRegionType
			int regType = GetPrivateProfileIntA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, 0, configFileName);
			staticReg.insRegionType = (RegionTypes)regType;


			int regionCount = GetPrivateProfileIntA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, 0, configFileName);
			//region
			staticReg.regionList.clear();
			staticReg.repitingPortionList.clear();
			for (int index = 0; index < regionCount; index++)
			{
				std::string indexString = std::to_string(index);
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				char layerRegFileName[MAX_PATH_LENGTH];
				GetPrivateProfileStringA(STATI_REG_APP_NAME.c_str(), layerRegionKey.c_str(), NULL, layerRegFileName, MAX_PATH_LENGTH, configFileName);
				HRegion tempRegion;
				if (*layerRegFileName != NULL)
				{
					std::string layerRegFileFolderName = folderName + '\\' + std::string(layerRegFileName);
					tempRegion.ReadRegion(layerRegFileFolderName.c_str());
				}
				else
				{
					tempRegion.GenEmptyRegion();
				}
				staticReg.regionList.push_back(tempRegion);

				std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
				char layerRepRegFileName[MAX_PATH_LENGTH];
				GetPrivateProfileStringA(STATI_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), NULL, layerRepRegFileName, MAX_PATH_LENGTH, configFileName);
				HRegion tempRepRegion;
				if (*layerRepRegFileName != NULL)
				{
					std::string layerRepRegFileFolderName = folderName + '\\' + std::string(layerRepRegFileName);
					tempRepRegion.ReadRegion(layerRepRegFileFolderName.c_str());
				}
				else
				{
					tempRepRegion.GenEmptyRegion();
				}
				staticReg.repitingPortionList.push_back(tempRepRegion);
			}

			statisticsRegions[staticReg.regionID] = staticReg;
		}
	}
	//transferMaskRegion
	int transRegCount = GetPrivateProfileIntA(APP_NAME, TRANS_MASK_REG_COUNT_KEY, 0, configFileName);
	if (transRegCount > 0)
	{
		for (int transRegID = 1; transRegID <= transRegCount; transRegID++)
		{
			std::string TRANS_REG_APP_NAME = std::string(LayerTransferMaskRegion::TRANS_MASK_REGION_APP_NAME) + std::to_string(transRegID);
			//regionID
			int sourceTaskID = GetPrivateProfileIntA(TRANS_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, 0, configFileName);
			sourceMaskID.push_back(sourceTaskID);
		}
	}

	//maxImage
	char maxImageFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MAX_IMAGE_KEY, NULL, maxImageFileName, MAX_PATH_LENGTH, configFileName);
	if (*maxImageFileName != NULL)
	{
		std::string maxImageFileNamePath = folderName + '\\' + maxImageFileName;
		maxImage.ReadImage(maxImageFileNamePath.c_str());
	}
	//minImage
	char minImageFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MIN_IMAGE_KEY, NULL, minImageFileName, MAX_PATH_LENGTH, configFileName);
	if (*minImageFileName != NULL)
	{
		std::string minImageFileNamePath = folderName + '\\' + minImageFileName;
		minImage.ReadImage(minImageFileNamePath.c_str());
	}
	//rankImage
	char rankImageFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, RANK_IMAGE_KEY, NULL, rankImageFileName, MAX_PATH_LENGTH, configFileName);
	if (*rankImageFileName != NULL)
	{
		std::string rankImageFileNamePath = folderName + '\\' + rankImageFileName;
		rankImage.ReadImage(rankImageFileNamePath.c_str());
	}

	{//Tuples
	 //rowRef
		char rowRefFileName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(APP_NAME, ROW_REF_KEY, NULL, rowRefFileName, MAX_PATH_LENGTH, configFileName);
		if (*rowRefFileName != NULL)
		{
			std::string rowRefPath = folderName + '\\' + rowRefFileName;
			ReadTuple(rowRefPath.c_str(), &rowRef);
		}
		//columnRef
		char columnRefFileName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(APP_NAME, COLUMN_REF_KEY, NULL, columnRefFileName, MAX_PATH_LENGTH, configFileName);
		if (*columnRefFileName != NULL)
		{
			std::string columnRefPath = folderName + '\\' + columnRefFileName;
			ReadTuple(columnRefPath.c_str(), &columnRef);
		}
		//angleRef
		char angleRefFileName[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(APP_NAME, ANGLE_REF_KEY, NULL, angleRefFileName, MAX_PATH_LENGTH, configFileName);
		if (*angleRefFileName != NULL)
		{
			std::string angleRefPath = folderName + '\\' + angleRefFileName;
			ReadTuple(angleRefPath.c_str(), &angleRef);
		}
	}
}

void LayerData::WriteConfiguration(std::string folderName)
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//taskID
	std::string taskIDValue = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID_KEY, taskIDValue.c_str(), configFileName);
	//taskType
	std::string taskTypeValue = std::to_string(typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE_KEY, taskTypeValue.c_str(), configFileName);
	//layerName
	WritePrivateProfileStringA(APP_NAME, TASK_NAME_KEY, taskName.c_str(), configFileName);
	//isEnabled
	std::string enabledValue = std::to_string((int)isEnabled);
	WritePrivateProfileStringA(APP_NAME, ENABLED_KEY, enabledValue.c_str(), configFileName);
	//ResolutionFactorToProcess
	std::string processResolutionValue = std::to_string(ResolutionFactorToProcess);
	WritePrivateProfileStringA(APP_NAME, RESOLUTION_FACTOR_KEY, processResolutionValue.c_str(), configFileName);

	std::string layerWindowRegionFile = "LayerInspectionWindow.reg";
	WritePrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_KEY, layerWindowRegionFile.c_str(), configFileName);
	std::string layerRegFileNamePath = folderName + '\\' + layerWindowRegionFile;
	inspectionWindow.WriteRegion(layerRegFileNamePath.c_str());

	//colorChannel		
	for (int channelID = 1; channelID <= MAX_NUM_OF_COLOR_CHANNELS; channelID++)
	{
		std::string CHANNEL_APP_NAME = std::string(LayerColorChannel::COLOR_CHANNEL_APP_NAME) + std::to_string(channelID);

		//isEnabled
		enabledValue = std::to_string((int)colorChannel[channelID - 1].isEnabled);
		WritePrivateProfileStringA(CHANNEL_APP_NAME.c_str(), ENABLED_KEY, enabledValue.c_str(), configFileName);
		//name
		WritePrivateProfileStringA(CHANNEL_APP_NAME.c_str(), LayerColorChannel::COLOR_CHANNEL_NAME_KEY, colorChannel[channelID - 1].name.c_str(), configFileName);
		//typeOfChannel
		std::string channelTypeValue = std::to_string((int)colorChannel[channelID - 1].typeOfChannel);
		WritePrivateProfileStringA(CHANNEL_APP_NAME.c_str(), LayerColorChannel::COLOR_CHANNEL_TYPE_KEY, channelTypeValue.c_str(), configFileName);
	}

	//anchorRegions
	std::string anchorRegDir = "anchorRegions_" + std::to_string(anchorRegions.taskID);
	WritePrivateProfileStringA(APP_NAME, ANCHOR_REGION_DIR_KEY, anchorRegDir.c_str(), configFileName);

	std::string anchorRegDirPath = folderName + '\\' + anchorRegDir;
	CreateDirectoryA(anchorRegDirPath.c_str(), NULL);
	anchorRegions.WriteConfiguration(anchorRegDirPath);



	//insRegions
	int inspRegCount = insRegions.size();
	std::string inspRegCountValue = std::to_string(inspRegCount);
	WritePrivateProfileStringA(APP_NAME, INSP_REG_COUNT_KEY, inspRegCountValue.c_str(), configFileName);
	if (inspRegCount > 0)
	{
		int inspRegID = 1;
		for (auto &e : insRegions)
		{
			std::string INSP_REG_APP_NAME = std::string(LayerInspectionRegion::INSP_REGION_APP_NAME) + std::to_string(inspRegID);
			std::string inspRegIDs = std::to_string(inspRegID);

			//regionID
			std::string inspLayerRegIDValue = std::to_string(e.second.regionID);
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, inspLayerRegIDValue.c_str(), configFileName);
			//insRegionType
			std::string layerRegInspTypeValue = std::to_string((int)e.second.insRegionType);
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, layerRegInspTypeValue.c_str(), configFileName);
			//regionName				
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, e.second.regionName.c_str(), configFileName);
			int regionCount = e.second.regionList.size();
			std::string regionCountString = std::to_string(regionCount);
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, regionCountString.c_str(), configFileName);

			//region
			for (int index = 0; index < regionCount; index++)
			{
				std::string indexString = std::to_string(index);
				std::string layerRegFileName = "Insp_LayerRegion_" + inspRegIDs + "_" + indexString + ".reg";
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), layerRegionKey.c_str(), layerRegFileName.c_str(), configFileName);
				std::string layerRegFileNamePath = folderName + '\\' + layerRegFileName;
				e.second.regionList[index].WriteRegion(layerRegFileNamePath.c_str());
			}

			//repitingPortion
			if (e.second.insRegionType == RepititiveInspectionRegion)
			{
				for (int index = 0; index < regionCount; index++)
				{
					//region
					std::string indexString = std::to_string(index);
					std::string layerRepRegFileName = "Insp_LayerRepRegion_" + inspRegIDs + "_" + indexString + ".reg";
					std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
					WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), layerRepRegFileName.c_str(), configFileName);
					std::string layerRepRegFileNamePath = folderName + '\\' + layerRepRegFileName;
					e.second.repitingPortionList[index].WriteRegion(layerRepRegFileNamePath.c_str());
				}
			}


			//underInkingSensitivity
			std::string underInkValue = std::to_string((int)e.second.underInkingSensitivity);
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerInspectionRegion::INSP_UNDER_INK_KEY, underInkValue.c_str(), configFileName);
			//overInkingSensitivity
			std::string overInkValue = std::to_string((int)e.second.overInkingSensitivity);
			WritePrivateProfileStringA(INSP_REG_APP_NAME.c_str(), LayerInspectionRegion::INSP_OVER_INK_KEY, overInkValue.c_str(), configFileName);
			inspRegID++;
		}
	}

	//maskRegions
	int maskRegCount = maskRegions.size();
	std::string maskRegCountValue = std::to_string(maskRegCount);
	WritePrivateProfileStringA(APP_NAME, MASK_REG_COUNT_KEY, maskRegCountValue.c_str(), configFileName);
	if (maskRegCount > 0)
	{
		int maskRegID = 1;
		for (auto &e : maskRegions)
		{
			std::string MASK_REG_APP_NAME = std::string(LayerRegion::MASK_REGION_APP_NAME) + std::to_string(maskRegID);
			std::string maskRegIDs = std::to_string(maskRegID);

			//regionID
			std::string maskLayerRegIDValue = std::to_string(e.second.regionID);
			WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, maskLayerRegIDValue.c_str(), configFileName);
			//insRegionType
			std::string layerRegInspTypeValue = std::to_string((int)e.second.insRegionType);
			WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, layerRegInspTypeValue.c_str(), configFileName);
			//regionName				
			WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, e.second.regionName.c_str(), configFileName);

			int regionCount = e.second.regionList.size();
			std::string regionCountString = std::to_string(regionCount);
			WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, regionCountString.c_str(), configFileName);
			//region

			for (int index = 0; index < regionCount; index++)
			{
				std::string indexString = std::to_string(index);
				std::string layerRegFileName = "Mask_LayerRegion_" + maskRegIDs + "_" + indexString + ".reg";
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), layerRegionKey.c_str(), layerRegFileName.c_str(), configFileName);
				std::string layerRegFileNamePath = folderName + '\\' + layerRegFileName;
				e.second.regionList[index].WriteRegion(layerRegFileNamePath.c_str());
			}

			//repitingPortion
			if (e.second.insRegionType == RepititiveMaskRegion)
			{
				for (int index = 0; index < regionCount; index++)
				{
					//region
					std::string indexString = std::to_string(index);
					std::string layerRepRegFileName = "Mask_LayerRepRegion_" + maskRegIDs + "_" + indexString + ".reg";
					std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
					WritePrivateProfileStringA(MASK_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), layerRepRegFileName.c_str(), configFileName);
					std::string layerRepRegFileNamePath = folderName + '\\' + layerRepRegFileName;
					e.second.repitingPortionList[index].WriteRegion(layerRepRegFileNamePath.c_str());
				}
			}
			maskRegID++;
		}
	}
	//statisticsRegions
	int statiRegCount = statisticsRegions.size();
	std::string statiRegCountValue = std::to_string(statiRegCount);
	WritePrivateProfileStringA(APP_NAME, STATI_REG_COUNT_KEY, statiRegCountValue.c_str(), configFileName);
	if (statiRegCount > 0)
	{
		int statiRegID = 1;
		for (auto &e : statisticsRegions)
		{
			std::string STATI_REG_APP_NAME = std::string(LayerRegion::STATISTICS_REGION_APP_NAME) + std::to_string(statiRegID);
			std::string statiRegIDs = std::to_string(statiRegID);

			//regionID
			std::string statiLayerRegIDValue = std::to_string(e.second.regionID);
			WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, statiLayerRegIDValue.c_str(), configFileName);
			//regionName
			WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_NAME_KEY, e.second.regionName.c_str(), configFileName);
			//insRegionType
			std::string layerRegInspTypeValue = std::to_string(e.second.insRegionType);
			WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_INSP_TYPE_KEY, layerRegInspTypeValue.c_str(), configFileName);

			int regionCount = e.second.regionList.size();
			std::string regionCountString = std::to_string(regionCount);
			WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_COUNT_KEY, regionCountString.c_str(), configFileName);

			for (int index = 0; index < regionCount; index++)
			{
				//region
				std::string indexString = std::to_string(index);
				std::string layerRegFileName = "Stati_LayerRegion_" + statiRegIDs + "_" + indexString + ".reg";
				std::string layerRegionKey = std::string(LayerRegion::LAYER_REGION__KEY) + "_" + indexString;
				WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), layerRegionKey.c_str(), layerRegFileName.c_str(), configFileName);
				std::string layerRegFileNamePath = folderName + '\\' + layerRegFileName;
				e.second.regionList[index].WriteRegion(layerRegFileNamePath.c_str());
				//repitingPortion
				std::string layerRepRegFileName = "Stati_LayerRepRegion_" + statiRegIDs + "_" + indexString + ".reg";
				std::string layerRepRegionKey = std::string(LayerRegion::LAYER_REGION_REP_KEY) + "_" + indexString;
				WritePrivateProfileStringA(STATI_REG_APP_NAME.c_str(), layerRepRegionKey.c_str(), layerRepRegFileName.c_str(), configFileName);
				std::string layerRepRegFileNamePath = folderName + '\\' + layerRepRegFileName;
				e.second.repitingPortionList[index].WriteRegion(layerRepRegFileNamePath.c_str());
			}
			statiRegID++;
		}
	}

	//transferMaskRegion
	int transRegCount = sourceMaskID.size();
	std::string transRegCountValue = std::to_string(transRegCount);
	WritePrivateProfileStringA(APP_NAME, TRANS_MASK_REG_COUNT_KEY, transRegCountValue.c_str(), configFileName);
	if (transRegCount > 0)
	{
		for (int transRegID = 1; transRegID <= transRegCount; transRegID++)
		{
			std::string TRANS_REG_APP_NAME = std::string(LayerTransferMaskRegion::TRANS_MASK_REGION_APP_NAME) + std::to_string(transRegID);

			//sourceTaskID
			std::string transMaskRegSourceIDValue = std::to_string(sourceMaskID[transRegID - 1]);
			WritePrivateProfileStringA(TRANS_REG_APP_NAME.c_str(), LayerRegion::LAYER_REGION_ID_KEY, transMaskRegSourceIDValue.c_str(), configFileName);
		}
	}

	//maxImage
	std::string maxImageFileName;
	if (maxImage.IsInitialized())
	{
		maxImageFileName = "maxImage.tif";
		std::string maxImageFileNamePath = folderName + '\\' + maxImageFileName;
		maxImage.WriteImage("tiff", 0, maxImageFileNamePath.c_str());
	}
	else
	{
		maxImageFileName = "";
	}
	WritePrivateProfileStringA(APP_NAME, MAX_IMAGE_KEY, maxImageFileName.c_str(), configFileName);
	//minImage
	std::string minImageFileName;
	if (minImage.IsInitialized())
	{
		minImageFileName = "minImage.tif";
		std::string minImageFileNamePath = folderName + '\\' + minImageFileName;
		minImage.WriteImage("tiff", 0, minImageFileNamePath.c_str());
	}
	else
	{
		minImageFileName = "";
	}
	WritePrivateProfileStringA(APP_NAME, MIN_IMAGE_KEY, minImageFileName.c_str(), configFileName);
	//rankImage
	std::string rankImageFileName;
	if (rankImage.IsInitialized())
	{
		rankImageFileName = "rankImage.tif";
		std::string rankImageFileNamePath = folderName + '\\' + rankImageFileName;
		rankImage.WriteImage("tiff", 0, rankImageFileNamePath.c_str());
	}
	else
	{
		rankImageFileName = "";
	}
	WritePrivateProfileStringA(APP_NAME, RANK_IMAGE_KEY, rankImageFileName.c_str(), configFileName);

	//rowRef
	std::string rowRefFileName = "rowRef.tup";
	WritePrivateProfileStringA(APP_NAME, ROW_REF_KEY, rowRefFileName.c_str(), configFileName);
	std::string rowRefPath = folderName + '\\' + rowRefFileName;
	rowRef.WriteTuple(rowRefPath.c_str());
	//columnRef
	std::string columnRefFileName = "columnRef.tup";
	WritePrivateProfileStringA(APP_NAME, COLUMN_REF_KEY, columnRefFileName.c_str(), configFileName);
	std::string columnRefPath = folderName + '\\' + columnRefFileName;
	columnRef.WriteTuple(columnRefPath.c_str());
	//angleRef
	std::string angleRefFileName = "angleRef.tup";
	WritePrivateProfileStringA(APP_NAME, ANGLE_REF_KEY, angleRefFileName.c_str(), configFileName);
	std::string angleRefPath = folderName + '\\' + angleRefFileName;
	angleRef.WriteTuple(angleRefPath.c_str());
}



void MeasurementData::ReadConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	//taskID
	taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID_KEY, 0, configFileName);
	//isEnabled
	isEnabled = GetPrivateProfileIntA(APP_NAME, ENABLED_KEY, 0, configFileName);
	//TaskName
	char taskNameValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, TASK_NAME_KEY, NULL, taskNameValue, MAX_PATH_LENGTH, configFileName);
	taskName = taskNameValue;
	//taskType
	typeOfInspectionTask = (InspectionTypes)(GetPrivateProfileIntA(APP_NAME, TASK_TYPE_KEY, 0, configFileName));
	//NumberOfMeasurements
	int numberOfMeasurements = GetPrivateProfileIntA(APP_NAME, NO_OF_MEASUREMENTS_KEY, 0, configFileName);

	measurementList.clear();
	for (int index = 0; index < numberOfMeasurements; index++)
	{
		string measurementConfigDirName = folderName + "\\Measurement" + to_string(index + 1);
		//CreateDirectoryA(measurementConfigDirName.c_str(), NULL);
		Measurement temp;
		temp.ReadConfiguration(measurementConfigDirName);
		measurementList.push_back(temp);		
	}
}


void Measurement::UpdateMeasurementPointsRefLocation(HTuple _rowRef, HTuple _columnRef, HTuple _angleRef, UINT _sourceTaskID)
{
	if (firstMeasurementPoint.tpData.sourceTaskIDList.size() > 0 && firstMeasurementPoint.tpData.sourceTaskIDList[0] == _sourceTaskID)
	{
		firstMeasurementPoint.UpdateRefLocations(_rowRef, _columnRef, _angleRef);
	}
	if (secondMeasurementPoint.tpData.sourceTaskIDList.size() > 0 && secondMeasurementPoint.tpData.sourceTaskIDList[0] == _sourceTaskID)
	{
		secondMeasurementPoint.UpdateRefLocations(_rowRef, _columnRef, _angleRef);
	}
}

void Measurement::ReadConfiguration(string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	//p1_row
	char P1_Row[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_ROW_KEY, NULL, P1_Row, MAX_PATH_LENGTH, configFileName);
	string P1_Row_Str = folderName + "\\" + string(P1_Row);
	firstMeasurementPoint.row = firstMeasurementPoint.row.ReadTuple(P1_Row_Str.c_str());
	//p1_column
	char P1_Column[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_COLUMN_KEY, NULL, P1_Column, MAX_PATH_LENGTH, configFileName);
	string P1_Column_Str = folderName + "\\" + string(P1_Column);
	firstMeasurementPoint.column = firstMeasurementPoint.column.ReadTuple(P1_Column_Str.c_str());
	//p1_rowRef
	char P1_RowRef[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_ROW_REF_KEY, NULL, P1_RowRef, MAX_PATH_LENGTH, configFileName);
	string P1_RowRef_Str = folderName + "\\" + string(P1_RowRef);
	firstMeasurementPoint.rowRef = firstMeasurementPoint.rowRef.ReadTuple(P1_RowRef_Str.c_str());
	//p1_columnRef
	char P1_Column_Ref[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_COLUMN_REF_KEY, NULL, P1_Column_Ref, MAX_PATH_LENGTH, configFileName);
	string P1_Column_Ref_Str = folderName + "\\" + string(P1_Column_Ref);
	firstMeasurementPoint.columnRef = 	firstMeasurementPoint.columnRef.ReadTuple(P1_Column_Ref_Str.c_str());
	//P1_Region
	char P1_Region[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_REGION, NULL, P1_Region, MAX_PATH_LENGTH, configFileName);
	if (*P1_Region != NULL)
	{
		string P1_Region_Str = folderName + "\\" + string(P1_Region);
		firstMeasurementPoint.measurementPointRegion.ReadRegion(P1_Region_Str.c_str());
	}
	else
	{
		//Generating default Regions
		HRegion temp1, temp2;
		temp1.GenRegionLine(40, 50, 60, 50);
		temp2.GenRegionLine(50, 40, 50, 60);
		firstMeasurementPoint.measurementPointRegion = temp1.Union2(temp2);
	}
	//P1_Directory
	char P1_Dir_char[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P1_DIRECTORY_KEY, NULL, P1_Dir_char, MAX_PATH_LENGTH, configFileName);
	string P1_Directory_Str = folderName + "\\" + string(P1_Dir_char);
	CreateDirectoryA(P1_Directory_Str.c_str(), NULL);
	firstMeasurementPoint.tpData.ReadConfiguration(P1_Directory_Str.c_str());


	//p2_row
	char P2_Row[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_ROW_KEY, NULL, P2_Row, MAX_PATH_LENGTH, configFileName);
	string P2_Row_Str = folderName + "\\" + string(P2_Row);
	secondMeasurementPoint.row = secondMeasurementPoint.row.ReadTuple(P2_Row_Str.c_str());
	//p2_column
	char P2_Column[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_COLUMN_KEY, NULL, P2_Column, MAX_PATH_LENGTH, configFileName);
	string P2_Column_Str = folderName + "\\" + string(P2_Column);
	secondMeasurementPoint.column = secondMeasurementPoint.column.ReadTuple(P2_Column_Str.c_str());
	//p2_rowRef
	char P2_Row_Ref[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_ROW_REF_KEY, NULL, P2_Row_Ref, MAX_PATH_LENGTH, configFileName);
	string P2_Row_Ref_Str = folderName + "\\" + string(P2_Row_Ref);
	secondMeasurementPoint.rowRef = secondMeasurementPoint.rowRef.ReadTuple(P2_Row_Ref_Str.c_str());
	//p2_columnRef
	char P2_Column_Ref[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_COLUMN_REF_KEY, NULL, P2_Column_Ref, MAX_PATH_LENGTH, configFileName);
	string P2_Column_Ref_Str = folderName + "\\" + string(P2_Column_Ref);
	secondMeasurementPoint.columnRef = secondMeasurementPoint.columnRef.ReadTuple(P2_Column_Ref_Str.c_str());
	//P2_Region
	char P2_Region[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_REGION, NULL, P2_Region, MAX_PATH_LENGTH, configFileName);
	if (*P2_Region != NULL)
	{
		string P2_Region_Str = folderName + "\\" + string(P2_Region);
		secondMeasurementPoint.measurementPointRegion.ReadRegion(P2_Region_Str.c_str());
	}
	else
	{
		//Generating default Regions
		HRegion temp1, temp2;
		temp1.GenRegionLine(90, 100, 110, 100);
		temp2.GenRegionLine(100, 90, 100, 110);
		secondMeasurementPoint.measurementPointRegion = temp1.Union2(temp2);
	}
	//P2_Directory
	char P2_Dir_char[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, P2_DIRECTORY_KEY, NULL, P2_Dir_char, MAX_PATH_LENGTH, configFileName);
	string P2_Directory_Str = folderName + "\\" + string(P2_Dir_char);
	CreateDirectoryA(P2_Directory_Str.c_str(), NULL);
	secondMeasurementPoint.tpData.ReadConfiguration(P2_Directory_Str.c_str());


	//verticalMeasureTollerance
	char verticalMeasureParamValue[10];
	GetPrivateProfileStringA(APP_NAME, MEASURE_VERTICAL_LOW_TOL_KEY, NULL, verticalMeasureParamValue, 10, configFileName);
	vertical.lowerTolerance = atof(verticalMeasureParamValue);
	GetPrivateProfileStringA(APP_NAME, MEASURE_VERTICAL_UP_TOL_KEY, NULL, verticalMeasureParamValue, 10, configFileName);
	vertical.upperTolerance = atof(verticalMeasureParamValue);
	GetPrivateProfileStringA(APP_NAME, VERTICAL_NOMINAL_VALUE, NULL, verticalMeasureParamValue, 10, configFileName);
	vertical.nominalDistance = atof(verticalMeasureParamValue);
	//horizontalMeasureTollerance
	char horizontalMeasureParamValue[10];
	GetPrivateProfileStringA(APP_NAME, MEASURE_HORIZONTAL_LOW_TOL_KEY, NULL, horizontalMeasureParamValue, 10, configFileName);
	horizontal.lowerTolerance = atof(horizontalMeasureParamValue);
	GetPrivateProfileStringA(APP_NAME, MEASURE_HORIZONTAL_UP_TOL_KEY, NULL, horizontalMeasureParamValue, 10, configFileName);
	horizontal.upperTolerance = atof(horizontalMeasureParamValue);
	GetPrivateProfileStringA(APP_NAME, HORIZONTAL_NOMINAL_VALUE, NULL, horizontalMeasureParamValue, 10, configFileName);
	horizontal.nominalDistance = atof(horizontalMeasureParamValue);
}
void MeasurementData::WriteConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//taskID
	std::string taskIDValue = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID_KEY, taskIDValue.c_str(), configFileName);
	//isEnabled
	std::string enabledValue = std::to_string((int)isEnabled);
	WritePrivateProfileStringA(APP_NAME, ENABLED_KEY, enabledValue.c_str(), configFileName);
	//taskType
	std::string taskTypeValue = std::to_string(typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE_KEY, taskTypeValue.c_str(), configFileName);
	//taskName
	WritePrivateProfileStringA(APP_NAME, TASK_NAME_KEY, taskName.c_str(), configFileName);
	//NumberOfMeasurements
	std::string noOfMeasurementsStr = std::to_string(measurementList.size());
	WritePrivateProfileStringA(APP_NAME, NO_OF_MEASUREMENTS_KEY, noOfMeasurementsStr.c_str(), configFileName);

	for (int index=0; index < measurementList.size(); index++)
	{
		string measurementConfigDirName = folderName+"\\Measurement"+to_string(index+1);
		CreateDirectoryA(measurementConfigDirName.c_str(), NULL);
		measurementList[index].WriteConfiguration(measurementConfigDirName);		
	}	
}

void Measurement::WriteConfiguration(string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}
	

	//p1_row
	std::string P1_Row = "P1_Row.tup";
	WritePrivateProfileStringA(APP_NAME, P1_ROW_KEY, P1_Row.c_str(), configFileName);
	firstMeasurementPoint.row.WriteTuple((folderName + "\\" + P1_Row).c_str());
	//p1_column
	std::string P1_Column = "P1_Column.tup";
	WritePrivateProfileStringA(APP_NAME, P1_COLUMN_KEY, P1_Column.c_str(), configFileName);
	firstMeasurementPoint.column.WriteTuple((folderName + "\\" + P1_Column).c_str());
	//p1_rowRef
	std::string P1_Row_Ref = "P1_Row_Ref.tup";
	WritePrivateProfileStringA(APP_NAME, P1_ROW_REF_KEY, P1_Row_Ref.c_str(), configFileName);
	firstMeasurementPoint.rowRef.WriteTuple((folderName + "\\" + P1_Row_Ref).c_str());
	//p1_columnRef
	std::string P1_Column_Ref = "P1_Column_Ref.tup";
	WritePrivateProfileStringA(APP_NAME, P1_COLUMN_REF_KEY, P1_Column_Ref.c_str(), configFileName);
	firstMeasurementPoint.columnRef.WriteTuple((folderName + "\\" + P1_Column_Ref).c_str());
	//P1_Region
	std::string P1_Region = "P1_Region.reg";
	WritePrivateProfileStringA(APP_NAME, P1_REGION, P1_Region.c_str(), configFileName);
	firstMeasurementPoint.measurementPointRegion.WriteRegion((folderName + "\\" + P1_Region).c_str());
	//P1_Directory
	string P1_Dir_char = "P1";
	WritePrivateProfileStringA(APP_NAME, P1_DIRECTORY_KEY, P1_Dir_char.c_str(), configFileName);
	string P1_Directory_Str = folderName + "\\" + string(P1_Dir_char);
	CreateDirectoryA(P1_Directory_Str.c_str(), NULL);
	firstMeasurementPoint.tpData.WriteConfiguration(P1_Directory_Str.c_str());

	//p2_row
	std::string P2_Row = "P2_Row.tup";
	WritePrivateProfileStringA(APP_NAME, P2_ROW_KEY, P2_Row.c_str(), configFileName);
	secondMeasurementPoint.row.WriteTuple((folderName + "\\" + P2_Row).c_str());
	//p2_column
	std::string P2_Column = "P2_Column.tup";
	WritePrivateProfileStringA(APP_NAME, P2_COLUMN_KEY, P2_Column.c_str(), configFileName);
	secondMeasurementPoint.column.WriteTuple((folderName + "\\" + P2_Column).c_str());
	//p2_rowRef
	std::string P2_Row_Ref = "P2_Row_Ref.tup";
	WritePrivateProfileStringA(APP_NAME, P2_ROW_REF_KEY, P2_Row_Ref.c_str(), configFileName);
	secondMeasurementPoint.rowRef.WriteTuple((folderName + "\\" + P2_Row_Ref).c_str());
	//p2_columnRef
	std::string P2_Column_Ref = "P2_Column_Ref.tup";
	WritePrivateProfileStringA(APP_NAME, P2_COLUMN_REF_KEY, P2_Column_Ref.c_str(), configFileName);
	secondMeasurementPoint.columnRef.WriteTuple((folderName + "\\" + P2_Column_Ref).c_str());
	//P2_Region
	std::string P2_Region = "P2_Region.reg";
	WritePrivateProfileStringA(APP_NAME, P2_REGION, P2_Region.c_str(), configFileName);
	secondMeasurementPoint.measurementPointRegion.WriteRegion((folderName + "\\" + P2_Region).c_str());
	//P2_Directory
	string P2_Dir_char = "P1";
	WritePrivateProfileStringA(APP_NAME, P2_DIRECTORY_KEY, P2_Dir_char.c_str(), configFileName);
	string P2_Directory_Str = folderName + "\\" + string(P2_Dir_char);
	CreateDirectoryA(P2_Directory_Str.c_str(), NULL);
	secondMeasurementPoint.tpData.WriteConfiguration(P2_Directory_Str.c_str());

	//verticalMeasureNominal
	std::string verticalMeasureNominalValue = std::to_string(vertical.nominalDistance);
	WritePrivateProfileStringA(APP_NAME, VERTICAL_NOMINAL_VALUE, verticalMeasureNominalValue.c_str(), configFileName);
	//horizontalMeasureNominal
	std::string horizontalMeasureNominalValue = std::to_string(horizontal.nominalDistance);
	WritePrivateProfileStringA(APP_NAME, HORIZONTAL_NOMINAL_VALUE, horizontalMeasureNominalValue.c_str(), configFileName);

	//verticalMeasureTolerance
	std::string verticalMeasureTolValue = std::to_string(vertical.upperTolerance);
	WritePrivateProfileStringA(APP_NAME, MEASURE_VERTICAL_UP_TOL_KEY, verticalMeasureTolValue.c_str(), configFileName);
	verticalMeasureTolValue = std::to_string(vertical.lowerTolerance);
	WritePrivateProfileStringA(APP_NAME, MEASURE_VERTICAL_LOW_TOL_KEY, verticalMeasureTolValue.c_str(), configFileName);
	//horizontalMeasureTolerance
	std::string horizontalMeasureTolValue = std::to_string(horizontal.upperTolerance);
	WritePrivateProfileStringA(APP_NAME, MEASURE_HORIZONTAL_UP_TOL_KEY, horizontalMeasureTolValue.c_str(), configFileName);
	horizontalMeasureTolValue = std::to_string(horizontal.lowerTolerance);
	WritePrivateProfileStringA(APP_NAME, MEASURE_HORIZONTAL_LOW_TOL_KEY, horizontalMeasureTolValue.c_str(), configFileName);
}

void ThreadData::ReadConfiguration(std::string  folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	//taskID
	taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID_KEY, 0, configFileName);
	//taskType
	typeOfInspectionTask = InspectionTypes(GetPrivateProfileIntA(APP_NAME, TASK_TYPE_KEY, 0, configFileName));
	//isEnabled
	isEnabled = GetPrivateProfileIntA(APP_NAME, ENABLED_KEY, 0, configFileName);
	//TaskName
	char taskNameValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, TASK_NAME_KEY, NULL, taskNameValue, MAX_PATH_LENGTH, configFileName);
	taskName = taskNameValue;

	//Inspection Window
	char inspectionWindowRegionFile[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_KEY, NULL, inspectionWindowRegionFile, MAX_PATH_LENGTH, configFileName);
	if (*inspectionWindowRegionFile != NULL)
	{
		std::string layerRegFileNamePath = folderName + '\\' + inspectionWindowRegionFile;
		inspectionWindow.ReadRegion(layerRegFileNamePath.c_str());
	}

	//Dynamic Threashold Value
	char dynamicThresholdValueStr[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, DYNAMIC_THRESHOLD_VALUE_KEY, NULL, dynamicThresholdValueStr, MAX_PATH_LENGTH, configFileName);
	dynamicThresholdValue = atof(dynamicThresholdValueStr);

	//Image Scale Factor
	char imageScaleFacorStr[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, IMAGE_SCALE_FACTOR_KEY, NULL, imageScaleFacorStr, MAX_PATH_LENGTH, configFileName);
	imageScaleFactor = atof(imageScaleFacorStr);

	//regType
	regType = (RegionTypes)GetPrivateProfileIntA(APP_NAME, REGION_TYPE, 0, configFileName);
	//main threadRegions
	int threadPatternRegCount = GetPrivateProfileIntA(APP_NAME, THREAD_PATTERN_REGION_COUNT_KEY, 0, configFileName);
	if (threadPatternRegCount > 0)
	{
		for (int threadID = 1; threadID <= threadPatternRegCount; threadID++)
		{
			std::string THREAD_REGION_SUB_KEY = std::string(THREAD_PATTERN_REGION_KEY) + std::to_string(threadID);
			char threadRegFileName[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(APP_NAME, THREAD_REGION_SUB_KEY.c_str(), NULL, threadRegFileName, MAX_PATH_LENGTH, configFileName);
			if (*threadRegFileName != NULL)
			{
				std::string threadRegFileNamePath = folderName + '\\' + threadRegFileName;
				HRegion threadReg;
				threadReg.ReadRegion(threadRegFileNamePath.c_str());
				threadPatternRegions.push_back(threadReg);
			}
		}
	}

	//Remaining thread Search Regions
	int threadSearchRegCount = GetPrivateProfileIntA(APP_NAME, THREAD_SEARCH_REGION_COUNT_KEY, 0, configFileName);
	if (threadSearchRegCount > 0)
	{
		for (int threadID = 1; threadID <= threadSearchRegCount; threadID++)
		{
			std::string THREAD_REGION_SUB_KEY = std::string(THREAD_SEARCH_REGION_KEY) + std::to_string(threadID);
			char threadRegFileName[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(APP_NAME, THREAD_REGION_SUB_KEY.c_str(), NULL, threadRegFileName, MAX_PATH_LENGTH, configFileName);
			if (*threadRegFileName != NULL)
			{
				std::string threadRegFileNamePath = folderName + '\\' + threadRegFileName;
				HRegion threadReg;
				threadReg.ReadRegion(threadRegFileNamePath.c_str());
				threadSearchWindows.push_back(threadReg);
			}
		}
	}
	//isThreadWindowingCheckRequired
	isThreadWindowingCheckRequired = GetPrivateProfileIntA(APP_NAME, IS_THREAD_WINDOWING_CHECK_REQUIRED, 0, configFileName);
	//noOfThreadWindowsPerColumn
	noOfThreadWindowsPerColumn = GetPrivateProfileIntA(APP_NAME, THREAD_WINDOW_COUNT_PER_COLUMN_KEY, 0, configFileName);
}
void ThreadData::WriteConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//taskID
	std::string taskIDValue = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID_KEY, taskIDValue.c_str(), configFileName);
	//isEnabled
	std::string enabledValue = std::to_string((int)isEnabled);
	WritePrivateProfileStringA(APP_NAME, ENABLED_KEY, enabledValue.c_str(), configFileName);

	//taskType
	std::string taskTypeValue = std::to_string(typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE_KEY, taskTypeValue.c_str(), configFileName);
	//task name
	WritePrivateProfileStringA(APP_NAME, TASK_NAME_KEY, taskName.c_str(), configFileName);
	//regType
	std::string regTypeString = std::to_string(regType);
	WritePrivateProfileStringA(APP_NAME, REGION_TYPE, regTypeString.c_str(), configFileName);

	// Inspection Window
	std::string inspectionWindowRegionFile = "InspectionWindow.reg";
	WritePrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_KEY, inspectionWindowRegionFile.c_str(), configFileName);
	std::string inspectionRegFileNamePath = folderName + '\\' + inspectionWindowRegionFile;
	inspectionWindow.WriteRegion(inspectionRegFileNamePath.c_str());

	//Dynamic Threashold Value
	std::string dynamicThresholdValueStr = std::to_string(dynamicThresholdValue);
	WritePrivateProfileStringA(APP_NAME, DYNAMIC_THRESHOLD_VALUE_KEY, dynamicThresholdValueStr.c_str(), configFileName);

	//Image Scale Factor
	std::string imageScaleFacorStr = std::to_string(imageScaleFactor);
	WritePrivateProfileStringA(APP_NAME, IMAGE_SCALE_FACTOR_KEY, imageScaleFacorStr.c_str(), configFileName);

	//threadPatternRegions
	int threadPatternRegCount = threadPatternRegions.size();
	std::string threadCountValue = std::to_string(threadPatternRegCount);
	WritePrivateProfileStringA(APP_NAME, THREAD_PATTERN_REGION_COUNT_KEY, threadCountValue.c_str(), configFileName);
	if (threadPatternRegCount > 0)
	{
		for (int threadID = 1; threadID <= threadPatternRegCount; threadID++)
		{
			std::string threadRegFileName = "ThreadPatternRegion" + std::to_string(threadID) + ".reg";
			std::string THREAD_REGION_SUB_KEY = std::string(THREAD_PATTERN_REGION_KEY) + std::to_string(threadID);
			WritePrivateProfileStringA(APP_NAME, THREAD_REGION_SUB_KEY.c_str(), threadRegFileName.c_str(), configFileName);

			std::string threadRegFileNamePath = folderName + '\\' + threadRegFileName;
			threadPatternRegions[threadID - 1].WriteRegion(threadRegFileNamePath.c_str());
		}
	}

	//threadSearchRegions
	int threadSearchRegCount = threadSearchWindows.size();
	threadCountValue = std::to_string(threadSearchRegCount);
	WritePrivateProfileStringA(APP_NAME, THREAD_SEARCH_REGION_COUNT_KEY, threadCountValue.c_str(), configFileName);
	if (threadSearchRegCount > 0)
	{
		for (int threadID = 1; threadID <= threadSearchRegCount; threadID++)
		{
			std::string threadRegFileName = "ThreadSearchRegion" + std::to_string(threadID) + ".reg";
			std::string THREAD_REGION_SUB_KEY = std::string(THREAD_SEARCH_REGION_KEY) + std::to_string(threadID);
			WritePrivateProfileStringA(APP_NAME, THREAD_REGION_SUB_KEY.c_str(), threadRegFileName.c_str(), configFileName);

			std::string threadRegFileNamePath = folderName + '\\' + threadRegFileName;
			threadSearchWindows[threadID - 1].WriteRegion(threadRegFileNamePath.c_str());
		}
	}

	//isThreadWindowingCheckRequired
	std::string isThreadWindowingCheckRequiredString = std::to_string(isThreadWindowingCheckRequired);
	WritePrivateProfileStringA(APP_NAME, IS_THREAD_WINDOWING_CHECK_REQUIRED, isThreadWindowingCheckRequiredString.c_str(), configFileName);
	//noOfThreadWindowsPerColumn
	std::string threadWindowCountValue = std::to_string(noOfThreadWindowsPerColumn);
	WritePrivateProfileStringA(APP_NAME, THREAD_WINDOW_COUNT_PER_COLUMN_KEY, threadWindowCountValue.c_str(), configFileName);
}


void BlobAnalyzerData::ReadConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	//taskID
	taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID_KEY, 0, configFileName);
	//taskType
	typeOfInspectionTask = InspectionTypes(GetPrivateProfileIntA(APP_NAME, TASK_TYPE_KEY, 0, configFileName));
	//TaskName
	char taskNameValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, TASK_NAME_KEY, NULL, taskNameValue, MAX_PATH_LENGTH, configFileName);
	taskName = taskNameValue;
	//blopParametersGroupID
	blopParametersGroupID = (BlobParametersGroups)GetPrivateProfileIntA(APP_NAME, BLOB_PARAMETERS_GROUP_ID, 0, configFileName);
	//ImageWidth
	imageWidth = GetPrivateProfileIntA(APP_NAME, IMAGE_WIDTH, 0, configFileName);
	//ImageHeight
	imageHeight = GetPrivateProfileIntA(APP_NAME, IMAGE_HEIGHT, 0, configFileName);

	//Up Wise Partation Region
	char upwiseRegFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, UP_WISE_PARTITION_REGION, NULL, upwiseRegFileName, MAX_PATH_LENGTH, configFileName);

	if (*upwiseRegFileName != NULL)
	{
		std::string upwiseRegFilePath = folderName + '\\' + upwiseRegFileName;
		UpWisePartation.ReadRegion(upwiseRegFilePath.c_str());
	}


	//numberOfLayerTasks
	int numberOfLayerTasks = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_LAYER_TASKS, 0, configFileName);
	layerInspectionTaskID.clear();
	for (int layerID = 1; layerID <= numberOfLayerTasks; layerID++)
	{
		std::string sourceLayerTaskID = SOURCE_LAYER_TASK_ID + std::to_string(layerID);
		layerInspectionTaskID.push_back(GetPrivateProfileIntA(APP_NAME, sourceLayerTaskID.c_str(), 0, configFileName));
	}
}

void BlobAnalyzerData::WriteConfiguration(std::string folderName)
{
	char configFileName[300];
	sprintf_s(configFileName, 300, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//taskID
	std::string taskIDValue = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID_KEY, taskIDValue.c_str(), configFileName);
	//taskType
	std::string taskTypeValue = std::to_string(typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE_KEY, taskTypeValue.c_str(), configFileName);
	//task name
	WritePrivateProfileStringA(APP_NAME, TASK_NAME_KEY, taskName.c_str(), configFileName);
	//blopParametersGroupID
	WritePrivateProfileStringA(APP_NAME, BLOB_PARAMETERS_GROUP_ID, std::to_string(blopParametersGroupID).c_str(), configFileName);
	//ImageWidth
	WritePrivateProfileStringA(APP_NAME, IMAGE_WIDTH, std::to_string(imageWidth).c_str(), configFileName);
	//ImageHeight
	WritePrivateProfileStringA(APP_NAME, IMAGE_HEIGHT, std::to_string(imageHeight).c_str(), configFileName);

	//Up Wise Partation Region
	std::string upwisePartitionRegFileName = "UpWisePartitionRegion.reg";
	WritePrivateProfileStringA(APP_NAME, UP_WISE_PARTITION_REGION, upwisePartitionRegFileName.c_str(), configFileName);
	std::string upwisePartitionRegFileNamePath = folderName + '\\' + upwisePartitionRegFileName;
	UpWisePartation.WriteRegion(upwisePartitionRegFileNamePath.c_str());

	//numberOfLayerTasks
	int numberOfLayerTasks = layerInspectionTaskID.size();
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_LAYER_TASKS, std::to_string(numberOfLayerTasks).c_str(), configFileName);

	for (int layerID = 1; layerID <= numberOfLayerTasks; layerID++)
	{
		std::string sourceLayerTaskID = SOURCE_LAYER_TASK_ID + std::to_string(layerID);
		WritePrivateProfileStringA(APP_NAME, sourceLayerTaskID.c_str(), std::to_string(layerInspectionTaskID[layerID - 1]).c_str(), configFileName);
	}
}


CameraData::CameraData()
{
}

CameraData::~CameraData()
{
	//for (auto &e : inspectionTasks)
	//{
	//	delete e.second;
	//}
	inspectionTasks.clear();
	thisCameraTrainingSet.clear();
}

LayerInspectionRegion CameraData::AddInspectionRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType, SensitivityLevels _underInkingSensitivity, SensitivityLevels _overInkingSensitivity)
{
	LayerInspectionRegion tempInsRegData;
	tempInsRegData.regionID = _regID;
	tempInsRegData.regionName = regName;
	tempInsRegData.insRegionType = _regionType;
	tempInsRegData.underInkingSensitivity = _underInkingSensitivity;
	tempInsRegData.overInkingSensitivity = _overInkingSensitivity;
	GetLayer(_layerID)->insRegions[_regID] = tempInsRegData;
	return tempInsRegData;
}

LayerRegion CameraData::AddMaskRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType)
{
	LayerRegion tempMaskRegData;
	tempMaskRegData.regionID = _regID;
	tempMaskRegData.regionName = regName;
	tempMaskRegData.insRegionType = _regionType;
	GetLayer(_layerID)->maskRegions[_regID] = tempMaskRegData;
	return tempMaskRegData;
}

LayerRegion CameraData::AddStatisticsRegion(UINT _layerID, UINT _regID, std::string &regName, RegionTypes _regionType)
{
	LayerRegion tempStatRegData;
	tempStatRegData.regionID = _regID;
	tempStatRegData.regionName = regName;
	tempStatRegData.insRegionType = _regionType;
	GetLayer(_layerID)->statisticsRegions[_regID] = tempStatRegData;
	return tempStatRegData;
}

bool CameraData::DeleteRegion(UINT _layerID, UINT _regID)
{
	bool isDeleted = false;

	if (GetLayer(_layerID)->insRegions.find(_regID) != GetLayer(_layerID)->insRegions.end())
	{
		GetLayer(_layerID)->insRegions.erase(_regID);
		isDeleted = true;
	}
	else if (GetLayer(_layerID)->maskRegions.find(_regID) != GetLayer(_layerID)->maskRegions.end())
	{
		GetLayer(_layerID)->maskRegions.erase(_regID);
		isDeleted = true;
	}
	else if (GetLayer(_layerID)->statisticsRegions.find(_regID) != GetLayer(_layerID)->statisticsRegions.end())
	{
		GetLayer(_layerID)->statisticsRegions.erase(_regID);
		isDeleted = true;
	}
	else
	{
		isDeleted = false;
	}

	return isDeleted;
}

bool CameraData::AddLayer(LayerData *layerData)
{
	LayerData *templayerData = GetLayer(layerData->taskID - 1);
	if (templayerData != NULL)
	{
		layerData->anchorRegions = templayerData->anchorRegions;
		layerData->inspectionWindow = this->InspectionWindow;
		layerData->minImage.GenEmptyObj();
		layerData->maxImage.GenEmptyObj();
		layerData->rankImage.GenEmptyObj();
		Hlong row1, row2, column1, column2;
		this->InspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
		HImage tempMinImage, tempMaxImage;
		tempMinImage.GenImageConst("byte", (column2 - column1) + 1 * layerData->ResolutionFactorToProcess, (row2 - row1) + 1 * layerData->ResolutionFactorToProcess);
		tempMaxImage = tempMinImage.GenImageProto(0.0);
		tempMinImage = tempMinImage.GenImageProto(255.0);
		layerData->rankImage = tempMinImage.GenImageProto(0.0);
		for (int index = 0; index < MAX_NUM_OF_COLOR_CHANNELS; index++)
		{
			//layerData->minImage = layerData->minImage.AppendChannel(tempMinImage);
			//layerData->maxImage = layerData->maxImage.AppendChannel(tempMaxImage);
			layerData->minImage = layerData->minImage.ConcatObj(tempMinImage);
			layerData->maxImage = layerData->maxImage.ConcatObj(tempMaxImage);
			layerData->colorChannel[index] = templayerData->colorChannel[index];
			layerData->colorChannel[index].isEnabled = true;
		}
		layerData->anchorRegions.CreateModel(masterImageReduced);
		layerData->UpdateAnchorRefLocations(masterImage);
	}
	ThreadData *threadData = GetThread();
	if (threadData != NULL)
	{
		layerData->sourceMaskID.push_back(threadData->taskID);
	}
	AddTransferMaskForLayers(layerData->taskID);

	BlobAnalyzerData *blobAnalyzerData = GetBlobAnalyzer();
	if (blobAnalyzerData != NULL)
	{
		blobAnalyzerData->layerInspectionTaskID.push_back(layerData->taskID);
	}
	this->inspectionTasks[layerData->taskID] = layerData;
	return true;
}
bool CameraData::RemoveLayer(UINT taskID)
{
	bool isRemoved = false;
	if (this->inspectionTasks.find(taskID) != this->inspectionTasks.end())
	{
		this->inspectionTasks.erase(taskID);
		RemoveTransferMaskForLayers(taskID);
		isRemoved = true;
	}
	BlobAnalyzerData *blobAnalyzerData = GetBlobAnalyzer();
	if (blobAnalyzerData != NULL)
	{
		blobAnalyzerData->layerInspectionTaskID.erase(std::remove(blobAnalyzerData->layerInspectionTaskID.begin(), blobAnalyzerData->layerInspectionTaskID.end(), taskID), blobAnalyzerData->layerInspectionTaskID.end());
	}
	return isRemoved;
}

int CameraData::GetLayersCount()
{
	int count = 0;
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			count++;
		}
	}
	return count;
}

UINT CameraData::GetNextAvailableLayerID()
{
	UINT id = LAYER_STARTING_ID;
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			id = max(id, e.first);
		}
	}
	return id + 1;
}

void CameraData::AddTransferMaskForLayers(UINT maskID)
{
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			((LayerData *)e.second)->sourceMaskID.push_back(maskID);
		}
	}
}

void CameraData::RemoveTransferMaskForLayers(UINT maskID)
{
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			((LayerData *)e.second)->sourceMaskID.erase(std::remove(((LayerData *)e.second)->sourceMaskID.begin(), ((LayerData *)e.second)->sourceMaskID.end(), maskID), ((LayerData *)e.second)->sourceMaskID.end());
		}
	}
}


LayerData * CameraData::GetLayer(UINT taskID)
{
	LayerData *layerData = NULL;
	if (this->inspectionTasks.find(taskID) != this->inspectionTasks.end())
	{
		layerData = static_cast<LayerData *> (this->inspectionTasks[taskID]);
	}
	return layerData;
}


ThreadData * CameraData::GetThread()
{
	ThreadData *threadData = NULL;
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_ThreadDetection)
		{
			threadData = static_cast<ThreadData *> (e.second);
		}
	}
	return threadData;
}


MeasurementData *CameraData::GetMeasurement()
{
	MeasurementData *measurementData = NULL;
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_Measurement)
		{
			measurementData = static_cast<MeasurementData *> (e.second);
		}
	}
	return measurementData;
}

BlobAnalyzerData *CameraData::GetBlobAnalyzer()
{
	BlobAnalyzerData *blobAnalyzerData = NULL;
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_BlobAnalyser)
		{
			blobAnalyzerData = static_cast<BlobAnalyzerData *> (e.second);
		}
	}
	return blobAnalyzerData;
}


UINT CameraData::GetNextAvailableInspectionRegionID(UINT _layerID)
{
	UINT nextAvailableRegionID = INSPECTION_REGION_STARTING_ID;
	for (auto &e : GetLayer(_layerID)->insRegions)
	{
		nextAvailableRegionID = MAX(nextAvailableRegionID, e.first);
	}
	return (nextAvailableRegionID + 1);
}

UINT CameraData::GetNextAvailableMaskRegionID(UINT _layerID)
{
	UINT nextAvailableRegionID = MASK_REGION_STARTING_ID;
	for (auto &e : GetLayer(_layerID)->maskRegions)
	{
		nextAvailableRegionID = MAX(nextAvailableRegionID, e.first);
	}
	return (nextAvailableRegionID + 1);
}

UINT CameraData::GetNextAvailableStatisticsRegionID(UINT _layerID)
{
	UINT nextAvailableRegionID = STATISTICS_REGION_STARTING_ID;
	for (auto &e : GetLayer(_layerID)->statisticsRegions)
	{
		nextAvailableRegionID = MAX(nextAvailableRegionID, e.first);
	}
	return (nextAvailableRegionID + 1);
}


int CameraData::GetInspectionRegionCount(UINT _layerID)
{
	return GetLayer(_layerID)->insRegions.size();
}

int CameraData::GetMaskRegionCount(UINT _layerID)
{
	return GetLayer(_layerID)->maskRegions.size();
}

int CameraData::GetStatisticsRegionCount(UINT _layerID)
{
	return GetLayer(_layerID)->statisticsRegions.size();
}



int CameraData::GetInspectionRegionIndex(UINT _layerID, UINT _regID)
{
	int index = 0;
    index = std::distance(this->GetLayer(_layerID)->insRegions.begin(), this->GetLayer(_layerID)->insRegions.find(_regID));
	return index;
}

int CameraData::GetMaskRegionIndex(UINT _layerID, UINT _regID)
{
	int index = 0;
	index = std::distance(this->GetLayer(_layerID)->maskRegions.begin(), this->GetLayer(_layerID)->maskRegions.find(_regID));
	return index + GetInspectionRegionCount(_layerID);
}

int CameraData::GetStatisticsRegionIndex(UINT _layerID, UINT _regID)
{
	int index = 0;
	index = std::distance(this->GetLayer(_layerID)->statisticsRegions.begin(), this->GetLayer(_layerID)->statisticsRegions.find(_regID));
	return index + GetInspectionRegionCount(_layerID) + GetMaskRegionCount(_layerID);
}


int CameraData::GetAnyRegionIndex(UINT _layerID, RegionTypes regType, UINT _regID)
{
	int regionIndex = -1;
	switch (regType)
	{
	case UniqueInspectionRegion:
	case RepititiveInspectionRegion:
		regionIndex = GetInspectionRegionIndex(_layerID, _regID);
		break;
	case UniqueMaskRegion:
	case RepititiveMaskRegion:
		regionIndex = GetMaskRegionIndex(_layerID, _regID);
		break;
	case StatisticsRegion:
		regionIndex = GetStatisticsRegionIndex(_layerID, _regID);
		break;
	default:
		break;
	}
	return regionIndex;
}


RegionTypes CameraData::GetRegionType(UINT _layerID, UINT _regID)
{	
	LayerData *layerData = GetLayer(_layerID);
	if (layerData->insRegions.find(_regID) != layerData->insRegions.end())
	{
		return layerData->insRegions[_regID].insRegionType;
	}
	if (layerData->maskRegions.find(_regID) != layerData->maskRegions.end())
	{
		return layerData->maskRegions[_regID].insRegionType;
	}
	if (layerData->statisticsRegions.find(_regID) != layerData->statisticsRegions.end())
	{
		return layerData->statisticsRegions[_regID].insRegionType;
	}
}

void CameraData::SetSheetDetails(int _numberOfPanels, int _numberOfUps)
{
	numberOfUps = _numberOfUps;
	numberOfPanels = _numberOfPanels;
	if (InspectionWindow.IsInitialized())
	{
		SetInspectionWindowToBlobAnalyzer();
	}

	for (auto &e:inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_ThreadDetection)
		{
			ThreadData *threadData = static_cast<ThreadData *>(e.second);
			threadData->regType = ThreadRegion;
			threadData->threadSearchWindows.clear();
			HRegion tempRegion;
			tempRegion.GenRectangle1(0.0, 0.0, 4096.0, 75.0);
			int skippedColumn = 100;
			int noteWidth = (4096 - (2 * skippedColumn)) / _numberOfPanels;
			double threadHposition = skippedColumn + (noteWidth / 2);
			for (int colIndex = 0; colIndex < _numberOfPanels ; colIndex++)
			{
				HHomMat2D tempMat2D;
				tempMat2D.VectorAngleToRigid(0.0, 0.0, 0.0, 0.0, threadHposition, 0.0);
				threadData->threadSearchWindows.push_back(tempRegion.AffineTransRegion(tempMat2D, "nearest_neighbor"));
				threadHposition += noteWidth;
			}
			threadData->noOfThreadWindowsPerColumn = 48;
		}
	}
}


void CameraData::UpdatUnderInkingSensitivity(UINT _layerID, UINT _regID, SensitivityLevels _uiSensitivity)
{
	LayerData *layerData = GetLayer(_layerID);
	if (layerData->insRegions.find(_regID) != layerData->insRegions.end())
	{
		layerData->insRegions[_regID].underInkingSensitivity = _uiSensitivity;
	}
}
void CameraData::UpdatOverInkingSensitivity(UINT _layerID, UINT _regID, SensitivityLevels _oiSensitivity)
{
	LayerData *layerData = GetLayer(_layerID);
	if (layerData->insRegions.find(_regID) != layerData->insRegions.end())
	{
		layerData->insRegions[_regID].overInkingSensitivity = _oiSensitivity;
	}
}


void CameraData::SetInspectionWindowToLayers()
{
	for(auto &e:  this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			LayerData *layerData = static_cast<LayerData *> (e.second);
			layerData->inspectionWindow = this->InspectionWindow;
			layerData->minImage.GenEmptyObj();
			layerData->maxImage.GenEmptyObj();
			layerData->rankImage.GenEmptyObj();
			Hlong row1, row2, column1, column2;
			this->InspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
			HImage tempMinImage, tempMaxImage;
			tempMinImage.GenImageConst("byte", ((column2 - column1) + 1) * layerData->ResolutionFactorToProcess, ((row2 - row1) + 1) * layerData->ResolutionFactorToProcess);
			tempMaxImage = tempMinImage.GenImageProto(0.0);
			tempMinImage = tempMinImage.GenImageProto(255.0);
			layerData->rankImage = tempMinImage.GenImageProto(0.0);
			for (int index = 1; index <= MAX_NUM_OF_COLOR_CHANNELS; index++)
			{
				//layerData->minImage = layerData->minImage.AppendChannel(tempMinImage);
				//layerData->maxImage = layerData->maxImage.AppendChannel(tempMaxImage);

				layerData->minImage = layerData->minImage.ConcatObj(tempMinImage);
				layerData->maxImage = layerData->maxImage.ConcatObj(tempMaxImage);
			}
			layerData->anchorRegions.CreateModel(masterImageReduced);
			layerData->UpdateAnchorRefLocations(masterImage);
			for (auto &e : GetMeasurement()->measurementList)
			{
				e.UpdateMeasurementPointsRefLocation(layerData->rowRef, layerData->columnRef, layerData->angleRef, layerData->taskID);
			}
		}
	}
}


void CameraData::SetInspectionWindowToThreadInspection()
{
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_ThreadDetection)
		{
			ThreadData *threadData = static_cast<ThreadData *> (e.second);
			threadData->inspectionWindow = this->InspectionWindow;
		}
	}
}

void CameraData::SetInspectionWindowToBlobAnalyzer()
{
	for (auto &e : this->inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_BlobAnalyser)
		{
			BlobAnalyzerData *blobAnalyzerData = static_cast<BlobAnalyzerData *> (e.second);
			int erosionRectSize = (ApplicationSettingsReader::GetInstance()->inspectionWindowErosionSize * 2) + 1;
			HRegion tempRegion = this->InspectionWindow.ErosionRectangle1(erosionRectSize, erosionRectSize);
			HTuple row1, row2, column1, column2;
			tempRegion.SmallestRectangle1(&row1, &column1, &row2, &column2);
			HHomMat2D affineTransRect;
			affineTransRect.VectorAngleToRigid(row1[0].D(), column1[0].D(), 0.0, ApplicationSettingsReader::GetInstance()->inspectionWindowErosionSize, ApplicationSettingsReader::GetInstance()->inspectionWindowErosionSize, 0.0);
			tempRegion = tempRegion.AffineTransRegion(affineTransRect, "nearest_neighbor");
			int numberOfRows = numberOfUps / numberOfPanels;
			blobAnalyzerData->UpWisePartation = tempRegion.PartitionRectangle((column2[0].D() - column1[0].D()) / numberOfPanels, (row2[0].D() - row1[0].D()) / numberOfRows);
			InspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
			blobAnalyzerData->imageHeight = (UINT)(row2[0].D() - row1[0].D()) + 1;
			blobAnalyzerData->imageWidth = (UINT)(column2[0].D() - column1[0].D()) + 1;
		}
	}
}

void CameraData::ResetLayerImages()
{
	for (auto &e : inspectionTasks)
	{			
		switch (e.second->typeOfInspectionTask)
		{
		case inspection_type_LayerInspection:
		case inspection_type_SpecialLayerInspection:
			e.second->ResetMinMaxData();
			break;
		default:continue;
		}
	}
}

void CameraData::ReadConfiguration(std::string folderName, bool ReadTrainingSet)
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", folderName.c_str(), CONFIG_NAME);
	//cameraID
	cameraID = GetPrivateProfileIntA(APP_NAME, CAMERA_ID, 0, configFileName);
	//Number Of UPs
	numberOfUps = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_UPS, 0, configFileName);
	//Number Of Panels
	numberOfPanels = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_PANELS, 0, configFileName);
	//camera taskID
	taskID = GetPrivateProfileIntA(APP_NAME, TASK_ID, 0, configFileName);
	//camera tasktype
	typeOfInspectionTask = (InspectionTypes)GetPrivateProfileIntA(APP_NAME, TASK_TYPE, 0, configFileName);
	//camera tasName
	char taskNameValue[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, TASK_NAME_KEY, NULL, taskNameValue, MAX_PATH_LENGTH, configFileName);
	taskName = taskNameValue;
	//Master Image
	char masterImageFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MASTER_IMAGE_FILE, NULL, masterImageFileName, MAX_PATH_LENGTH, configFileName);
	if (*masterImageFileName != NULL)
	{
		std::string masterImageFilePath = folderName + "\\" + std::string(masterImageFileName);
		masterImage.ReadImage(masterImageFilePath.c_str());
		isMasterImageInitialized = true;
	}
	else
	{
		isMasterImageInitialized = false;
	}
	//Master Image Reduced
	char masterImageReducedFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MASTER_IMAGE_REDUCED_FILE, NULL, masterImageReducedFileName, MAX_PATH_LENGTH, configFileName);
	if (*masterImageReducedFileName != NULL)
	{
		std::string masterImageReducedFilePath = folderName + "\\" + std::string(masterImageReducedFileName);
		masterImageReduced.ReadImage(masterImageReducedFilePath.c_str());
		isMasterImageInitialized = true;
	}
	else
	{
		isMasterImageInitialized = false;
	}
	//Master IR Image
	char masterIRImageFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, MASTER_IR_IMAGE_FILE, NULL, masterIRImageFileName, MAX_PATH_LENGTH, configFileName);
	if (*masterIRImageFileName != NULL)
	{
		std::string masterIRImageFilePath = folderName + "\\" + std::string(masterIRImageFileName);
		masterIRImage.ReadImage(masterIRImageFilePath.c_str());
		isMasterImageInitialized = true;
	}
	else
	{
		if (isMasterImageInitialized)
		{
			masterIRImage = masterImage.Rgb1ToGray();
			isMasterImageInitialized = true;
		}
		else
		{
			isMasterImageInitialized = false;
		}
	}
	//Inspection Window
	char inspectionWindowFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_FILE, NULL, inspectionWindowFileName, MAX_PATH_LENGTH, configFileName);
	if (*inspectionWindowFileName != NULL)
	{
		std::string inspectionWindowFilePath = folderName + "\\" + std::string(inspectionWindowFileName);
		InspectionWindow.ReadRegion(inspectionWindowFilePath.c_str());
		isMasterImageInitialized = true;
	}
	else
	{
		isMasterImageInitialized = false;
	}
	//repAnchor
	char repAnchorDir[300];
	GetPrivateProfileStringA(APP_NAME, REP_ANCHOR_DIR_KEY, NULL, repAnchorDir, 300, configFileName);
	if (*repAnchorDir != NULL)
	{
		std::string repAnchorDirPath = folderName + '\\' + repAnchorDir;
		repAnchor.ReadConfiguration(repAnchorDirPath);
	}

	//repRowRef
	char repRowRefFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_ROW_REF_KEY, NULL, repRowRefFileName, MAX_PATH_LENGTH, configFileName);
	if (*repRowRefFileName != NULL)
	{
		std::string repRowRefPath = folderName + '\\' + repRowRefFileName;
		ReadTuple(repRowRefPath.c_str(), &repRowRef);
	}
	//repColumnRef
	char repColumnRefFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_COLUMN_REF_KEY, NULL, repColumnRefFileName, MAX_PATH_LENGTH, configFileName);
	if (*repColumnRefFileName != NULL)
	{
		std::string repColumnRefPath = folderName + '\\' + repColumnRefFileName;
		ReadTuple(repColumnRefPath.c_str(), &repColumnRef);
	}
	//repAngleRef
	char repAngleRefFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_ANGLE_REF_KEY, NULL, repAngleRefFileName, MAX_PATH_LENGTH, configFileName);
	if (*repAngleRefFileName != NULL)
	{
		std::string repAngleRefPath = folderName + '\\' + repAngleRefFileName;
		ReadTuple(repAngleRefPath.c_str(), &repAngleRef);
	}
	//repRowAll
	char repRowAllFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_ROW_ALL_KEY, NULL, repRowAllFileName, MAX_PATH_LENGTH, configFileName);
	if (*repRowAllFileName != NULL)
	{
		std::string repRowAllPath = folderName + '\\' + repRowAllFileName;
		ReadTuple(repRowAllPath.c_str(), &repRowAll);
	}
	//repColumnAll
	char repColumnAllFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_COLUMN_ALL_KEY, NULL, repColumnAllFileName, MAX_PATH_LENGTH, configFileName);
	if (*repColumnAllFileName != NULL)
	{
		std::string repColumnAllPath = folderName + '\\' + repColumnAllFileName;
		ReadTuple(repColumnAllPath.c_str(), &repColumnAll);
	}
	//repAngleAll
	char repAngleAllFileName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, REP_ANGLE_ALL_KEY, NULL, repAngleAllFileName, MAX_PATH_LENGTH, configFileName);
	if (*repAngleAllFileName != NULL)
	{
		std::string repAngleAllPath = folderName + '\\' + repAngleAllFileName;
		ReadTuple(repAngleAllPath.c_str(), &repAngleAll);
	}

	//TaskCount
	int taskCount = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_TASKS, 0, configFileName);
	for (int index = 1; index <= taskCount; index++)
	{
		std::string TASK_APP_NAME = "TASK_" + std::to_string(index);
		int taskID = GetPrivateProfileIntA(TASK_APP_NAME.c_str(), TASK_ID, 0, configFileName);
		InspectionTypes taskType = (InspectionTypes)GetPrivateProfileIntA(TASK_APP_NAME.c_str(), TASK_TYPE, 0, configFileName);
		char taskFile[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(TASK_APP_NAME.c_str(), TASK_FILE, NULL, taskFile, MAX_PATH_LENGTH, configFileName);
		std::string taskDirPathStr = folderName + "\\" + std::string(taskFile);

		switch (taskType)
		{
		case inspection_type_None:
			inspectionTasks[taskID] = new InspectionData();
			break;

		case inspection_type_LayerInspection:
		case inspection_type_SpecialLayerInspection:
			inspectionTasks[taskID] = new LayerData();
			break;

		case inspection_type_ThreadDetection:
			inspectionTasks[taskID] = new ThreadData();
			break;
		case inspection_type_BlobAnalyser:
			inspectionTasks[taskID] = new BlobAnalyzerData();
			break;
		case inspection_type_Measurement:
			inspectionTasks[taskID] = new MeasurementData();
			break;
		default:
			inspectionTasks[taskID] = new InspectionData();
		}
		inspectionTasks[taskID]->ReadConfiguration(taskDirPathStr);
	}
	if (ReadTrainingSet)
	{
		// TrainingSet
		thisCameraTrainingSet.clear();
		int tsCount = GetPrivateProfileIntA(APP_NAME, TS_COUNT, 0, configFileName);
		for (int index = 1; index <= tsCount; index++)
		{
			std::string TS_APP_NAME = "TRAINING_SET_" + std::to_string(index);
			ULONG imageNumber = GetPrivateProfileIntA(TS_APP_NAME.c_str(), TS_NUMBER, 0, configFileName);

			TrainingImageData tempTrainingSetImageData;
			tempTrainingSetImageData.imgNumber = imageNumber;
			tempTrainingSetImageData.type = (TrainingSetType)GetPrivateProfileIntA(TS_APP_NAME.c_str(), TS_TYPE, 0, configFileName);
			tempTrainingSetImageData.isTrained = (bool)GetPrivateProfileIntA(TS_APP_NAME.c_str(), TS_ISTRAINED, 0, configFileName);

			char buff[20];
			GetPrivateProfileStringA(TS_APP_NAME.c_str(), TS_ADDEDTIME, NULL, buff, 20, configFileName);
			tempTrainingSetImageData.addedTime = strtoull(buff, NULL, 0);;

			char tsFileStr[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(TS_APP_NAME.c_str(), TS_FILE, NULL, tsFileStr, MAX_PATH_LENGTH, configFileName);

			std::string tsFilePathStr = folderName + "\\" + std::string(tsFileStr);
			tempTrainingSetImageData.image.ReadImage(tsFilePathStr.c_str());


			char tsRegFileStr[MAX_PATH_LENGTH];
			GetPrivateProfileStringA(TS_APP_NAME.c_str(), TS_MASK_FILE, NULL, tsRegFileStr, MAX_PATH_LENGTH, configFileName);

			if (*tsRegFileStr != NULL)
			{
				std::string tsRegFilePathStr = folderName + "\\" + std::string(tsRegFileStr);
				tempTrainingSetImageData.maskRegion.ReadRegion(tsRegFilePathStr.c_str());
			}
			else
			{
				tempTrainingSetImageData.maskRegion.GenEmptyRegion();
			}

			thisCameraTrainingSet.push_back(tempTrainingSetImageData);
		}
	}

}


void CameraData::WriteConfiguration(std::string folderName)
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	DWORD ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}
	//cameraID
	std::string cameraIDStr = std::to_string(cameraID);
	WritePrivateProfileStringA(APP_NAME, CAMERA_ID, cameraIDStr.c_str(), configFileName);
	//Number Of UPs
	std::string numberOfUpsString = std::to_string(numberOfUps);
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_UPS, numberOfUpsString.c_str(), configFileName);
	//Number Of Panels
	std::string numberOfPanelsString = std::to_string(numberOfPanels);
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_PANELS, numberOfPanelsString.c_str(), configFileName);
	//taskID
	std::string taskIDString = std::to_string(taskID);
	WritePrivateProfileStringA(APP_NAME, TASK_ID, taskIDString.c_str(), configFileName);
	//taskType
	std::string taskTypeString = std::to_string((int)typeOfInspectionTask);
	WritePrivateProfileStringA(APP_NAME, TASK_TYPE, taskTypeString.c_str(), configFileName);
	//taskName
	WritePrivateProfileStringA(APP_NAME, TASK_NAME, taskName.c_str(), configFileName);
	//Master Image
	std::string masterImageFileStr = "MasterImage.bmp";
	WritePrivateProfileStringA(APP_NAME, MASTER_IMAGE_FILE, masterImageFileStr.c_str(), configFileName);
	std::string masterImageFilePath = folderName + "\\" + masterImageFileStr;
	masterImage.WriteImage("bmp", 0, masterImageFilePath.c_str());
	//Master Image Reduced
	std::string masterImageReducedFileStr = "MasterImageReduced.bmp";
	WritePrivateProfileStringA(APP_NAME, MASTER_IMAGE_REDUCED_FILE, masterImageReducedFileStr.c_str(), configFileName);
	std::string masterImageReducedFilePath = folderName + "\\" + masterImageReducedFileStr;
	masterImageReduced.WriteImage("bmp", 0, masterImageReducedFilePath.c_str());
	//Master IR Image
	std::string masterIRImageFileStr = "MasterIRImage.bmp";
	WritePrivateProfileStringA(APP_NAME, MASTER_IR_IMAGE_FILE, masterIRImageFileStr.c_str(), configFileName);
	std::string masterIRImageFilePath = folderName + "\\" + masterIRImageFileStr;
	masterIRImage.WriteImage("bmp", 0, masterIRImageFilePath.c_str());
	//Inspection Window
	std::string inspectionWindowFileStr = "InspectionWindow.reg";
	WritePrivateProfileStringA(APP_NAME, INSPECTION_WINDOW_FILE, inspectionWindowFileStr.c_str(), configFileName);
	std::string inspectionWindowFilePath = folderName + "\\" + inspectionWindowFileStr;
	InspectionWindow.WriteRegion(inspectionWindowFilePath.c_str());
	//repAnchor
	std::string repAnchorDir = "repAnchor_" + std::to_string(repAnchor.taskID);
	WritePrivateProfileStringA(APP_NAME, REP_ANCHOR_DIR_KEY, repAnchorDir.c_str(), configFileName);

	std::string repAnchorDirPath = folderName + '\\' + repAnchorDir;
	CreateDirectoryA(repAnchorDirPath.c_str(), NULL);
	repAnchor.WriteConfiguration(repAnchorDirPath);

	//repRowRef
	std::string repRowRefFileName = "repRowRef.tup";
	WritePrivateProfileStringA(APP_NAME, REP_ROW_REF_KEY, repRowRefFileName.c_str(), configFileName);
	std::string repRowRefPath = folderName + '\\' + repRowRefFileName;
	repRowRef.WriteTuple(repRowRefPath.c_str());
	//repColumnRef
	std::string repColumnRefFileName = "repColumnRef.tup";
	WritePrivateProfileStringA(APP_NAME, REP_COLUMN_REF_KEY, repColumnRefFileName.c_str(), configFileName);
	std::string repColumnRefPath = folderName + '\\' + repColumnRefFileName;
	repColumnRef.WriteTuple(repColumnRefPath.c_str());
	//repAngleRef
	std::string repAngleRefFileName = "repAngleRef.tup";
	WritePrivateProfileStringA(APP_NAME, REP_ANGLE_REF_KEY, repAngleRefFileName.c_str(), configFileName);
	std::string repAngleRefPath = folderName + '\\' + repAngleRefFileName;
	repAngleRef.WriteTuple(repAngleRefPath.c_str());
	//repRowAll
	std::string repRowAllFileName = "repRowAll.tup";
	WritePrivateProfileStringA(APP_NAME, REP_ROW_ALL_KEY, repRowAllFileName.c_str(), configFileName);
	std::string repRowAllPath = folderName + '\\' + repRowAllFileName;
	repRowAll.WriteTuple(repRowAllPath.c_str());
	//repColumnAll
	std::string repColumnAllFileName = "repColumnAll.tup";
	WritePrivateProfileStringA(APP_NAME, REP_COLUMN_ALL_KEY, repColumnAllFileName.c_str(), configFileName);
	std::string repColumnAllPath = folderName + '\\' + repColumnAllFileName;
	repColumnAll.WriteTuple(repColumnAllPath.c_str());
	//repAngleAll
	std::string repAngleAllFileName = "repAngleAll.tup";
	WritePrivateProfileStringA(APP_NAME, REP_ANGLE_ALL_KEY, repAngleAllFileName.c_str(), configFileName);
	std::string repAngleAllPath = folderName + '\\' + repAngleAllFileName;
	repAngleAll.WriteTuple(repAngleAllPath.c_str());

	//TaskCount
	std::string taskCountStr = std::to_string(inspectionTasks.size());
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_TASKS, taskCountStr.c_str(), configFileName);
	int index = 1;
	for (auto &e : inspectionTasks)
	{
		std::string TASK_APP_NAME = "TASK_" + std::to_string(index);
		WritePrivateProfileStringA(TASK_APP_NAME.c_str(), TASK_ID, std::to_string(e.first).c_str(), configFileName);
		WritePrivateProfileStringA(TASK_APP_NAME.c_str(), TASK_TYPE, std::to_string(e.second->typeOfInspectionTask).c_str(), configFileName);
		std::string taskDirStr = "Task_" + std::to_string(e.first);
		WritePrivateProfileStringA(TASK_APP_NAME.c_str(), TASK_FILE, taskDirStr.c_str(), configFileName);
		std::string taskDirPathStr = folderName + "\\" + taskDirStr;
		CreateDirectoryA(taskDirPathStr.c_str(), NULL);
		e.second->WriteConfiguration(taskDirPathStr);
		index++;
	}
	std::string tsCountStr = std::to_string(thisCameraTrainingSet.size());
	WritePrivateProfileStringA(APP_NAME, TS_COUNT, tsCountStr.c_str(), configFileName);
	index = 1;
	for (auto &e : thisCameraTrainingSet)
	{
		std::string TS_APP_NAME = "TRAINING_SET_" + std::to_string(index);
		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_NUMBER, std::to_string(e.imgNumber).c_str(), configFileName);
		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_TYPE, std::to_string(e.type).c_str(), configFileName);
		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_ISTRAINED, std::to_string(e.isTrained).c_str(), configFileName);
		char timeString[100];
		sprintf(timeString, "%ulld", (__int64)e.addedTime);
		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_ADDEDTIME, timeString, configFileName);

		std::string tsFileStr;
		if (e.type == BasicTrainingSet)
		{
			tsFileStr = "Base TrainingSet " + std::to_string(e.imgNumber) + ".bmp";
		}
		else
		{
			tsFileStr = "Extended TrainingSet " + std::to_string(e.imgNumber) + ".bmp";
		}

		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_FILE, tsFileStr.c_str(), configFileName);
		std::string tsFilePathStr = folderName + "\\" + tsFileStr;

		ftyp = GetFileAttributesA(tsFilePathStr.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
		{
			e.image.WriteImage("bmp", 0, tsFilePathStr.c_str());
		}

		std::string tsFileRegStr;
		if (e.type == BasicTrainingSet)
		{
			tsFileRegStr = "Base TrainingSet " + std::to_string(e.imgNumber) + " Mask.reg";
		}
		else
		{
			tsFileRegStr = "Extended TrainingSet " + std::to_string(e.imgNumber) + " Mask.reg";
		}
		WritePrivateProfileStringA(TS_APP_NAME.c_str(), TS_MASK_FILE, tsFileRegStr.c_str(), configFileName);
		std::string tsFileRegPathStr = folderName + "\\" + tsFileRegStr;

		ftyp = GetFileAttributesA(tsFileRegPathStr.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
		{
			e.maskRegion.WriteRegion(tsFileRegPathStr.c_str());
		}
		index++;
	}
}


GoldenData::GoldenData()
{
	goldenName = "";
	numberOfUps = 0;
	numberOfPanels = 0;
	numberOfCameras = 1;

	CameraData tempCameraData;
	allCameraData[1] = tempCameraData;
}


GoldenData::~GoldenData()
{
}

GoldenData::GoldenData(std::string &_goldenName, int _numberOfUps, int _numberOfPanels, int _numberOfCameras)
{
	goldenName = _goldenName;
	numberOfUps = _numberOfUps;
	numberOfPanels = _numberOfPanels;
	numberOfCameras = _numberOfCameras;

	for (int index = 1; index <= numberOfCameras; index++)
	{
		CameraData tempCameraData;
		allCameraData[index] = tempCameraData;
	}

	for (auto &e: allCameraData)
	{
		e.second.SetSheetDetails(_numberOfPanels, _numberOfUps);
	}
}


void GoldenData::AddTrainingSet(UINT _cameraID, ImageData &_imageData, TrainingSetType _type)
{
	int imgNumber = 1;
	if (allCameraData[_cameraID].thisCameraTrainingSet.size())
	{
		imgNumber += allCameraData[_cameraID].thisCameraTrainingSet.rbegin()->imgNumber;
	}
	TrainingImageData temp(_imageData.image, _imageData.irImage, imgNumber, _type);
	allCameraData[_cameraID].thisCameraTrainingSet.push_back(temp);
	trainingSetCount = allCameraData[_cameraID].thisCameraTrainingSet.size();
}

void GoldenData::AddTrainingSet(UINT _cameraID, TrainingImageData &_imageData)
{
	int imgNumber = 1;
	if (allCameraData[_cameraID].thisCameraTrainingSet.size())
	{
		imgNumber += allCameraData[_cameraID].thisCameraTrainingSet.rbegin()->imgNumber;
	}
	_imageData.imgNumber = imgNumber;
	_imageData.isTrained = false;
	allCameraData[_cameraID].thisCameraTrainingSet.push_back(_imageData);
	trainingSetCount = allCameraData[_cameraID].thisCameraTrainingSet.size();
}


int GoldenData::GetTrainingSetCount(UINT _cameraID)
{
	int count = allCameraData[_cameraID].thisCameraTrainingSet.size();
	return count;
}

HImage GoldenData::GetTraingSetImage(UINT _cameraID, UINT _imageIndex, HImage &_irTrainingImage)
{
	HImage tempImage = this->allCameraData[_cameraID].thisCameraTrainingSet[_imageIndex - 1].image.CopyImage();
	_irTrainingImage = this->allCameraData[_cameraID].thisCameraTrainingSet[_imageIndex - 1].irImage;
	HTuple maskAreaValues = HTuple::TupleGenConst(tempImage.CountChannels(), 255);
	tempImage.OverpaintRegion(this->allCameraData[_cameraID].thisCameraTrainingSet[_imageIndex - 1].maskRegion, maskAreaValues, HString("fill"));
	return tempImage;
}


int GoldenData::RemoveTrainingSet(UINT _cameraID, UINT _imageIndex)
{
	if (_imageIndex <= this->allCameraData[_cameraID].thisCameraTrainingSet.size())
	{
		this->allCameraData[_cameraID].thisCameraTrainingSet.erase(this->allCameraData[_cameraID].thisCameraTrainingSet.begin() + _imageIndex - 1);
	}
	return this->allCameraData[_cameraID].thisCameraTrainingSet.size();
}

bool GoldenData::ResetTrainingData(UINT _cameraID)
{
	for (auto &e : this->allCameraData[_cameraID].thisCameraTrainingSet)
	{
		e.isTrained = false;
	}
	for (auto &e : this->allCameraData[_cameraID].inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			LayerData *tempLayerData = static_cast<LayerData *>(e.second);
			tempLayerData->ResetMinMaxData();
		}
	}
	return true;
}

bool GoldenData::isMasterAssigned(UINT _cameraID)
{
	bool returnValue = false;
	if (this->allCameraData[_cameraID].masterImage.IsInitialized() && this->allCameraData[_cameraID].masterIRImage.IsInitialized())
	{
		returnValue = true;
	}
	return returnValue;
}


bool GoldenData::SetMaster(UINT _cameraID, HImage &_masterNote, HImage &_irImage)
{
	bool returnValue = true;
	this->allCameraData[_cameraID].masterImage = _masterNote;
	this->allCameraData[_cameraID].masterIRImage = _irImage;
	return returnValue;
}

bool GoldenData::RemoveMaster(UINT _cameraID)
{
	bool returnValue = true;
	this->allCameraData[_cameraID].masterImage.Clear();
	return returnValue;
}

void GoldenData::SetGoldenData(std::string &_goldenName, int _numberOfUps, int _numberOfPanels, int _numberOfCameras)
{
	goldenName = _goldenName;
	numberOfUps = _numberOfUps;
	numberOfPanels = _numberOfPanels;
	numberOfCameras = _numberOfCameras;

	for (auto &e : allCameraData)
	{
		e.second.SetSheetDetails(_numberOfPanels, _numberOfUps);
	}
}

void GoldenData::ReadConfiguration(std::string folderName, bool ReadTrainingSet)
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", folderName.c_str(), CONFIG_NAME);
	//GoldenName
	char tempGoldenName[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, GOLDEN_NAME, NULL, tempGoldenName, MAX_PATH_LENGTH, configFileName);
	goldenName = std::string(tempGoldenName);

	//Number Of UPs
	numberOfUps = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_UPS, 0, configFileName);
	//Number Of Panels
	numberOfPanels = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_PANELS, 0, configFileName);
	//TS count
	trainingSetCount = GetPrivateProfileIntA(APP_NAME, TS_COUNT, 0, configFileName);
	//number of cameras
	numberOfCameras = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_CAMERAS, 0, configFileName);
	allCameraData.clear();

	for (int index = 1; index <= numberOfCameras; index++)
	{
		std::string CAMERA_APP_NAME = "CAMERA" + std::to_string(index);
		int camID = GetPrivateProfileIntA(CAMERA_APP_NAME.c_str(), CAMERA_ID, 0, configFileName);
		char cameraDir[MAX_PATH_LENGTH];
		GetPrivateProfileStringA(CAMERA_APP_NAME.c_str(), CAMERA_FILE, NULL, cameraDir, MAX_PATH_LENGTH, configFileName);
		std::string cameraDirPath = folderName + '\\' + std::string(cameraDir);
		allCameraDataLocation[camID] = cameraDirPath;
		allCameraData[camID] = CameraData();
		allCameraData[camID].ReadConfiguration(cameraDirPath.c_str(), ReadTrainingSet);
	}
}

void GoldenData::WriteConfiguration(std::string folderName)
{
	DWORD ftyp = GetFileAttributesA(folderName.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(folderName.c_str(), NULL);
	}

	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, "%s\\%s", folderName.c_str(), CONFIG_NAME);

	ftyp = GetFileAttributesA(configFileName);
	if (ftyp != INVALID_FILE_ATTRIBUTES)
	{
		remove(configFileName);
	}

	//GoldenName
	WritePrivateProfileStringA(APP_NAME, GOLDEN_NAME, goldenName.c_str(), configFileName);
	//Number Of UPs
	std::string numberOfUpsString = std::to_string(numberOfUps);
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_UPS, numberOfUpsString.c_str(), configFileName);
	//Number Of Panels
	std::string numberOfPanelsString = std::to_string(numberOfPanels);
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_PANELS, numberOfPanelsString.c_str(), configFileName);
	//TS count
	std::string tsCountString = std::to_string(trainingSetCount);
	WritePrivateProfileStringA(APP_NAME, TS_COUNT, tsCountString.c_str(), configFileName);
	//number of cameras
	std::string cameraCountString = std::to_string(numberOfCameras);
	WritePrivateProfileStringA(APP_NAME, NUMBER_OF_CAMERAS, cameraCountString.c_str(), configFileName);

	int index = 1;
	for (auto &e : allCameraData)
	{
		std::string cameraDir = "Camera_" + std::to_string(e.first);
		std::string CAMERA_APP_NAME = "CAMERA" + std::to_string(index);
		std::string camIDStr = std::to_string(e.first);
		WritePrivateProfileStringA(CAMERA_APP_NAME.c_str(), CAMERA_ID, camIDStr.c_str(), configFileName);
		WritePrivateProfileStringA(CAMERA_APP_NAME.c_str(), CAMERA_FILE, cameraDir.c_str(), configFileName);

		std::string cameraDirPath = folderName + '\\' + cameraDir;
		CreateDirectoryA(cameraDirPath.c_str(), NULL);
		e.second.WriteConfiguration(cameraDirPath);
		index++;
	}
}


NewGoldenDetails::NewGoldenDetails()
{

}

NewGoldenDetails::~NewGoldenDetails()
{

}