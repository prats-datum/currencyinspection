#pragma once
#include "stdafx.h"
#include "Halconcpp.h"
#include "IPAException.h"
#include <algorithm> 
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <map>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/memory.hpp>


using namespace std;
//using namespace Halcon;
using namespace HalconCpp;

//#define USE_GPU
//#define DIOENABLED 0
//USER DEFINED MESSAGES

#define UWM_NEW_GOLDEN (WM_USER + 1)
#define UWM_START_CAPTURE_TS (WM_USER + 2)
#define UWM_STOP_CAPTURE_TS (WM_USER + 3)
#define UWM_TS_CAPTURE_STATUS (WM_USER + 4)
#define UWM_SELECT_MASTER_IMAGE (WM_USER + 5)
#define UWM_MASTER_IMAGE_SELECTED (WM_USER + 6)
#define UWM_REG_NAME_RECEIVED (WM_USER + 7)
#define UWM_DISABLE_ALL_OPERATIONS (WM_USER + 8)
#define UWM_ENABLE_ALL_OPERATIONS (WM_USER + 9)
#define UWM_INSPECTION_REGION_CLICKED (WM_USER + 10)
#define UWM_MODIFY_GOLDEN_RECEIVED (WM_USER + 11)
#define UWM_IMAGE_EXTEND_COMPLETED (WM_USER + 12)
#define UWM_IMAGE_EXTEND_ERROR (WM_USER + 13)
#define UWM_IMAGE_MODEL_BUILD_ENDED (WM_USER + 14)
#define UWM_START_SHIFT_RECEIVED (WM_USER + 15)
#define UWM_CAMERA_RESULT_RECEIVED (WM_USER + 16)
#define UWM_REQUEST_RESULT_BUFFER (WM_USER + 17)
#define UWM_SEND_RESULT_BUFFER (WM_USER + 18)
#define UWM_SEND_LEARN_DEFECT (WM_USER + 19)
#define UWM_EXTEND_GOLDEN_DATA (WM_USER + 20)
#define UWM_CHANGE_IMAGE_TRAININGSTATUS (WM_USER + 21)
#define UWM_UPDATE_WAIT_SCREEN_STATUS (WM_USER + 22)
#define UWM_RESET_WAIT_SCREEN_STATUS (WM_USER + 23)
#define UWM_UPDATE_CURRENT_MEASUREMENT_VALUE (WM_USER + 24)
#define UWM_MASTER_IMAGE_SELECTION_FAILED (WM_USER + 25)
#define UWM_LOG_MESSAGE (WM_USER + 26)
#define UWM_TS_CAPTURE_FAILURE (WM_USER + 27)
#define UWM_MACHINE_STATE_CHANGED (WM_USER + 28)
#define UWM_PRINTING_STATE_CHANGED (WM_USER + 29)

//Macros

#define MAX_NUM_OF_CAMERAS 5
#define MAX_NUM_OF_COLOR_CHANNELS 5
#define MAX_NUM_OF_LAYERS_PER_CAMERA 3
#define MAX_NUM_OF_MEASUREMENTS_PER_CAMERA 3
#define MAX_NUM_OF_NOTES_PER_SHEET 100
#define MAX_NO_OF_SENSITIVITY_LEVELS 7
#define MAX_NO_OF_BLOB_PARAMETERS_GROUP 3
#define SAFE_EXIT_TIME_DELAY 3000
#define MAX_NO_OF_INSPECTION_TASKS 20

#define IMAGE_BUFFER_SIZE 10
#define RESULT_BUFFER_SIZE 10
#define MAX_DOCUMENT_RESULTS_COUNT 20
#define MAX_ERROR_MESSAGE_LENGTH 200
#define MAX_PATH_LENGTH 500
#define MAX_GPU_NAME_LENGTH 50

#define LAYER_STARTING_ID 0

#define ANCHOR_REGION_STARTING_ID 1000
#define INSPECTION_REGION_STARTING_ID 10000
#define MASK_REGION_STARTING_ID 20000
#define STATISTICS_REGION_STARTING_ID 30000
#define MASK_RESULT_TIME_OUT 200
#define TP_RESULT_TIME_OUT 300
#define LAYER_RESULT_TIME_OUT 400
#define RESULT_TIMEOUT 400

#define MAX_RESULT_LOG_COUNT 1000
#define IPA_LOGS_DIRECTORY "./Timing Logs"
const char IPA_LOG_CONFIG_FILE_NAME[] = "I:/Lucid/Assignments/CISys V2/Source Code/CurrencyInspectionSystem/CurrencyInspectionSystem/Configuration Files/Log.Config";          // log properties file name

#define CREATE_GOLDEN_STRING "Create Golden"
#define UPDATE_GOLDEN_STRING "Update Golden"

//Layer ErrorStrings
#define TIEPOINT_NOT_FOUND "Tie-point not found"
#define MASK_NOT_RECIEVED "Mask not recieved"

//Golbal INI tags
static const char *TASK_ID_KEY = "TaskID";
static const char *TASK_TYPE_KEY = "TaskType";
static const char *ENABLED_KEY = "Enabled";
static const char *TASK_NAME_KEY = "TaskName";
static const char *REGION_TYPE = "RegionType";
//

#define DialogBackgroundColor        ((COLORREF)(((BYTE)(45)|((WORD)((BYTE)(60))<<8))|(((DWORD)(BYTE)(75))<<16)))
#define DialogTextColor       ((COLORREF)(((BYTE)(0)|((WORD)((BYTE)(0))<<8))|(((DWORD)(BYTE)(0))<<16)))
#define DialogStaticTextColor       ((COLORREF)(((BYTE)(255)|((WORD)((BYTE)(255))<<8))|(((DWORD)(BYTE)(255))<<16)))
#define DialogButtonColor       ((COLORREF)(((BYTE)(20)|((WORD)((BYTE)(35))<<8))|(((DWORD)(BYTE)(65))<<16)))

#define RESULTS_LOG_NEEDED



enum OperationMode : char
{
	StartupMode = 0,
	GoldenCreationMode = 1,
	InspectionMode = 2
};

enum ImageSourceType : char
{
	File = 0,
	Camera = 1,
	Buffer = 2
};

enum CameraType : char
{
	RGB = 1,
	Mono = 2,
	RGBIR = 3
};

enum RegionTypes : char
{
	UniqueInspectionRegion = 0,
	UniqueMaskRegion = 1,
	RepititiveInspectionRegion = 2,
	RepititiveMaskRegion = 3,
	StatisticsRegion = 4,
	AnchorRegion = 5,
	RepAnchorRegion = 6,
	ThreadRegion = 7,
	MeasurementRegion = 8
};

enum SearchType : char
{
	ShapeBased = 0,
	GrayValueBased = 1,
	SourceTaskBased = 2
};

enum GoldenModifyOperation : char
{
	Edit = 0,
	Delete = 1
};

enum SensitivityLevels : char
{
	Level1 = 0,
	Level2 = 1,
	Level3 = 2,
	Level4 = 3,
	Level5 = 4,
	Custom1 = 5,
	Custom2 = 6
};

enum BlobParametersGroups : char
{
	Group1 = 0,
	Group2 = 1,
	Group3 = 2
};

enum ColorChannelType : char
{
	L = 0,
	A = 1,
	B = 2,
	E = 3,
	VE = 4,
	I = 5
};

enum ApplicationStates : char
{
	StartupState = 0,
	NewGoldenInitailState = 1,
	NewGoldenTSCapturedState = 2,
	InspectionState = 3
};


enum InspectionResults
{
	NotChecked = -1,
	Error = 0,
	Fail = 1,
	Pass = 2,
	NotDefined = 3
};

enum Severity
{
	none = 0,
	info = 1,
	warning = 2,
	error = 3
};

enum InspectionTypes
{
	inspection_type_None = 0,                            // no inspection algo specified
	inspection_type_TiePoint = 1,						 // tie point detection algo
	inspection_type_LayerInspection = 2,                 // Layer Inspection algo
	inspection_type_SpecialLayerInspection = 3,          // Special Layer Inspection algo
	inspection_type_ThreadDetection = 4,				 // Thread inspection algo
	inspection_type_Measurement = 5,					 // Measurement inspection algo
	inspection_type_BlobAnalyser = 6,					 // BlobAnalyser algo
	inspection_type_Camera = 7
};

enum TrainingSetType
{
	BasicTrainingSet = 0,
	ExtensionTrainingSet = 1
};

enum DefectBlobType
{
	MajorBlob = 0,
	DominantBlob = 1,
	HighlightingRegion = 2
};

enum LearningType
{
	LearnMajorBlob = 0,
	LearnDominantBlob = 1,
	LearnCompleteImage = 2
};


struct ColorChannel
{
	std::string name;
	ColorChannelType type;
};

struct ColorChannelConfig
{
public:
	int numOfColorChannels;
	std::vector<ColorChannel> DefaultColorChannels;
};

struct CameraConfig
{
	std::string cameraName;
	UINT cameraID;
	CameraType cameraType;
	UINT fgIndex;
	UINT dmaIndex;
	int bytesPerPixel;
	int imageWidth;
	int imageHeight;
	int imageBufferCount;
	int timeout;
	int allowedBufferedImageCount;
	int numberOfLightSticks;
	int numberOfFFCGains;
	std::vector<UINT> lightSticksLevel;
	std::vector<double> ffcGain;
};

struct Shift
{
	int shiftIndex;
	string shiftDate;
	string shiftName;
	vector<time_t> shiftStartedTime;
	vector<time_t> shiftEndedTime;
	string goldenName;
	string userID;
	ULONG elapsedTime=0;
	ULONG lastImagenumber;
	Shift() {};
	Shift(int _shIn, string _shDt, string _shN, vector<time_t>  _shST, vector<time_t>  _shET,
		string _gN, string _shUID, ULONG _shElT, ULONG _shLiM) :shiftIndex(_shIn),
		shiftDate(_shDt), shiftName(_shN), shiftStartedTime(_shST), shiftEndedTime(_shET),
		goldenName(_gN), userID(_shUID), elapsedTime(_shElT), lastImagenumber(_shLiM){}

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			CEREAL_NVP(shiftIndex),
			CEREAL_NVP(shiftDate),
			CEREAL_NVP(shiftName),
			CEREAL_NVP(shiftStartedTime),
			CEREAL_NVP(shiftEndedTime),
			CEREAL_NVP(goldenName),
			CEREAL_NVP(userID),
			CEREAL_NVP(elapsedTime),
			CEREAL_NVP(lastImagenumber)
		);
	}

};

struct ShiftTypes
{
	std::string shiftName;
	byte shiftStartHour;
	byte totalShiftHours;
	int perHourTarget;
};

class SensitivityLevelParameterLookup
{
public:
	HTuple tolerance, limit, gain;
	SensitivityLevelParameterLookup()
	{
		tolerance = tolerance.TupleGenConst(MAX_NUM_OF_COLOR_CHANNELS, 10);
		limit = limit.TupleGenConst(MAX_NUM_OF_COLOR_CHANNELS, 20);
		gain = gain.TupleGenConst(MAX_NUM_OF_COLOR_CHANNELS, 1.0);
	}

};

class BlobParameterLookup
{
public:
	int globalTolerance, majorBlobThreshold, dominantBlobThreshold, groupOfBlobThreshold;
	BlobParameterLookup()
	{
		globalTolerance = 2;
		majorBlobThreshold = 10;
		dominantBlobThreshold = 600;
		groupOfBlobThreshold = 1000;
	}

};

class InspectionToleranceParametersLookup
{
public:
	SensitivityLevelParameterLookup sensitivityLevelParameterLookup[MAX_NO_OF_SENSITIVITY_LEVELS];
	BlobParameterLookup blobParameterLookup[MAX_NO_OF_BLOB_PARAMETERS_GROUP];
};
class ImageData
{
public:
	ImageData()
	{

	}
	~ImageData()
	{

	}
	ImageData(const ImageData &_imageData)
	{
		imageNumber = _imageData.imageNumber;
		cameraID = _imageData.cameraID;
		timeStamp = _imageData.timeStamp;
		encoderCount = _imageData.encoderCount;
		image = _imageData.image.CopyImage();
		irImage = _imageData.irImage.CopyImage();
	}
	unsigned long           imageNumber;                                    // image Number
	double                  timeStamp;                                      // image acquisition timestamp 
	HImage                  image;                                          // image dat
	HImage					irImage;
	double					encoderCount;
	UINT					cameraID;
};

class TrainingImageData
{
public:
	ULONG imgNumber;
	HImage image;
	HImage irImage;
	HRegion maskRegion;
	time_t addedTime;
	bool isTrained;
	TrainingSetType type;
	TrainingImageData()
	{
		isTrained = false;
	}
	TrainingImageData(HImage _img, HImage _irImage, UINT _imgNumber, TrainingSetType _type)
	{
		image = _img;
		irImage = _irImage;
		imgNumber = _imgNumber;
		addedTime = time(0);
		/*char buff[20];
		strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&tempTime));
		addedTime = std::string(buff);*/
		isTrained = false;
		maskRegion.GenEmptyRegion();
		type = _type;
	}

	TrainingImageData(HImage _img, HImage _irImage, HRegion _maskRegion, UINT _imgNumber, TrainingSetType _type) : TrainingImageData(_img, _irImage, _imgNumber, _type)
	{
		maskRegion = _maskRegion;
	}

	//TrainingImageData(const TrainingImageData &_trainingSetImageData)
	//{
	//	addedTime = _trainingSetImageData.addedTime;
	//	isTrained = _trainingSetImageData.isTrained;
	//	image = _trainingSetImageData.image.CopyImage();
	//	type = _trainingSetImageData.type;
	//	imgNumber = _trainingSetImageData.imgNumber;
	//	maskRegion = _trainingSetImageData.maskRegion;
	//}
	~TrainingImageData()
	{

	}
};


class PreprocessedImageData
{
	void UpdateCompositeImages(const HRegion &inspectionWindow)
	{
		originalImageData.image = originalImageData.image.ReduceDomain(inspectionWindow).CropDomain();
		//originalImageData.irImage = originalImageData.irImage.ReduceDomain(inspectionWindow).CropDomain();
		compositeImages.clear();
		HImage imageRed, imageGreen, imageBlue, imageL, imageA, imageB, grayDilation, grayErosion, grayEdge, sobelImage, edgeImage, VedgeImage, grayImage;
		imageRed = originalImageData.image.Decompose3(&imageGreen, &imageBlue);
		imageL = imageRed.TransFromRgb(imageGreen, imageBlue, &imageA, &imageB, "cielab");
		compositeImages.push_back(imageL);
		compositeImages.push_back(imageA);
		compositeImages.push_back(imageB);
		//
		grayImage = originalImageData.image.Rgb1ToGray();
		grayDilation = grayImage.GrayDilationRect(3, 3);
		grayErosion = grayImage.GrayErosionRect(3, 3);
		grayEdge = grayErosion.AbsDiffImage(grayDilation, 1);
		edgeImage = grayEdge.InvertImage();
		compositeImages.push_back(edgeImage);

		grayDilation = grayImage.GrayDilationRect(1, 3);
		grayErosion = grayImage.GrayErosionRect(1, 3);
		grayEdge = grayErosion.AbsDiffImage(grayDilation, 1);
		VedgeImage = grayEdge.InvertImage();
		compositeImages.push_back(VedgeImage);

		compositeImages.push_back(grayImage);

		//compositeImages.push_back(edgeImage);
		//compositeImages.push_back(edgeImage);
		//compositeImages.push_back(edgeImage);
		//compositeImages.push_back(edgeImage);
		//compositeImages.push_back(edgeImage);
		//compositeImages.push_back(grayImage);
	}

public:
	PreprocessedImageData()
	{

	}
	~PreprocessedImageData()
	{

	}
	ImageData originalImageData;
	std::vector<HImage> compositeImages;

	PreprocessedImageData(ImageData &_originalImageData, HRegion &inspectionWindow)
	{
		originalImageData = _originalImageData;
		UpdateCompositeImages(inspectionWindow);
	}

	PreprocessedImageData(const PreprocessedImageData &_preprocessedImageData)
	{
		originalImageData = _preprocessedImageData.originalImageData;
		compositeImages.clear();
		for (auto &image : _preprocessedImageData.compositeImages)
		{
#ifdef USE_GPU
			compositeImages.push_back(image.CopyImage());
#else
			compositeImages.push_back(image);
#endif

		}
	}

	//PreprocessedImageData CopyImage()
	//{
	//	PreprocessedImageData imageData;
	//	imageData.originalImageData = originalImageData;
	//	imageData.compositeImages.clear();
	//	for (auto &image : compositeImages)
	//	{
	//		imageData.compositeImages.push_back(image.CopyImage());
	//	}
	//	return imageData;
	//}
};


class PreprocessedTrainingImageData
{
	void UpdateCompositeImages(const HRegion &inspectionWindow)
	{
		try
		{
			//originalImageData.image.SetGrayval(0, 0, originalImageData.image.GetGrayval(0, 0));
			originalImageData.image = originalImageData.image.ReduceDomain(inspectionWindow).CropDomain();
			//originalImageData.irImage = originalImageData.irImage.ReduceDomain(inspectionWindow).CropDomain();
			Hlong row1, column1, row2, column2;
			inspectionWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
			HHomMat2D affineTrainsMatrix;
			affineTrainsMatrix.VectorAngleToRigid(row1, column1, 0.0, 0.0, 0.0, 0.0);
			originalImageData.maskRegion = originalImageData.maskRegion.AffineTransRegion(affineTrainsMatrix, "nearest_neighbor");


			compositeImages.clear();
			HImage imageRed, imageGreen, imageBlue, imageL, imageA, imageB, grayDilation, grayErosion, grayEdge, sobelImage, edgeImage, VedgeImage, grayImage;
			imageRed = originalImageData.image.Decompose3(&imageGreen, &imageBlue);
			imageL = imageRed.TransFromRgb(imageGreen, imageBlue, &imageA, &imageB, "cielab");
			compositeImages.push_back(imageL);
			compositeImages.push_back(imageA);
			compositeImages.push_back(imageB);

			grayImage = originalImageData.image.Rgb1ToGray();
			grayDilation = grayImage.GrayDilationRect(3, 3);
			grayErosion = grayImage.GrayErosionRect(3, 3);
			grayEdge = grayErosion.AbsDiffImage(grayDilation, 1);
			edgeImage = grayEdge.InvertImage();
			compositeImages.push_back(edgeImage);

			grayDilation = grayImage.GrayDilationRect(1, 3);
			grayErosion = grayImage.GrayErosionRect(1, 3);
			grayEdge = grayErosion.AbsDiffImage(grayDilation, 1);
			VedgeImage = grayEdge.InvertImage();
			compositeImages.push_back(VedgeImage);

			compositeImages.push_back(grayImage);

			//compositeImages.push_back(edgeImage);
			//compositeImages.push_back(edgeImage);
			//compositeImages.push_back(edgeImage);
			//compositeImages.push_back(edgeImage);
			//compositeImages.push_back(edgeImage);
			//compositeImages.push_back(grayImage);
		}
		catch (HException &ex)
		{
			std::string errorMessage = ex.ErrorMessage().Text();
		}
	}

public:
	PreprocessedTrainingImageData()
	{

	}
	~PreprocessedTrainingImageData()
	{
		HTuple type, width, height;
		for (auto &image : compositeImages)
		{
			image.GetImagePointer1(&type, &width, &height);
		}
	}
	TrainingImageData originalImageData;
	std::vector<HImage> compositeImages;

	PreprocessedTrainingImageData(TrainingImageData &_originalImageData, HRegion &inspectionWindow)
	{
		originalImageData = _originalImageData;
		UpdateCompositeImages(inspectionWindow);
	}
};



class iExtendedTrainingSetReceiver
{
public:
	virtual void OnExtendedTrainingSetReceived(UINT cameraID, TrainingImageData _trainingSetData) = 0;
};



class iTrainingSetStatusReceiver
{
public:
	virtual void OnTrainingSetExceptionReceived(UINT trainingSetNumber, char *exceptionMessage) {}
	virtual void OnTrainingSetBuildStaus(UINT trainingSetNumber, bool status) {}
};

struct ImageSourceSettings
{
public:
	std::string cameraName;
	ImageSourceType imageSourceType;
	std::string imageFilesPath;
	std::string configFilePath;

	std::string GetConfiguration()
	{
		return (imageSourceType == ImageSourceType::Camera) ? configFilePath : imageFilesPath;
	}
};




class DefectData
{
public:
	UINT defectID;
	HRegion defectRegion;
	HRegion highlightingRegion;
	HRegion zoomWindowRegion;
	double defectValue;
	double defectSize;
	DefectBlobType defectBlobType;
	bool isInitialized;
	bool isTrained;
	DefectData()
	{

	}
	~DefectData()
	{
		defectRegion.Clear();
		highlightingRegion.Clear();
		zoomWindowRegion.Clear();
	}
	void Set(HRegion &_defectRegion, double &_defectValue, UINT _defectID, DefectBlobType _defectBlobType, bool _isTrained)
	{
		defectID = _defectID;
		defectRegion = _defectRegion.DilationCircle(5.0);
		highlightingRegion = defectRegion.ShapeTrans("rectangle1").DilationRectangle1(100, 100);
		Hlong row1, column1, row2, column2;
		highlightingRegion.SmallestRectangle1(&row1, &column1, &row2, &column2);
		HHomMat2D regionTransMatrix;
		regionTransMatrix.VectorAngleToRigid(row1, column1, 0.0, 0.0, 0.0, 0.0); // To transfer Region to Zoom Window
		zoomWindowRegion = regionTransMatrix.AffineTransRegion(defectRegion, "nearest_neighbor");
		//zoomWindowRegion = zoomWindowRegion.DilationCircle(5.0);
		//zoomWindowRegion = zoomWindowRegion.Boundary("outer");
		defectValue = _defectValue;
		defectSize = _defectRegion.Area();
		defectBlobType = _defectBlobType;
		isTrained = _isTrained;
		isInitialized = true;
	}
	void Reset()
	{
		defectRegion.GenEmptyObj();
		highlightingRegion.GenEmptyObj();
		zoomWindowRegion.GenEmptyObj();
		defectValue = -1;
		defectSize = -1;
		isInitialized = false;
	}
};

class iStatusUpdateReceiver
{
public:
	virtual void UpdateStatus(std::string status, bool isErrorStaus) = 0;
};


class HalconCerealize
{
public:
	HalconCerealize() {}
	~HalconCerealize() {}
	void HTupleCerealize(HTuple tup, string *temp)
	{
		stringbuf buffer;
		ostream out(&buffer);
		HSerializedItem writeTup = tup.SerializeTuple();
		writeTup.Serialize(out);
		*temp = buffer.str();
		std::transform(temp->begin(), temp->end(), temp->begin(), [](int x) {return x + 5; });
	}

	void HTupleDeCerealize(string str, HTuple *temp)
	{
		
		stringbuf buffer;
		std::transform(str.begin(), str.end(), str.begin(), [](int x) {return x - 5; });
		buffer.sputn(str.c_str(), str.size());
		istream in(&buffer);
		HSerializedItem readTup = readTup.Deserialize(in);
		DeserializeTuple(readTup, temp);
		
	}
};

