#include "stdafx.h"
#include "ChartDataManager.h"
#include "InspectionParametersConfigReader.h"
#include "ApplicationSettingsReader.h"
ChartDataManager::ChartDataManager()
{
	docCount = 0;
	symbolheight.resize(docSize, stripheight);
	symbolwidth.resize(docSize, stripwidth);
	resultReceived = false;
	resultPercentage[0] = Chart::NoValue;
	resultPercentage[1] = Chart::NoValue;
	iota(begin(imagecountData), end(imagecountData), 1);
	modelReceived = false;
	noOfCols = 5;
	noOfRows = 10;
	initializeHeatMap();
	isResume = false;
	measData = NULL;
	baData = NULL;
	measResult = NULL;
	layerResult = NULL;
	baResult = NULL;
	imageNumber = 0;
	goldenName = " ";
	isStatChartDataAvailable = isMeasurementDataAvailable = isThreadDetectionAvailable = false;
	initializeHourlyChartData();
	initializeLineChartData();
	shiftStartingHour=0;
	totalShiftHours=9;
	perHourTarget=10000;
	
}


ChartDataManager::~ChartDataManager()
{
}

void ChartDataManager::initializeStripChartData()
{
	
	for (int i = 0; i<typeOfResults; i++)
	{
		for (auto &e : taskLabelIDs)
		{
			if (stripChartData[i].count(e.first) == 0)
			{
				fill(begin(stripChartData[i][e.first]), end(stripChartData[i][e.first]), -100);
				fill(begin(stripChartDataX[i][e.first]), end(stripChartDataX[i][e.first]), Chart::NoValue);
			}
		}

	}
}


void ChartDataManager::initializeLineChartData()
{
	fill(begin(balineDBData), end(balineDBData), Chart::NoValue);
	fill(begin(balineSoBData), end(balineSoBData), Chart::NoValue);
	fill(begin(measlineHData), end(measlineHData), Chart::NoValue);
	fill(begin(measlineVData), end(measlineVData), Chart::NoValue);

}
//
// A utility to shift a new data value into a data array
//
static void shiftData(double *data, int len, double newValue)
{
	memmove(data, data + 1, sizeof(*data) * (len - 1));
	data[len - 1] = newValue;
}


void ChartDataManager::initializeTaskResultsCount()
{

}

void ChartDataManager::initializeHeatMap()
{
	vector<double> j(noOfCols), k(noOfCols), l(noOfCols + 1);
	iota(begin(k), end(k), 0.5);
	heatMapX.clear();
	heatMapY.clear();
	//Initialize the X & Y Coordinates for the heatmap
	for (int i = 0; i < noOfRows; i++)
	{
		fill(begin(j), end(j), i + 0.5);
		copy(begin(j), end(j), back_inserter(heatMapY));
		copy(begin(k), end(k), back_inserter(heatMapX));

	}
	
	 


}


void ChartDataManager::setHeatMapModelData()
{ 
	int noofUps = noOfCols*noOfRows;
	/*shiftMaxDominantDefectValue.resize(noofUps);
	shiftMaxSoBValue.resize(noofUps);
	bufferMaxDominantDefectValue.resize(noofUps);
	buffertMaxSoBValue.resize(noofUps);
	currentDominantDefectValue.resize(noofUps);
	currentSoBValue.resize(noofUps);*/
	for (auto &e : thisCameraModelData.inspectionTasks)
	{
		if (e.second->typeOfInspectionTask == inspection_type_LayerInspection || e.second->typeOfInspectionTask == inspection_type_BlobAnalyser || e.second->typeOfInspectionTask == inspection_type_SpecialLayerInspection)
		{
			if (failureCount.count(e.first) == 0)
			{
				failureCount[e.first] = HTuple::TupleGenConst(noofUps, 0);
				failurePercentage[e.first] = HTuple::TupleGenConst(noofUps, 0);
			}
		}
	}
}

void ChartDataManager::CerealizeHalconData()
{
	cerstatsCount.clear();
	cerstatsPercentage.clear();
	cerstatsRegionNames.clear();
	cerstatsRegIDs.clear();
	cerfailureCount.clear();
	cerfailurePercentage.clear();
	cerstripChartData.clear();
	cerstripChartDataX.clear();
	for (auto &e : statsCount)
	{
		double *temp1 = statsCount[e.first].ToDArr();
		copy(temp1, temp1 + statsCount[e.first].Length(), back_inserter(cerstatsCount[e.first]));
		HTuple::DeleteArr(temp1);
		
		double *temp2 = statsPercentage[e.first].ToDArr();
		copy(temp2, temp2 + statsPercentage[e.first].Length(), back_inserter(cerstatsPercentage[e.first]));
		HTuple::DeleteArr(temp2);
		
		HString *HtempLabel = statsRegionNames[e.first].ToSArr();
		for (int i = 0; i < statsRegionNames[e.first].Length(); i++)
		{
			cerstatsRegionNames[e.first].push_back(string(HtempLabel[i].Text()));
		}
		HTuple::DeleteArr(HtempLabel);
		
		double *temp3 = statsRegIDs[e.first].ToDArr();
		copy(temp3, temp3 + statsRegIDs[e.first].Length(), back_inserter(cerstatsRegIDs[e.first]));
		HTuple::DeleteArr(temp3);
		
	}

	for (auto &e : failureCount)
	{
		double *temp1 = failureCount[e.first].ToDArr();
		copy(temp1, temp1 + failureCount[e.first].Length(), back_inserter(cerfailureCount[e.first]));
		HTuple::DeleteArr(temp1);

		double *temp2 = failurePercentage[e.first].ToDArr();
		copy(temp2, temp2 + failurePercentage[e.first].Length(), back_inserter(cerfailurePercentage[e.first]));
		HTuple::DeleteArr(temp2);
	}

	for (auto &e: taskLabelIDs)
	{
		vector<double> temp,tempX;
		for (int r = 0; r < typeOfResults; r++)
		{	
			copy(begin(stripChartData[r][e.first]), end(stripChartData[r][e.first]),back_inserter(temp));
			copy(begin(stripChartDataX[r][e.first]), end(stripChartDataX[r][e.first]), back_inserter(tempX));
		}
		cerstripChartData[e.first] = temp;
		cerstripChartDataX[e.first] = tempX;
	}


}

void ChartDataManager::DeCerealizeHalconData()
{
	for (auto &e : cerstatsCount)
	{
		int i = 0;
		for (auto &f : cerstatsPercentage[e.first])
		{
			statsPercentage[e.first][i] = HTuple(f);
			statsCount[e.first][i] = HTuple(cerstatsCount[e.first][i]);
			statsRegIDs[e.first][i] = HTuple(cerstatsRegIDs[e.first][i]);
			statsRegionNames[e.first][i] = HString(cerstatsRegionNames[e.first][i].c_str());
			i++;
		}
	}

	for (auto &e : cerfailureCount)
	{
		int i = 0;
		for (auto &f : cerfailurePercentage[e.first])
		{
			failurePercentage[e.first]=failurePercentage[e.first].TupleConcat(HTuple(f));
			failureCount[e.first] =failureCount[e.first].TupleConcat(cerfailureCount[e.first][i]);
			i++;
		}
		HTuple fp = failurePercentage[e.first];
		HTuple fc = failureCount[e.first];
	}

	for (auto &e : cerstripChartData)
	{
		vector<double> temp, tempX;
		temp = cerstripChartData[e.first];
		tempX = cerstripChartDataX[e.first];
		for (int i = 1; i <= typeOfResults; i++)
		{
			double dTemp[docSize], dTempX[docSize];
			int it = (i - 1)*docSize;
			copy(&temp[it], &temp[it]+docSize, dTemp);
			copy(&tempX[it], &tempX[it] + docSize, dTempX);
			double *datPtr = stripChartData[i - 1][e.first];
			double *datXPtr = stripChartDataX[i - 1][e.first];
			memcpy(datPtr, dTemp, docSize * sizeof(double));
			memcpy(datXPtr, dTempX, docSize * sizeof(double));
			/*copy(temp.begin() + (i*docSize), temp.begin() + (i*docSize - 1), stripChartData[i - 1][e.first]);
			copy(tempX.begin() + (i*docSize), tempX.begin() + (i*docSize - 1), stripChartDataX[i - 1][e.first]);*/
		}

	}
}


void ChartDataManager::reportSheetPieChart(PieChart *c)
{
	// The data for the pie chart
	double(&data)[2] = resultPercentage;

	c->setLabelPos(-20);
	//c->setRoundedFrame(m_extBgColor);
	// The labels for the pie chart
	const char *labels[] = { "Fit", "Unfit" };
	//c->setSectorStyle(Chart::RoundedEdgeShading, 0xffffff, 1);
	TextBox *title = c->addTitle("SHEET-WISE OVERALL SPOILAGE", boldFont.c_str(), 8, 0x1f4d78, 0xffffff);
	c->addLine(10, title->getHeight()+3, c->getWidth() - 11, title->getHeight() + 3, 0x5b9bd5, 2);
	c->setPieSize(60,85, 50);
	c->setLabelStyle("arial.ttf", 8, 0x000000);
	c->setLabelFormat("{value|P0}%");
	// Set the pie data and the pie labels
	c->setData(DoubleArray(data, (int)(sizeof(data) / sizeof(data[0]))), StringArray(labels, (int)(
		sizeof(labels) / sizeof(labels[0]))));
	Sector *fit = c->getSector(1);
	Sector *unfit = c->getSector(0);
	fit->setColor(0xffffff, 0);
	unfit->setColor(0xffffff,0xff0000, 0xff0000);
	c->setExplode(2, 3);
	
}
void ChartDataManager::reportUpPieChart(PieChart * c)
{
	double data[2];
	data[1] = failureCount[baTaskID].TupleSum().TupleMult(100.0 / (imageNumber*noOfCols*noOfRows)).D();
	data[0] = 100 - data[1];

	c->setLabelPos(-20);
	//c->setRoundedFrame(m_extBgColor);
	// The labels for the pie chart
	const char *labels[] = { "Fit", "Unfit" };
	TextBox *title = c->addTitle("UP-WISE OVERALL SPOILAGE", boldFont.c_str(), 8, 0x1f4d78, 0xffffff);
	c->addLine(10, title->getHeight()+3, c->getWidth() - 11, title->getHeight() + 3, 0x5b9bd5, 2);
	c->setPieSize(60, 85, 50);
	c->setLabelStyle("arial.ttf", 8, 0x000000);
	c->setLabelFormat("{value|P0}%");


	// Set the pie data and the pie labels
	c->setData(DoubleArray(data, (int)(sizeof(data) / sizeof(data[0]))), StringArray(labels, (int)(
		sizeof(labels) / sizeof(labels[0]))));
	Sector *fit = c->getSector(0);
	Sector *unfit = c->getSector(1);
	fit->setColor(0xffffff,0);
	//unfit->setColor(0xff0000,0);
	unfit->setColor(0xffffff, 0xff0000, 0xff0000);
	c->setExplode(2, 3);

}
void ChartDataManager::reportFCHourlyChart(XYChart *c, Shift &shift)
{
	ShiftTypes shiftList = ApplicationSettingsReader::GetInstance()->shifConfig[shift.shiftIndex];
	TextBox *title = c->addTitle("SHEET-WISE HOURLY SPOILAGE" , boldFont.c_str(), 8, 0x1f4d78, 0xffffff);
	c->addLine(10, title->getHeight()+3, c->getWidth() - 11, title->getHeight() + 3, 0x5b9bd5, 2);
	
	c->xAxis()->setLabelFormat("{={value}%24}-{={value}%24+1}");
	c->yAxis()->setTitle("No. of sheets", "arialbd.ttf", 8);
	c->xAxis()->setTitle("Time (Hours)", "arialbd.ttf", 8);
	c->xAxis()->setLabelStyle("arial.ttf", 5, 0);
	c->yAxis()->setLabelStyle("arial.ttf", 5, 0);

	c->yAxis()->setLinearScale(0, shiftList.perHourTarget+(shiftList.perHourTarget * 0.2), 0, 0);
	c->xAxis()->setLinearScale((int)shiftList.shiftStartHour,
		(int)shiftList.shiftStartHour + shiftList.totalShiftHours, 1);

	Mark *yMark = c->yAxis()->addMark(shiftList.perHourTarget, c->dashLineColor(0, Chart::DotLine), "Hourly Target", "arialbd.ttf", 8);
	yMark->setAlignment(Chart::TopRight);
	BarLayer *layer = c->addBarLayer(Chart::Stack);
	layer->addDataSet(DoubleArray(&hourlyFitDataY[0], 24), 0xffffff,
		"Pass");
	layer->setBorderColor(0);
	layer->addDataSet(DoubleArray(&hourlyUnfitDataY[0], 24), 0xff0000,
		"Fail");
	layer->setAggregateLabelFormat("{value|P0}");
	// Enable labelling for the entire bar and use 12pt Arial font
	layer->setAggregateLabelStyle("arial.ttf", 5);
	layer->setDataLabelStyle("arial.ttf", 5, labelColor, 0)->setAlignment(Chart::Center);
}
void ChartDataManager::reportStatRegSpoilageChart(XYChart *c)
{
	TextBox *title = c->addTitle("STATISTICS REGION SPOILAGE PERCENTAGE", boldFont.c_str(), 8, 0x1f4d78, 0xffffff);

	c->addLine(10, title->getHeight() + 3, c->getWidth() - 11, title->getHeight() + 3, 0x5b9bd5, 2);
	BarLayer *layer;
	vector<double> data;
	vector<const char*> labels;
	bool isDataPresent;
	for (auto &e : statsRegionNames)
	{
		isDataPresent = statsRegionNames[e.first].Length() > 0 ? true : false;
		if (isDataPresent)
		{
			HTuple tempd = statsPercentage[e.first]; // .DArr();
			HTuple tempLabeld = statsRegionNames[e.first]; // .SArr();

			double *temp = statsPercentage[e.first].ToDArr();
			char** tempLabel = statsRegionNames[e.first].SArr();
			int length = statsPercentage[e.first].Length();
			//layer->addDataSet(DoubleArray(&temp[0], length),-1,e.second->taskName.c_str());
			copy(temp, temp + length, back_inserter(data));
			copy(tempLabel, tempLabel + length, back_inserter(labels));
		}

	}
	//isDataPresent = statsRegionNames[e.first].Length() > 0 ? true : false;
	if (isDataPresent)
	{
		layer = c->addBarLayer(DoubleArray(&data[0], labels.size()));
		layer->setAggregateLabelFormat("{value|0} %");
		layer->setAggregateLabelStyle("arial.ttf", 8, blueTextColor);
		c->xAxis()->setLabels(StringArray(&labels[0], labels.size()));
		c->xAxis()->setLabelStyle("arialbd.ttf", 8.0, 0);
		c->yAxis()->setLinearScale(0, 100, 0, 0);
		layer->setBarWidth(5);
		layer->setBorderColor(Chart::Transparent);
	}
	c->dashLineColor(Chart::Transparent);
	// Set the x axis to Transparent, with labels in dark red (0x663300)
	c->xAxis()->setColors(Chart::Transparent, 0, 0);
	c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);
	// Set the y axis and labels to Transparent
	c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);
	c->swapXY();

}

void ChartDataManager::reportTaskwiseSpoilageChart(XYChart *c)
{
	TextBox *title = c->addTitle("TASK-WISE SPOILAGE PERCENTAGE", boldFont.c_str(), 8, 0x1f4d78, 0xffffff);

	c->addLine(10, title->getHeight() + 3, c->getWidth() - 11, title->getHeight() + 3, 0x5b9bd5, 2);
	BarLayer *layer;
	vector<double> data;
	vector<const char*> labels;
	bool isDataPresent;
	int i = taskLabelIDs.size()-1;
	for (auto &e : taskLabelIDs)
	{
		isDataPresent = taskLabelIDs.size() > 0 ? true : false;
		if (isDataPresent)
		{
			double unfit = taskwiseResultCount[0][i] + taskwiseResultCount[1][i];
			double unfitP = unfit * 100 / (unfit + taskwiseResultCount[2][i]);
			data.push_back(unfitP);
			labels.push_back(e.second.c_str());
			
		}
		i--;
	}

	if (isDataPresent)
	{
		layer = c->addBarLayer(DoubleArray(&data[0], labels.size()));
		layer->setAggregateLabelFormat("{value|0} %");
		layer->setAggregateLabelStyle("arial.ttf", 8, blueTextColor);
		c->xAxis()->setLabels(StringArray(&labels[0], labels.size()));
		c->xAxis()->setLabelStyle("arialbd.ttf", 8.0, 0);
		c->yAxis()->setLinearScale(0, 100, 0, 0);
		layer->setBarWidth(5);
		layer->setBorderColor(Chart::Transparent);
	}
	c->dashLineColor(Chart::Transparent);
	// Set the x axis to Transparent, with labels in dark red (0x663300)
	c->xAxis()->setColors(Chart::Transparent, 0, 0);
	c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);
	// Set the y axis and labels to Transparent
	c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);
	c->swapXY();

}

void ChartDataManager::reportUpSpoilageChart(XYChart *c)
{
	c->yAxis()->setTitle("Rows", "arialbd.ttf", 8);
	c->yAxis()->setTitlePos(4, -2);
	c->xAxis()->setTitle("Panels", "arialbd.ttf", 8);
	c->setColors(Chart::transparentPalette);
	c->xAxis()->setLabelStyle("arialbd.ttf", 8, 0);
	c->xAxis()->setLabelAlignment(4);
	c->yAxis()->setLabelAlignment(4);
	c->yAxis()->setLabelStyle("arialbd.ttf", 8, 0);
	c->xAxis()->setTickColor(Chart::Transparent, Chart::Transparent);
	c->yAxis()->setTickColor(Chart::Transparent, Chart::Transparent);
	/*c->xAxis()->setWidth(3);
	c->yAxis()->setWidth(3);*/
	c->yAxis()->setLabelOffset(20);
	//c->xAxis()->setLabelOffset(-0.5);
	c->yAxis()->setTickWidth(1, 5);
	c->xAxis()->setTickWidth(1, 5);
	c->xAxis()->setLinearScale(0, noOfCols, 0, 0);
	c->yAxis()->setLinearScale(0, noOfRows, 0, 0);
	c->yAxis()->setReverse();
	TextBox *title = c->addTitle("UP-WISE SPOILAGE CHART", boldFont.c_str(), 8, 0x1f4d78, 0xffffff);

	c->addLine(10, title->getHeight()+3, c->getWidth() - 11, title->getHeight()+3, 0x5b9bd5,2);


	double colorScale[] = { 0x0000cc, 0x0066ff, 0x66ccff, 0x66ffff,0x88ff88, 0x00ff00,
		0xffff00,  0xff6600,  0xcc0000,  0x000000 };
	c->yAxis()->setLabelOffset(-0.5);
	c->xAxis()->setLabelOffset(-0.5);
	double height = 1;
	double width = 1;

	for (int i = 0; i <heatMapY.size(); ++i)
	{
		int colIndex = 0;

			HTuple fp = failurePercentage[baTaskID];
			HTuple percentage = failurePercentage[baTaskID][i];
			colIndex = (int)(percentage.D() / 10);
			
		ScatterLayer *scatter = c->addScatterLayer(DoubleArray(&heatMapX[i], 1),
			DoubleArray(&heatMapY[i], 1),
			"", Chart::SquareSymbol, 2,
			Chart::Transparent,
			0x000000);
		char percent[40];
		sprintf(percent, "%0.0f%%", percentage.D());
		ostringstream xlabel;
		xlabel << "<*font=arialbd.ttf,size=7,color=FF0000*>" << percent
			<< "<*/font*><*br*>"<< "<*font=arial.ttf,size=5,color=000000*>" <<failureCount[baTaskID][i].D();
		string temp = xlabel.str();
		TextBox *t= scatter->addCustomDataLabel(0,0, temp.c_str(),"arial.ttf");
		t->setAlignment(5);

		scatter->setSymbolScale(DoubleArray(&width, 1), Chart::XAxisScale, DoubleArray(&height, 1),
			Chart::YAxisScale);
		

		//c->getPlotArea()->setGridWidth(5, 5, 5, 5);
		//c->getPlotArea()->moveGridBefore(scatter);
	}
	//ContourLayer *layer = c->addContourLayer(DoubleArray(&width, 1), DoubleArray(&width, 1), DoubleArray(colorScale, (int)(
	//	sizeof(colorScale) / sizeof(colorScale[0]))));
	//double colorScale1[] = { 0.0, 0x0000cc,10.0, 0x0066ff,20.0, 0x66ccff,30.0, 0x66ffff,40.0,0x88ff88,50.0, 0x00ff00,60.0,
	//	0xffff00,70.0,  0xff6600,80.0,  0xcc0000,90.0,  0x000000,100.0 };
	//ColorAxis *cAxis = layer->setColorAxis(310, 50, Chart::TopCenter, 180, Chart::Right);

	//// Add a title to the color axis using 12 points Arial Bold Italic font
	//cAxis->setTitle("Failure Percentage Scale", "arialbi.ttf", 10);

	//// Set color axis labels to use Arial Bold font
	//cAxis->setLabelStyle("arialbd.ttf");

	//// Set the color axis range as 0 to 20, with a step every 2 units
	//cAxis->setLinearScale(0, 100, 10);
	//cAxis->setColorScale(DoubleArray(colorScale1, (int)(
	//	sizeof(colorScale1) / sizeof(colorScale1[0]))));


}

string ChartDataManager::GenerateReport(Shift &shift)
{

	MultiChart *pdfReport = new MultiChart(830, 1170, 0xfFfFfF, 0x000000, 1);
	int itableWidth;
	int itableHeight;
	int tableWidth;
	int tableHeight;
	char buffer[40];
	
	int topBorder = 60;
	int leftBorder = 70;
	int rightBorder = 760;
	int bottomBorder = 1100;
	int centerX = (rightBorder - leftBorder) / 2;
	char sTime[100];
#pragma region table

	pdfReport->addText(leftBorder, topBorder - 10, "<*img=.\\Configuration Files\\Icons\\Komori-Logo.jpg,width=130,height=25*>");
	pdfReport->addText(625, topBorder - 20, "<*img=.\\Configuration Files\\Icons\\LucidLogo.png,width=125,height=30*>");
	DrawArea *cdraw = pdfReport->getDrawArea();
	cdraw->rect(leftBorder, topBorder + 25, rightBorder+5, topBorder + 52, 0x5B9BD5, 0x5B9BD5);
	pdfReport->addText(leftBorder + centerX, topBorder + 38, "OIS PRODUCTION REPORT", boldFont.c_str(), 12, 0xFFFFFF, 5);//Title
	pdfReport->addText(leftBorder, bottomBorder-5, "* NOTE: Indicated values are for reference purpose only."
		"User should refer Audit Trail Log (for respective Golden) for more detail.", normalFont.c_str(), 5, 0, 7);//Title
	string footer1 = "GOLDEN NAME: " + shift.goldenName;
	pdfReport->addText(leftBorder, bottomBorder + 15, footer1.c_str(), normalFont.c_str(), 8, 0, 7);//Title
	strftime(sTime, 100, "%d-%m-%Y", std::localtime(&shift.shiftStartedTime[0]));
	string footer2 = "SHIFT: "+ string(sTime) + "/" + shift.shiftName;
	pdfReport->addText(rightBorder, bottomBorder + 15, footer2.c_str(), normalFont.c_str(), 8, 0, 9);//Title
	time_t currTime = 0;
	time(&currTime);
	strftime(sTime, 100, "%d/%m/%Y %T", std::localtime(&currTime));
	pdfReport->addText(leftBorder + centerX, bottomBorder + 15, sTime, normalFont.c_str(), 8, 0, 8);//Title																											   //
	CDMLTable * machineInfo = pdfReport->addTable(leftBorder, topBorder + 60, 7, 4, 7);

	for (int i = 0; i< machineInfo->getColCount(); i++)
	{
		if (((i + 1) % 2) == 0)
		{
			TextBox *colStyle = machineInfo->getColStyle(i);
			setNormalFontStyle(colStyle, 5, 75, 8, 8, 7, Chart::Transparent);
		}
		else
		{
			TextBox *cellStyle = machineInfo->getColStyle(i);
			setBoldFontStyle(cellStyle, 5, 60, 8, 8, 7, Chart::Transparent);
		}
	}
	int r = 0;
	TextBox *rowHStyle1 = machineInfo->getRowStyle(r);
	setHeadingStyle(rowHStyle1, 5, 60, 3, 3, 8, Chart::Transparent);

	machineInfo->setText(0, r, "PRODUCTION MACHINE");
	
	r = 1;
	machineInfo->setText(0, r, "MACHINE REFERENCE");
	machineInfo->setText(1, r, ApplicationSettingsReader::GetInstance()->MachineID.c_str());
	machineInfo->setText(2, r, "PRINTER NAME");
	machineInfo->setText(3, r, "BRBNMPL, Salboni");

	r = 2;
	TextBox *rowHStyle2 = machineInfo->getRowStyle(r);
	setHeadingStyle(rowHStyle2, 5, 60, 3, 3, 8, Chart::Transparent);
	machineInfo->setText(0, r, "JOB DETAIL");

	r = 3;
	machineInfo->setText(0, r, "GOLDEN NAME");
	machineInfo->setText(1, r, shift.goldenName.c_str());
	machineInfo->setText(2, r, "USER ID");
	machineInfo->setText(3, r, shift.userID.c_str());

	r = 4;
	machineInfo->setText(0, r, "DATE OF PRODUCTION");
	strftime(sTime, 100, "%d %B,%Y", std::localtime(&shift.shiftStartedTime[0]));
	machineInfo->setText(1, r, sTime);
	machineInfo->setText(2, r, "SHIFT ID");
	machineInfo->setText(3, r, shift.shiftName.c_str());

	r = 5;
	machineInfo->setText(0, r, "SHIFT STARTED TIME");
	strftime(sTime, 100, "%I:%M %p", std::localtime(&shift.shiftStartedTime[0]));
	machineInfo->setText(1, r, sTime);
	machineInfo->setText(2, r, "TOTAL SHIFT TIME");
	ULONG diff = shift.elapsedTime;
	sprintf(sTime,"%02d:%02d:%02d", (int)(diff / 3600), (int)(diff / 60) % 60, (int)diff % 60);
	machineInfo->setText(3, r, sTime);


	r = 6;
	TextBox *rowHStyle3 = machineInfo->getRowStyle(r);
	setHeadingStyle(rowHStyle3, 5, 60, 3, 3, 8, Chart::Transparent);
	machineInfo->setText(0, r, "INSPECTION PROFILE");

	machineInfo->layout();
	tableWidth = machineInfo->getWidth();
	tableHeight = machineInfo->getHeight();
	
	



	CDMLTable * inspProfile = pdfReport->addTable(leftBorder, topBorder + 65 + tableHeight + 5, 7, 5, 3);

	for (int i = 1; i< inspProfile->getColCount(); i++)
	{
		if (((i) % 2) == 0)
		{
			TextBox *colStyle = inspProfile->getColStyle(i);
			setNormalFontStyle(colStyle, 5, 80, 4, 4, 7, Chart::Transparent);
		}
		else
		{
			TextBox *cellStyle = inspProfile->getColStyle(i);
			setBoldFontStyle(cellStyle, 5, 30, 4, 4, 7, Chart::Transparent);
		}
	}

	TextBox *colStyle0 = inspProfile->getColStyle(0);
	setNormalFontStyle(colStyle0, 5, 5, 8, 10, 7, Chart::Transparent);

	r = 0;
	inspProfile->setText(0, r, "<*img=.\\Configuration Files\\Icons\\layer.png,width=30,height=30*>");
	inspProfile->setText(1, r, "GLOBAL TOLERANCE\n\nMAJOR BLOB THRESHOLD");

	blopAnalyzerParameterLookup = InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[baGroupID];
	string tol = to_string(blopAnalyzerParameterLookup.globalTolerance)+"\n\n"+ to_string(blopAnalyzerParameterLookup.majorBlobThreshold);
	inspProfile->setText(2, r, tol.c_str());
	string thresh = to_string(blopAnalyzerParameterLookup.dominantBlobThreshold) + "\n\n" + to_string(blopAnalyzerParameterLookup.groupOfBlobThreshold);
	inspProfile->setText(3, r, "DOMINANT BLOB THRESHOLD\n\nGROUP OF BLOB THRESHOLD");
	inspProfile->setText(4, r, thresh.c_str());

	r = 1;
	inspProfile->setText(0, r, "<*img=.\\Configuration Files\\Icons\\thread.png,width=30,height=30*>");
	inspProfile->setText(1, r, "THREAD DETECTION");
	inspProfile->setText(2, r, "DISABLED");
	r = 2;
	inspProfile->setText(0, r, "<*img=.\\Configuration Files\\Icons\\measurement.png,width=30,height=30*>");
	inspProfile->setText(1, r, "HORIZONTAL OFFSET\n\nVERTICAL OFFSET");
	char measString[70];
	sprintf(measString, "%0.1f<=%0.1f<=%0.1f mm\n\n%0.1f<=%0.1f<=%0.1f mm", measurementList[0].horizontal.lowerTolerance
		, measurementList[0].horizontal.nominalDistance
		, measurementList[0].horizontal.upperTolerance
		, measurementList[0].vertical.lowerTolerance
		, measurementList[0].vertical.nominalDistance
		, measurementList[0].vertical.upperTolerance);
	inspProfile->setText(2, r, measString);


	inspProfile->layout();
	itableWidth = inspProfile->getWidth();
	itableHeight = inspProfile->getHeight();
	
	CDMLTable * GraphsTitle = pdfReport->addTable(leftBorder, topBorder + 65 + itableHeight + tableHeight + 5, 7, 1, 1);
	r = 0;
	TextBox *rowHStyle5 = GraphsTitle->getRowStyle(r);
	setHeadingStyle(rowHStyle5, 5, 490, 3, 3, 8, Chart::Transparent);
	GraphsTitle->setText(0, r, "PRODUCTION SPOILAGE STATISTICS");
#pragma endregion	

	PieChart *sheetWisePie = new PieChart(340, 150, 0xFFFFFF, 0xFFFFFF, 0);
	reportSheetPieChart(sheetWisePie);
	CDMLTable *sheetWiseTable = sheetWisePie->addTable(140, 50, 7, 2, 4);
	TextBox *cellCStyle1 = sheetWiseTable->getColStyle(0);
	setBoldFontStyle(cellCStyle1, 5, 30, 2, 2, 7, 0x000000);
	cellCStyle1->setAlignment(5);
	TextBox *cellHStyle2 = sheetWiseTable->getCell(1, 0);
	setBoldFontStyle(cellHStyle2, 5, 30, 2, 2, 7, 0x000000);
	cellHStyle2->setAlignment(5);
	
	sheetWiseTable->setText(0, 1, "TOTAL");
	sheetWiseTable->setText(0, 2, "FIT");
	sheetWiseTable->setText(0, 3, "UNFIT");

	sheetWiseTable->setText(1, 0, "SHEET COUNT");
	
	sprintf(buffer, "%d", imageNumber);
	sheetWiseTable->setText(1, 1, buffer);
	sprintf(buffer, "%d", taskwiseResultCount[2].back());
	sheetWiseTable->setText(1, 2, buffer);
	sprintf(buffer, "%d", imageNumber-taskwiseResultCount[2].back());
	sheetWiseTable->setText(1, 3, buffer);
	 
	
	PieChart *upwiseWisePie = new PieChart(340, 150, 0xFFFFFF, 0xFFFFFF, 0);
	reportUpPieChart(upwiseWisePie);
	CDMLTable *upWiseTable = upwiseWisePie->addTable(140, 50, 7, 2, 4);
	int currentLine = topBorder + 110 + tableHeight + itableHeight;
	TextBox *cellCStyle3 = upWiseTable->getColStyle(0);
	setBoldFontStyle(cellCStyle3, 5, 30, 2, 2, 7, 0x000000);
	cellCStyle3->setAlignment(5);
	TextBox *cellHStyle4 = upWiseTable->getCell(1, 0);
	setBoldFontStyle(cellHStyle4, 5, 30, 2, 2, 7, 0x000000);
	cellHStyle4->setAlignment(5);
	upWiseTable->setText(0, 1, "TOTAL");
	upWiseTable->setText(0, 2, "FIT");
	upWiseTable->setText(0, 3, "UNFIT");

	upWiseTable->setText(1, 0, "SHEET COUNT");
	int totalUps = imageNumber*noOfCols*noOfRows;
	sprintf(buffer, "%d", totalUps);
	upWiseTable->setText(1, 1, buffer);
	HTuple te = failureCount[baTaskID].TupleSum();
	int upFailCount = (int)failureCount[baTaskID].TupleSum().D();
	sprintf(buffer, "%d", totalUps- upFailCount);
	upWiseTable->setText(1, 2, buffer);
	sprintf(buffer, "%d", upFailCount);
	upWiseTable->setText(1, 3, buffer);



	XYChart *hourlyFCountChart = new XYChart(340, 280, 0xFFFFFF, 0xFFFFFF, 0);
	hourlyFCountChart->setPlotArea(40, 50, 260, 200, -1, -1, Chart::Transparent);
	reportFCHourlyChart(hourlyFCountChart,shift);

	/*XYChart *heatmap = new XYChart(340,280, 0xFFFFFF, 0, 0);
	heatmap->setPlotArea(20, 50, 250, 180, -1, -1, Chart::Transparent);*/
	XYChart *heatmap = new XYChart(340, 280, 0xFFFFFF, 0xFFFFFF, 0);
	heatmap->setPlotArea(25, 30, baTaskID, 220, -1, -1, Chart::Transparent);
	reportUpSpoilageChart(heatmap);
	//sheetWisePie->layout();
	pdfReport->addChart(leftBorder, currentLine, sheetWisePie);
	pdfReport->addChart(leftBorder + 350, currentLine, upwiseWisePie);

	currentLine = currentLine + 160;
	pdfReport->addChart(leftBorder, currentLine, hourlyFCountChart);
	pdfReport->addChart(leftBorder+350, currentLine, heatmap);
	//pdfReport->addChart(100, 600, sheetWisePie);//pdfReport->addText(leftBorder +5, topBorder + 67, "PRODUCTON MACHINE", boldFont.c_str(), 8, 0x000000, 4);  //Sub-Title
	
	currentLine = currentLine + 300;
	XYChart *statsChart = new XYChart(340, 180, 0xFFFFFF, 0xFFFFFF, 0);
	statsChart->setPlotArea(120, 30, 150, 120, Chart::Transparent, Chart::Transparent, Chart::Transparent, Chart::Transparent, Chart::Transparent);
	reportStatRegSpoilageChart(statsChart);
	
	XYChart *tasksChart = new XYChart(340, 180, 0xFFFFFF, 0xFFFFFF, 0);
	tasksChart->setPlotArea(120, 30, 150, 120, Chart::Transparent, Chart::Transparent, Chart::Transparent, Chart::Transparent, Chart::Transparent);
	reportTaskwiseSpoilageChart(tasksChart);

	pdfReport->addChart(leftBorder, currentLine, tasksChart);
	pdfReport->addChart(leftBorder+ 350, currentLine, statsChart);


	DrawArea *d = pdfReport->initDynamicLayer();
	int tableTop = topBorder + 60 + (24 * 7);
	int temp = tableTop;
	for (int i = 0; i < inspProfile->getRowCount(); i++)
	{
		int rowHeight = inspProfile->getRowHeight(i);
		int colWidth = inspProfile->getColWidth(0);
		d->rect(leftBorder, temp, leftBorder + itableWidth, temp + rowHeight, 0x000000, Chart::Transparent);
		d->rect(leftBorder, temp, leftBorder + colWidth, temp + rowHeight, 0x000000, Chart::Transparent);
		temp += rowHeight;
	}
	d->destroy();
	string writeLoc = ApplicationSettingsReader::GetInstance()->ShiftDataLocation + "\\ShiftReport_" + shift.shiftDate +"_"+shift.shiftName.back() + ".pdf";
	string tempLoc = ApplicationSettingsReader::GetInstance()->ShiftDataLocation + "\\temp.png";
	pdfReport->makeChart(writeLoc.c_str());
	pdfReport->makeChart(tempLoc.c_str());
	delete statsChart;
	delete tasksChart;
	delete sheetWisePie;
	delete upwiseWisePie;
	delete heatmap;
	delete hourlyFCountChart;
	//pdfReport->destroy();
	int cCount = pdfReport->getChartCount();

	return writeLoc;
}



void ChartDataManager::setHeadingStyle(TextBox *cellStyle, int left, int right, int top, int bottom, int fontSize, int bkcolor)
{
	cellStyle->setBackground(0xdeeaf6, 0xdeeaf6);
	cellStyle->setFontSize(fontSize);
	cellStyle->setFontStyle(boldFont.c_str());
	cellStyle->setMargin(left, right, top, bottom);
	cellStyle->setMaxWidth(1500);
	cellStyle->setAlignment(4);
}


void ChartDataManager::setBoldFontStyle(TextBox *cellStyle, int left, int right, int top, int bottom, int fontSize, int edgeColor)
{
	cellStyle->setFontSize(fontSize);
	cellStyle->setFontStyle(boldFont.c_str());
	cellStyle->setMargin(left, right, top, bottom);
	cellStyle->setMaxWidth(250);
	cellStyle->setBackground(Chart::Transparent, edgeColor);
	cellStyle->setAlignment(4);
}

void ChartDataManager::setNormalFontStyle(TextBox *cellStyle, int left, int right, int top, int bottom, int fontSize, int edgeColor)
{
	cellStyle->setFontSize(fontSize);
	cellStyle->setFontStyle(normalFont.c_str());
	cellStyle->setMargin(left, right, top, bottom);
	cellStyle->setMaxWidth(250);
	cellStyle->setBackground(Chart::Transparent, edgeColor);
	cellStyle->setAlignment(4);
}



void ChartDataManager::initializeHourlyChartData()
{
		hourlyDataX.resize(24);
		hourlyFitDataY.resize(24, Chart::NoValue);
		hourlyUnfitDataY.resize(24, Chart::NoValue);
		hourlyFitPercentDataY.resize(24, Chart::NoValue);
		hourlyUnfitPercentDataY.resize(24, Chart::NoValue);
		iota(hourlyDataX.begin(), hourlyDataX.end(), 0);

}

int ChartDataManager::setTaskwiseResultData()
{
	int i = 1;
	HTuple dominantBlobEnergy = 0;
	HTuple SoBEnergy = 0;
	int camresult = camResultData->result;
	time_t currTime = 0;
	time(&currTime);
	tm *startTimeinfo;
	startTimeinfo = localtime(&currTime);

	for (auto &e : camResultData->taskResults) {
		
		int result = e.second->result;
		if ((result > 2) || (result<0))
			result = 0;
		
			if (docCount <= docSize)
			{
				for (int r = 0; r < typeOfResults; r++)
				{
					if (r == result)
					{
						stripChartData[r][e.first][docCount - 1] = 1;
						stripChartDataX[r][e.first][docCount - 1] = imageNumber;
					}
					else
					{
						stripChartData[r][e.first][docCount - 1] = -200;
						stripChartDataX[r][e.first][docCount - 1] = imageNumber;
					}
					
				}
				if(result>0)
				{
					switch (e.second->typeOfInspection)
					{
					case inspection_type_BlobAnalyser:
						baResult = (BlobAnalyzerResultData *)e.second;
						if (baResult->dominantBlobEnergy.Length())
						{
							dominantBlobEnergy = baResult->dominantBlobEnergy.TupleMax();
							SoBEnergy = baResult->groupOfDefectBlobsUPWiseEnergy.TupleMax();

						}
						balineDBData[docCount - 1] = dominantBlobEnergy.D();
						balineSoBData[docCount - 1] = SoBEnergy.D();
						updateHeatmapData();
						updateStatsData();
						break;
					case  inspection_type_LayerInspection:
					case inspection_type_SpecialLayerInspection:
						layerResult = (LayerResultData *)e.second;
						break;
					case inspection_type_Measurement:
						measResult = (MeasurementResultData*)e.second;
						measlineHData[docCount - 1] = measResult->horizontalDiff.D();
						measlineVData[docCount - 1] = measResult->verticleDiff.D();
						break;
					case inspection_type_ThreadDetection:
						thrResult = (ThreadResultData*)e.second;
						break;
					}

				}
				imagecountData[docCount - 1] = imageNumber;
			}
			else
			{
				for (int r = 0; r < typeOfResults; r++)
				{
					if (r == result)
					{
						shiftData(stripChartData[r][e.first], docSize, 1);
						shiftData(stripChartDataX[r][e.first], docSize, imageNumber);
					}
					else
					{
						shiftData(stripChartData[r][e.first], docSize, -200);
						shiftData(stripChartDataX[r][e.first], docSize, imageNumber);
					}
				}
				if (result > 0)
				{
					switch (e.second->typeOfInspection)
					{
					case inspection_type_BlobAnalyser:
						baResult = (BlobAnalyzerResultData *)e.second;
						if (baResult->dominantBlobEnergy.Length())
						{
							dominantBlobEnergy = baResult->dominantBlobEnergy.TupleMax();
							SoBEnergy = baResult->groupOfDefectBlobsUPWiseEnergy.TupleMax();
							
						}
						shiftData(balineDBData, docSize, dominantBlobEnergy);
						shiftData(balineSoBData, docSize, SoBEnergy);
						updateHeatmapData();
						updateStatsData();
						break;
					case  inspection_type_LayerInspection:
					case inspection_type_SpecialLayerInspection:
						//layerResult = (LayerResultData *)e.second;
						break;
					case inspection_type_Measurement:
						measResult = (MeasurementResultData*)e.second;
						shiftData(measlineHData, docSize, measResult->horizontalDiff.D());
						shiftData(measlineVData, docSize, measResult->verticleDiff.D());
						//delete measResult;
						break;
					}
				}				
			}
		taskwiseResultCount[result][i - 1]++;
		
		i++;

	}
	
	for (int r = 0; r < typeOfResults; r++)
	{
		if (docCount <= docSize)
		{
			if (r == camresult)
				stripChartData[r][thisCameraModelData.taskID][docCount - 1] = 1;
			else
				stripChartData[r][thisCameraModelData.taskID][docCount - 1] = -200;
			
			//shiftData(stripChartDataX[camresult][thisCameraModelData.taskID], docSize, imageNumber);
		}
		else
		{
			if (r == camresult)
				shiftData(stripChartData[r][thisCameraModelData.taskID], docSize, 1);
			else
				shiftData(stripChartData[r][thisCameraModelData.taskID], docSize, -200);
		}

		
	}

	if (docCount > docSize)
		shiftData(imagecountData, docSize, imageNumber);
	taskwiseResultCount[camresult][i - 1]++;

	double unfit = taskwiseResultCount[0][i - 1] + taskwiseResultCount[1][i - 1];
	resultPercentage[0] = unfit * 100 / (unfit + taskwiseResultCount[2][i - 1]);
	resultPercentage[1] = 100 - resultPercentage[0];
	resultReceived = true;

    //Update HourlychartData
	hourlyUnfitDataY[startTimeinfo->tm_hour]= unfit;
	hourlyFitDataY[startTimeinfo->tm_hour] = imageNumber - unfit;
	hourlyUnfitPercentDataY[startTimeinfo->tm_hour] = resultPercentage[0];
	hourlyFitPercentDataY[startTimeinfo->tm_hour] = resultPercentage[1];
	return 1;
}


void ChartDataManager::setTaskwiseModelData()
{
	
	for (auto &e :thisCameraModelData.inspectionTasks) {
		
		taskLabelIDs[e.second->taskID] = e.second->taskName;

		switch (e.second->typeOfInspectionTask)
		{
		case inspection_type_BlobAnalyser:
			baData = (BlobAnalyzerData *)e.second;
			blopAnalyzerParameterLookup = InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[baData->blopParametersGroupID];
			baTaskID = e.first;
			baGroupID = baData->blopParametersGroupID;
			break;
		case inspection_type_LayerInspection:
		case inspection_type_SpecialLayerInspection:
			layerData[e.first] = (LayerData *)e.second;
			break;
		case inspection_type_Measurement:
			measData = (MeasurementData *)e.second;
			isMeasurementDataAvailable = measData->isEnabled;
			measurementList = measData->measurementList;
			break;
		case inspection_type_ThreadDetection:
			thrData = (ThreadData *)e.second;
			isThreadDetectionAvailable = thrData->isEnabled;
			break;
		}
		

	}


	int i = 0;
	for (auto&e : taskLabelIDs)
	{
		if (temptaskLblIDs.count(e.first) == 0)
		{
			stripCharttaskID.insert(stripCharttaskID.begin() + i, 1, e.first);
			stripChartLabel.insert(stripChartLabel.begin() + i, 1, e.second);//.push_back(e.second);
			stripLabelCoordX.insert(stripLabelCoordX.begin() + i, 1, Chart::NoValue); //.push_back(Chart::NoValue);
			stripLabelCoordY.insert(stripLabelCoordY.begin() + i, 1, Chart::NoValue); //.push_back(Chart::NoValue);
			stripPercentCoordX.insert(stripPercentCoordX.begin() + i, 1, Chart::NoValue); //.push_back(Chart::NoValue);
			stripYValues.insert(stripYValues.begin() + i, 1, Chart::NoValue); //.push_back(Chart::NoValue);
			for (int r = 0; r < typeOfResults; r++)
			{
				taskwiseResultCount[r].insert(taskwiseResultCount[r].begin() + i, 1, 0);// .resize(taskLabelIDs.size());
			}
		}
		i++;

	}
}

void ChartDataManager::setModelData(CameraData &_cameraModelData)
{
	modelReceived = true;
	thisCameraModelData = _cameraModelData;
	if ((noOfCols == _cameraModelData.numberOfPanels) && (noOfRows == _cameraModelData.numberOfUps / noOfCols))
	{
	int	temp = 10;
	}
	else
	{
		noOfCols = _cameraModelData.numberOfPanels;
		noOfRows = _cameraModelData.numberOfUps / noOfCols;
		initializeHeatMap();
		
	
	}
	onesTuple.TupleGenConst(_cameraModelData.numberOfUps, 1);
	setHeatMapModelData();
}

void ChartDataManager::initializeStatsCountData()
{
	bool temp = false;
	for (auto &e : layerData)
	{
		try{

		int i = 0;
		for (auto &f : e.second->statisticsRegions)
		{
			HTuple find;
			
			if (statsRegIDs[e.first].Length() > 0)
				find = statsRegIDs[e.first].TupleFind(HTuple((int)f.first));
			if ((find == -1) || (find.Length() == 0))
			{

				statsRegionNames[e.first] = statsRegionNames[e.first].TupleConcat(HTuple(f.second.regionName.c_str()));
				statsCount[e.first] = statsCount[e.first].TupleConcat(0);

				statsPercentage[e.first] = statsPercentage[e.first].TupleConcat(0);
				statsRegIDs[e.first] = statsRegIDs[e.first].TupleConcat(HTuple((int)f.first));
			}
			else
			{
				statsRegionNames[e.first][find] = HTuple(f.second.regionName.c_str());
			}
			i++;
			HTuple ids = statsRegIDs[e.first];
			HTuple sc = statsRegionNames[e.first];
			HTuple sp = statsPercentage[e.first];
		}
		for (int c = 0; c < statsRegIDs[e.first].Length(); c++)
		{
			if (e.second->statisticsRegions.count((int)statsRegIDs[e.first][c].D()) == 0)
			{
				statsRegionNames[e.first] = statsRegionNames[e.first].TupleRemove(HTuple(c));
				statsCount[e.first] = statsCount[e.first].TupleRemove(HTuple(c));
				statsPercentage[e.first] = statsPercentage[e.first].TupleRemove(HTuple(c));
				statsRegIDs[e.first] = statsRegIDs[e.first].TupleRemove(HTuple(c));
			}

		}
		temp = e.second->statisticsRegions.size() > 0;
	}
			catch (HException &ex)
			{
				CString x;
				x.Format(_T("ChartDataManager Exception:Initializing Stats Count: %S"), ex.ErrorMessage().Text());
				AfxMessageBox(x);
			}
	}
	isStatChartDataAvailable = temp;
}

void ChartDataManager::updateStatsData()
{
	try {
		for (auto &e : layerData)
		{
			if(statsCount.count(e.first))
			{
				HTuple statsRgNms = statsRegionNames[e.first];
				HTuple statsCnt = statsCount[e.first];
				if (statsCnt[e.first].Length() > 0)
				{
					HTuple statRgID = statsRegIDs[e.first];
					HTuple statsRgNms = statsRegionNames[e.first];
					HTuple se = baResult->statisticsResultStatus[e.first];
					HTuple result = baResult->statisticsResultStatus[e.first];
					HTuple added = baResult->statisticsResultStatus[e.first].TupleGreaterElem(0);
					if( (result.Length() == statsCount[e.first].Length()) && (statsCount[e.first].Length()!=0))
					{
						statsCount[e.first] = statsCount[e.first].TupleAdd(added);
						statsPercentage[e.first] = statsCount[e.first].TupleMult(100.0 / (double)imageNumber);
						HTuple sc = statsCount[e.first];
						HTuple sp = statsPercentage[e.first];
					}
				}
			}
		}
	}

	catch (HException &ex)
	{
		CString x;
		x.Format(_T("ChartDataManager Exception:Updating Stats Count: %S"), ex.ErrorMessage().Text());
		AfxMessageBox(x);
	}

}

void ChartDataManager::updateHeatmapData()
{
	for (auto &e : baResult->groupOfDefectBlobsUPWiseStatus)
	{
		failureCount[e.first]= failureCount[e.first].TupleAdd(e.second.TupleGreaterElem(0));
		failurePercentage[e.first] = failureCount[e.first].TupleMult(100.0/(double)imageNumber);
	}
	
}


