#pragma once
#include <numeric>
#include <random>
#include <algorithm> 
#include <iterator>
#include <math.h>
#include <list>
#include <vector>
#include "ResultData.h"
#include "GoldenData.h"
#include "ChartViewer.h"

const int sampleSize = 240;
const int docSize = 100;
const int barDataSize = 10;
const int typeOfResults = 3;
const double stripheight = 0.8;
const double stripwidth = 1.5;
const double stripscale = 1.5;
const double maxDisplayEnergy = 15000;
const int titlebackgroundColor = 0x000f32;
const int chartbackgroundColor = 0x2d3c4b;
const int chartedgeColor = 0x000000;
const int fontColor = 0xff8401;
const int gridColor = 0x80ff8401;
const int labelColor = 0xffffff;
const int titleColor = 0xffffff;
const int semibackgroundColor = 0x80ff8401;
const int percentageTextColor = 0xFFFF00;
const int blueTextColor = 0x0000FF;
const int measLineColor = 0xFF0000;
const int tolLineColor = 0x00FFFFFF;
const int bdbLineColor = 0x0000FF;
const int sobLineColor = 0xFF0000;


const string normalFont = "arial.ttf";
const string boldFont = "arialbd.ttf";

class ChartDataManager : public HalconCerealize
{
public:
	ChartDataManager();
	~ChartDataManager();
	bool isResume;
	shared_ptr<CameraResultData>camResultData;
	CameraData thisCameraModelData;
	ULONG imageNumber;
	int noOfRows, noOfCols;
	map< int, string> taskLabelIDs,temptaskLblIDs;
	vector<string>stripChartLabel;
	vector<int>stripCharttaskID;
	map<UINT, double [docSize]> stripChartData[typeOfResults];
	map<UINT, double [docSize]>stripChartDataX[typeOfResults];
	vector<int> taskwiseResultCount[typeOfResults];
	vector<double>symbolheight;
	vector<double>symbolwidth;
	int docCount;
	vector<int> stripLabelCoordX, stripLabelCoordY,stripPercentCoordX;
	vector<double> stripYValues;
	LayerResultData *layerResult;
	MeasurementResultData *measResult;
	BlobAnalyzerResultData *baResult;
	ThreadResultData *thrResult;
	BlobAnalyzerData *baData;
	int baTaskID, baGroupID;
	map<UINT,LayerData *> layerData;
	MeasurementData *measData;
	std::vector<Measurement> measurementList;
	ThreadData *thrData;
	BlobParameterLookup blopAnalyzerParameterLookup;
	bool modelReceived,resultReceived;
	double resultPercentage[2];
	double balineDBData[docSize];
	double balineSoBData[docSize];
	double measlineVData[docSize];
	double measlineHData[docSize];
	double imagecountData[docSize];
	vector<double> heatMapX;
	vector<double> heatMapY;
	map<UINT, HTuple> statsCount, statsPercentage;
	map<UINT, HTuple> statsRegionNames, statsRegIDs;
	vector<double>hourlyDataX, hourlyFitDataY, hourlyUnfitDataY, hourlyFitPercentDataY, hourlyUnfitPercentDataY;
	CRITICAL_SECTION                 dataUpdateMutex;
	bool isStatChartDataAvailable, isMeasurementDataAvailable, isThreadDetectionAvailable;
	//vector<double> shiftMaxDominantDefectValue, shiftMaxSoBValue,
	//	bufferMaxDominantDefectValue, buffertMaxSoBValue,
	//	currentDominantDefectValue, currentSoBValue;
	map<UINT, HTuple> failureCount, failurePercentage;
	map<UINT, vector<double>> cerstripChartData, cerstripChartDataX;
	map<UINT, vector<double>>cerstatsCount,  cerstatsRegIDs, cerfailureCount, cerfailurePercentage, cerstatsPercentage;
	map < UINT, vector<string>> cerstatsRegionNames;
	HTuple onesTuple;
	void setTaskwiseModelData();
	void setModelData(CameraData &_cameraModelData);
	void initializeStatsCountData();
	void updateStatsData();
	void updateHeatmapData();
	void initializeStripChartData();
	void initializeLineChartData();
	void initializeTaskResultsCount();
	void initializeHeatMap();
	void setHeadingStyle(TextBox * cellStyle, int left, int right, int top, int bottom, int fontSize, int bkcolor);
	void setBoldFontStyle(TextBox * cellStyle, int left, int right, int top, int bottom, int fontSize, int edgeColor);
	void setNormalFontStyle(TextBox * cellStyle, int left, int right, int top, int bottom, int fontSize, int edgeColor);
	void initializeHourlyChartData();
	int setTaskwiseResultData();
	void setHeatMapModelData();
	void CerealizeHalconData();
	void DeCerealizeHalconData();
	void reportSheetPieChart(PieChart *c);
	void reportUpPieChart(PieChart *c);
	void reportFCHourlyChart(XYChart *c, Shift &shift);
	void reportStatRegSpoilageChart(XYChart *c);
	void reportTaskwiseSpoilageChart(XYChart * c);
	void reportUpSpoilageChart(XYChart *c);

	string GenerateReport(Shift & shift);


	std::string shiftName;
	vector<time_t> shiftStartedTime;
	vector<time_t> shiftEndedTime;
	std::string goldenName;
	byte shiftStartingHour;
	ULONG elapsedTime;
	byte totalShiftHours;
	int perHourTarget;
	string shiftDate;
	string userID;

	template<class Archive>
	void save(Archive & archive) const
	{
		archive(
			(imageNumber),
			(noOfRows),
			(noOfCols),
			(taskLabelIDs),
			(stripChartLabel),
			(stripCharttaskID),
			(stripLabelCoordX),
			(stripLabelCoordY),
			(stripPercentCoordX),
			(taskwiseResultCount),
			(symbolheight),
			(symbolwidth),
			(docCount),
			(stripYValues),
			(modelReceived),
			(resultReceived),
			(resultPercentage),
			(balineDBData),
			(balineSoBData),
			(baTaskID),
			(baGroupID),
			(measurementList),
			(measlineVData),
			(measlineHData),
			(imagecountData),
			(heatMapY),
			(heatMapX),
			(hourlyDataX),
			(hourlyFitDataY),
			(hourlyUnfitDataY),
			(hourlyFitPercentDataY),
			(hourlyUnfitPercentDataY),
			(cerstatsCount),
			(cerstatsPercentage),
			(cerstatsRegionNames),
			(cerstatsRegIDs),
			(cerfailureCount),
			(cerfailurePercentage),
			(cerstripChartData),
			(cerstripChartDataX),
			(isStatChartDataAvailable),
			(isMeasurementDataAvailable),
			(isThreadDetectionAvailable)
		);
	}


	template<class Archive>
	void load(Archive & archive)
	{
		archive(
			(imageNumber),
			(noOfRows),
			(noOfCols),
			(taskLabelIDs),
			(stripChartLabel),
			(stripCharttaskID),
			(stripLabelCoordX),
			(stripLabelCoordY),
			(stripPercentCoordX),
			(taskwiseResultCount),
			(symbolheight),
			(symbolwidth),
			(docCount),
			(stripYValues),
			(modelReceived),
			(resultReceived),
			(resultPercentage),
			(balineDBData),
			(balineSoBData),
			(baTaskID),
			(baGroupID),
			(measurementList),
			(measlineVData),
			(measlineHData),
			(imagecountData),
			(heatMapY),
			(heatMapX),
			(hourlyDataX),
			(hourlyFitDataY),
			(hourlyUnfitDataY),
			(hourlyFitPercentDataY),
			(hourlyUnfitPercentDataY),
			(cerstatsCount),
			(cerstatsPercentage),
			(cerstatsRegionNames),
			(cerstatsRegIDs),
			(cerfailureCount),
			(cerfailurePercentage),
			(cerstripChartData),
			(cerstripChartDataX),
			(isStatChartDataAvailable),
			(isMeasurementDataAvailable),
			(isThreadDetectionAvailable)
		);


	

	}

};

