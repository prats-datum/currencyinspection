// ImageWindowDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "ImageWindowDialog.h"
#include "afxdialogex.h"
#include "HalconCpp.h"
#include "ApplicationSettingsReader.h"
#include "ApplicationLogsCollector.h"

// ImageWindowDialog dialog

IMPLEMENT_DYNAMIC(ImageWindowDialog, CDialogEx)

ImageWindowDialog::ImageWindowDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_WINDOW, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);

}

ImageWindowDialog::~ImageWindowDialog()
{
	m_pEditBkBrush->DeleteObject();
}

void ImageWindowDialog::SetCameraGoldenData(CameraData &_cameraData)
{
	this->cameraData = &_cameraData;
	UpdateDisplay();
}

void ImageWindowDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE_WINDOW, staticImageWindow);
	DDX_Control(pDX, IDC_STATIC_RADIO_GROUP, contGroupBoxRadioButton);
	
}

BOOL ImageWindowDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!wndToolBar.CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_CUSTOMERASE | TBSTYLE_FLAT, WS_CHILD |
		WS_VISIBLE | CBRS_GRIPPER | CBRS_TOOLTIPS |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC| CBRS_ALIGN_LEFT)
		|| !wndToolBar.LoadToolBar(IDR_TOOLBAR_IMAGE))
	{
		TRACE0("Failed to Create Dialog Toolbar\n");
		EndDialog(IDCANCEL);
	}
	//wndToolBar.SetBarStyle(CBRS_ALIGN_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY);
	wndToolBar.EnableToolTips(TRUE);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	wndToolBar.MoveWindow(0, 0, 24, 120, 0);

	CRect rect;
	staticImageWindow.GetClientRect(&rect);
	mainWindow.OpenWindow(0, 0, rect.Width(), rect.Height(), (int)staticImageWindow.m_hWnd, "visible", "");
	isHWindowInitialized = true;
	lastSelectedRegionID = -1;
	lastSelectedLayerID = 0;
	mainWindow.RegisterForHalconWindowEvents(this);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_ANCHOR_BLUE);
	((CButton*)GetDlgItem(IDC_RADIO_ANCHOR))->SetBitmap(bmp);
	bmp.Detach(); // don't forget this 

	((CButton*)GetDlgItem(IDC_RADIO_ANCHOR))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SHEET_ANCHOR));
	((CButton*)GetDlgItem(IDC_RADIO_REP_ANCHOR))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_UP_ANCHOR));
	((CButton*)GetDlgItem(IDC_RADIO_UNIQUE_REGION))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SHEET_REGION));
	((CButton*)GetDlgItem(IDC_RADIO_REP_REGION))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_UP_REGION));
	((CButton*)GetDlgItem(IDC_RADIO_MEASUREMENT_REG))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_MEASUREMENT));
	((CButton*)GetDlgItem(IDC_RADIO_THREAD_REG))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_THREAD));
	((CButton*)GetDlgItem(IDC_RADIO_TRAINING_SET))->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_TRAINING_SET));
		
	
	toolTipCtrl.Create(this);
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_ANCHOR), _T("Anchor"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_REP_ANCHOR), _T("UP Anchor"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_UNIQUE_REGION), _T("Sheet Region"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_REP_REGION), _T("UP Region"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_MEASUREMENT_REG), _T("Registration Check"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_THREAD_REG), _T("Security Thread"));
	toolTipCtrl.AddTool(GetDlgItem(IDC_RADIO_TRAINING_SET), _T("Training Set")); 

	toolTipCtrl.Activate(true);
	return TRUE;
}

BOOL ImageWindowDialog::PreTranslateMessage(MSG* pMsg)
{

	CRect rect;
	staticImageWindow.GetWindowRect(rect);
	POINT pt = pMsg->pt;

	toolTipCtrl.RelayEvent(pMsg);
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		bRet = TRUE; // do not dispatch message
	}
	else if (rect.PtInRect(pt))
	{
		mainWindow.eventhandler(pMsg);
		bRet = TRUE; // do not dispatch message
		SetFocus();
		bRet = CDialogEx::PreTranslateMessage(pMsg);
	}
	else
	{
		bRet = CDialogEx::PreTranslateMessage(pMsg);
	}
	return bRet;
}

void ImageWindowDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (isHWindowInitialized)
	{
		CRect rect;
		staticImageWindow.GetClientRect(&rect);
		mainWindow.SetWindowExtents(0, 0, rect.Width(), rect.Height());
		UpdateDisplay();
	}
}

BEGIN_MESSAGE_MAP(ImageWindowDialog, CDialogEx)
	ON_WM_SIZE()
	ON_MESSAGE(UWM_SELECT_MASTER_IMAGE, &ImageWindowDialog::OnSetMasterImageMessage)
	ON_BN_CLICKED(IDC_RADIO_ANCHOR, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_REP_ANCHOR, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_UNIQUE_REGION, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_REP_REGION, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_THREAD_REG, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_TRAINING_SET, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_BN_CLICKED(IDC_RADIO_MEASUREMENT_REG, &ImageWindowDialog::OnRadioButtonSelectChanged)
	ON_COMMAND(ID_BUTTON_ADD_RECT_REGION, &ImageWindowDialog::OnClickDrawRectRegion)
	ON_COMMAND(ID_BUTTON_ADD_FREE_DRAW_REGION, &ImageWindowDialog::OnClickDrawFreeRegion)
	ON_COMMAND(ID_BUTTON_DELETE_SELECTED_REGION, &ImageWindowDialog::OnClickDeleteRegion)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ImageWindowDialog message handlers

void ImageWindowDialog::OnClickDrawRectRegion()
{
	if (lastSelectedRegionID >= 0)
	{
		UpdateRadioButtonForTheSelectedRegion();
		UpdateRegion(GetRectRegion());
	}
	else
	{
		MessageBox(_T("Please select the Region from the List"), _T("OptiCheck - Intaglio Inspection"), MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
	SetFocus();
}

void ImageWindowDialog::OnClickDrawFreeRegion()
{
	if (lastSelectedRegionID >= 0)
	{
		UpdateRadioButtonForTheSelectedRegion();
		UpdateRegion(GetFreeDrawRegion());
	}
	else
	{
		MessageBox(_T("Please select the Region from the List"), _T("OptiCheck - Intaglio Inspection"), MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
	SetFocus();
}

void ImageWindowDialog::OnClickDeleteRegion()
{
	if (lastSelectedRegionID >= 0)
	{
		mainWindow.ClearRegion(lastSelectedRegionID);
	}
	else
	{
		MessageBox(_T("Please select the Region from the List"), _T("OptiCheck - Intaglio Inspection"), MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
}

void ImageWindowDialog::DisplayTrainingSet(HImage &_tsImage)
{
	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_TRAINING_SET);
	lastDisplayedTS = _tsImage;
	DisplayImage(lastDisplayedTS);
}



void ImageWindowDialog::GetInpectionWindow()
{
	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_TRAINING_SET);
	try
	{
		DisplayImage(cameraData->masterImage);
		mainWindow.SetColor("green");
		double row1, row2, col1, col2;
		contGroupBoxRadioButton.SetEnable(FALSE);
		try
		{
			mainWindow.DrawRectangle1(&row1, &col1, &row2, &col2);
		}
		catch (HException &ex)
		{
			contGroupBoxRadioButton.SetEnable(TRUE);
			MessageBox(_T("The inspection Window you have drawn is incorrect! Please Select the Master again"), _T("OptiCheck - Intaglio Inspection"), MB_ICONERROR | MB_OK | MB_TOPMOST);
			GetParent()->PostMessageW(UWM_MASTER_IMAGE_SELECTION_FAILED, NULL, NULL);
			return;
		}
		contGroupBoxRadioButton.SetEnable(TRUE);

		int row2_int = row2;
		int row1_int = row1;
		int col2_int = col2;
		int col1_int = col1;


		if ((row2_int - row1_int + 1) % 2 != 0)
		{
			row2_int = row2_int - 1;
		}
		if ((col2_int - col1_int + 1) % 2 != 0)
		{
			col2_int = col2_int - 1;
		}
		cameraData->InspectionWindow.GenRectangle1(row1_int, col1_int, row2_int, col2_int);

		if ((cameraData->InspectionWindow.Area()[0].D() / cameraData->masterImage.GetDomain().Area()[0].D()) * 100 < 50.0) // Need to move it to application settings
		{
			MessageBox(_T("The inspection Window you have drawn is incorrect! Please Select the Master again"), _T("OptiCheck - Intaglio Inspection"), MB_ICONERROR | MB_OK | MB_TOPMOST);
			GetParent()->PostMessageW(UWM_MASTER_IMAGE_SELECTION_FAILED, NULL, NULL);
			return;
		}
		HImage tempImage = cameraData->masterImage.ReduceDomain(cameraData->InspectionWindow);
		cameraData->masterImageReduced = tempImage.CropDomain();
		cameraData->SetInspectionWindowToLayers();
		cameraData->SetInspectionWindowToBlobAnalyzer();
		cameraData->SetInspectionWindowToThreadInspection();
	}
	catch (HException &ex)
	{
		//CString errorMessage;
		//errorMessage.Format(_T("%S"), ex.ErrorMessage().Text());
		//AfxMessageBox(errorMessage);
		MessageBox(_T("The inspection Window you have drawn is incorrect! Please Select the Master again"), _T("OptiCheck - Intaglio Inspection"), MB_ICONERROR | MB_OK | MB_TOPMOST);
		GetParent()->PostMessageW(UWM_MASTER_IMAGE_SELECTION_FAILED, NULL, NULL);
		return;
	}
	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_ANCHOR);
	UpdateDisplay();
	UpdateAllRepLocations();
	UpdateAllMeasurementCoordinates();
	GetParent()->PostMessageW(UWM_MASTER_IMAGE_SELECTED, NULL, NULL);
	return;
}

void ImageWindowDialog::OnRegionSelectedEvent(UINT regID, void *tag)
{
	int *temp = (int*)tag;
	RegionTypes type = (RegionTypes)(*temp);
	switch (type)	
	{
	case UniqueInspectionRegion:
	case UniqueMaskRegion:
	case RepititiveInspectionRegion:
	case RepititiveMaskRegion:
	case StatisticsRegion:
		lastSelectedRegionID = regID;
		GetParent()->PostMessageW(UWM_INSPECTION_REGION_CLICKED, (WPARAM)type, (LPARAM)regID);
		break;
	case AnchorRegion:
	case RepAnchorRegion:
	case ThreadRegion:
	case MeasurementRegion:
	default:
		break;
	}
}

void ImageWindowDialog::OnRegionModifiedEvent(UINT regID, void *tag)
{
	int *temp = (int*)tag;
	RegionTypes type = (RegionTypes)(*temp);
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	switch (type)
	{
	case UniqueInspectionRegion:
		break;
	case UniqueMaskRegion:
		break;
	case RepititiveInspectionRegion:
		if (layerData->insRegions.find(regID) != layerData->insRegions.end())
		{
			UpdateRepeatingPortion((LayerRegion *)&(layerData->insRegions[regID]));
		}
		break;
	case RepititiveMaskRegion:
		if (layerData->maskRegions.find(regID) != layerData->maskRegions.end())
		{
			UpdateRepeatingPortion((LayerRegion *)&(layerData->maskRegions[regID]));
		}
		break;
	case StatisticsRegion:
		if (layerData->statisticsRegions.find(regID) != layerData->statisticsRegions.end())
		{
			UpdateRepeatingPortion((LayerRegion *)&(layerData->statisticsRegions[regID]));
		}
		break;
	case AnchorRegion:
		layerData->anchorRegions.CreateModel(cameraData->masterImageReduced);
		layerData->UpdateAnchorRefLocations(cameraData->masterImage);
		UpdateMeasurementReferenceCoordinates(layerData);
		break;
	case RepAnchorRegion:
		UpdateAllRepLocations();
		UpdateAllMeasurementCoordinates();
		break;
	case ThreadRegion:
		if (cameraData->GetThread() != NULL)
		{
			Hlong row1, column1, row2, column2, threadSearchWindowHeight, threadSearchWindowWidth;
			double minWindowWidth, minWindowHeight;
			HRegion threadWindow = cameraData->GetThread()->threadPatternRegions[0].ZoomRegion(cameraData->GetThread()->imageScaleFactor, cameraData->GetThread()->imageScaleFactor);
			threadWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
			minWindowWidth = ((column2 - column1) + 1) * 0.55;
			minWindowHeight = ((row2 - row1) + 1) * 0.55;

			HImage imageL, imageA, imageB, redImage, greenImage, blueImage, compositeImage;
			redImage = cameraData->masterImageReduced.Decompose3(&greenImage, &blueImage);
			imageL = redImage.TransFromRgb(greenImage, blueImage, &imageA, &imageB, "cielab");
			HRegion zoomedSearchWindow = cameraData->GetThread()->threadSearchWindows[0].ZoomRegion(cameraData->GetThread()->imageScaleFactor, cameraData->GetThread()->imageScaleFactor);

			zoomedSearchWindow.SmallestRectangle1(&row1, &column1, &row2, &column2);
			threadSearchWindowHeight = (row2 - row1) + 1;
			threadSearchWindowWidth = (column2 - column1) + 1;

			if (ApplicationSettingsReader::GetInstance()->UseThreeChannelImageForThread)
			{
				compositeImage = imageA.ZoomImageFactor(cameraData->GetThread()->imageScaleFactor, cameraData->GetThread()->imageScaleFactor, "weighted");
			}
			else
			{

				HImage BZoomedImage = imageB.ZoomImageFactor(cameraData->GetThread()->imageScaleFactor, cameraData->GetThread()->imageScaleFactor, "weighted");
				HImage IRZoomedImage = cameraData->masterIRImage.ReduceDomain(cameraData->InspectionWindow).CropDomain().ZoomImageFactor(cameraData->GetThread()->imageScaleFactor, cameraData->GetThread()->imageScaleFactor, "weighted");
				compositeImage = BZoomedImage.AddImage(IRZoomedImage, 1, 0);
			}
			compositeImage = compositeImage.ReduceDomain(zoomedSearchWindow);

			HImage minImage = compositeImage.GrayErosionRect(minWindowHeight, minWindowWidth);
			HImage minImageScaled = minImage.ScaleImageMax();
			HImage minScaledMean = minImageScaled.MeanImage(threadSearchWindowWidth / 2, threadSearchWindowHeight / 10);
			double meanScaled = 0, meanScaledMean = 0, deviation;
			for (auto &e : cameraData->GetThread()->threadPatternRegions)
			{
				meanScaled += minImageScaled.Intensity(e, &deviation);
				meanScaledMean += minScaledMean.Intensity(e, &deviation);
			}
			meanScaled = meanScaled / cameraData->GetThread()->threadPatternRegions.size();
			meanScaledMean = meanScaledMean / cameraData->GetThread()->threadPatternRegions.size();
			cameraData->GetThread()->dynamicThresholdValue = (meanScaledMean - meanScaled) * 0.85;
		}
		break;
	case MeasurementRegion:
		for (auto &e : cameraData->GetMeasurement()->measurementList)
		{
			if (e.firstMeasurementPoint.tpData.regID == regID || e.secondMeasurementPoint.tpData.regID == regID)
			{
				UpdateMeasurementCoordinates(&e);
			}
		}
		break;
	default:
		break;
	}
}

void ImageWindowDialog::UpdateAllRepRegionsForTheLayer()
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	
	for (auto &iter1: layerData->insRegions)
	{
		if (iter1.second.insRegionType == RepititiveInspectionRegion)
		{
			UpdateRepeatingPortion((LayerRegion *)&(iter1.second));
		}
	}
	for (auto &iter1: layerData->maskRegions)
	{
		if (iter1.second.insRegionType == RepititiveMaskRegion)
		{
			UpdateRepeatingPortion((LayerRegion *)&(iter1.second));
		}
	}
	for (auto &iter1: layerData->statisticsRegions)
	{
		UpdateRepeatingPortion((LayerRegion *)&(iter1.second));
	}

}

void ImageWindowDialog::UpdateRepeatingPortion(LayerRegion *reg)
{
	reg->regionList.clear();
	for (auto &iter: reg->repitingPortionList)
	{
		HRegion uniRepRegion;
		uniRepRegion.GenEmptyRegion();
		HRegion tempReg = iter;
		int count = cameraData->repRowAll.Length();
		HHomMat2D tempHomMat2D;
		for (int index = 0; index < count; index++)
		{
			tempHomMat2D.VectorAngleToRigid(cameraData->repRowRef, cameraData->repColumnRef, cameraData->repAngleRef,
				cameraData->repRowAll[index], cameraData->repColumnAll[index], cameraData->repAngleAll[index]);
			HRegion affinedReg = tempReg.AffineTransRegion(tempHomMat2D, "nearest_neighbor");
			uniRepRegion = uniRepRegion.Union2(affinedReg);
		}
		reg->regionList.push_back(uniRepRegion);
	}
}

void ImageWindowDialog::UpdateMeasurementCoordinates(Measurement *measurement)
{
	int count = cameraData->repRowAll.Length();
	int index = count / 2;

	HHomMat2D tempHomMat2D;
	tempHomMat2D.VectorAngleToRigid(cameraData->repRowRef, cameraData->repColumnRef, cameraData->repAngleRef,
		cameraData->repRowAll[index], cameraData->repColumnAll[index], cameraData->repAngleAll[index]);
	HTuple tempRow, tempColumn;
	measurement->firstMeasurementPoint.measurementPointRegion.AreaCenter(&tempRow, &tempColumn);
	measurement->firstMeasurementPoint.row = tempHomMat2D.AffineTransPoint2d(tempRow, tempColumn, &measurement->firstMeasurementPoint.column);
	measurement->secondMeasurementPoint.measurementPointRegion.AreaCenter(&tempRow, &tempColumn);
	measurement->secondMeasurementPoint.row = tempHomMat2D.AffineTransPoint2d(tempRow, tempColumn, &measurement->secondMeasurementPoint.column);
	GetParent()->PostMessageW(UWM_UPDATE_CURRENT_MEASUREMENT_VALUE, (WPARAM)abs(measurement->secondMeasurementPoint.column[0].D() - measurement->firstMeasurementPoint.column[0].D()),
		(LPARAM)abs(measurement->secondMeasurementPoint.row[0].D() - measurement->firstMeasurementPoint.row[0].D()));
}

void ImageWindowDialog::UpdateAllMeasurementCoordinates()
{
	for (auto &e : cameraData->GetMeasurement()->measurementList)
	{
		UpdateMeasurementCoordinates(&e);
	}
}

void ImageWindowDialog::UpdateMeasurementReferenceCoordinates(LayerData *layerData)
{
	for (auto &e : cameraData->GetMeasurement()->measurementList)
	{
		e.UpdateMeasurementPointsRefLocation(layerData->rowRef, layerData->columnRef, layerData->angleRef, layerData->taskID);
	}
}

void ImageWindowDialog::UpdateAllRepLocations()
{
	HTuple row1, col1, row2, col2;
	HRegion patternReg = cameraData->repAnchor.regionList.front();
	HRegion singleImageReg = cameraData->repAnchor.regionList.back();
	singleImageReg.SmallestRectangle1(&row1, &col1, &row2, &col2);
	HHomMat2D temMat2D;
	temMat2D.VectorAngleToRigid(row1[0].D(), col1[0].D(), 0.0, 0.0, 0.0, 0.0);
	patternReg = patternReg.AffineTransRegion(temMat2D, "nearest_neighbor");
	HImage tempSearchImage;
	if (cameraData->masterImageReduced.CountChannels() == 3)
	{
		tempSearchImage = cameraData->masterImageReduced.Rgb1ToGray();
	}
	else
	{
		tempSearchImage = cameraData->masterImageReduced;
	}

	HImage patternImage = tempSearchImage.ReduceDomain(singleImageReg);
	patternImage = patternImage.CropDomain();
	patternImage = patternImage.ReduceDomain(patternReg);
	
	HTuple rowRef, columnRef, angleRef, scoreRef;
	if (cameraData->repAnchor.searchType == ShapeBased)
	{
		try
		{
			HShapeModel tempShapeModel;
			tempShapeModel.CreateShapeModel(patternImage, 0, -0.2, 0.4, "auto", "auto", "use_polarity", "auto", "auto");
			patternImage.FindShapeModel(tempShapeModel, -0.2, 0.4, 0.5, 1, 0.5, "least_squares", 0, 0.9, &rowRef, &columnRef, &angleRef, &scoreRef);
			tempSearchImage.FindShapeModel(tempShapeModel, -0.2, 0.4, 0.5, cameraData->numberOfUps, 0.5, "least_squares", 0, 0.9, &cameraData->repRowAll, &cameraData->repColumnAll, &cameraData->repAngleAll, &scoreRef);
		}
		catch (HException &ex)
		{
			rowRef = 0.0;
			columnRef = 0.0;
			angleRef = 0.0;
		}
	}
	else
	{
		try
		{
			HNCCModel tempNCCModel;
			tempNCCModel.CreateNccModel(patternImage, 0, -0.2, 0.4, "auto", "use_polarity");
			patternImage.FindNccModel(tempNCCModel, -0.2, 0.4, 0.5, 1, 0.5, "true", 0, &rowRef, &columnRef, &angleRef, &scoreRef);
			tempSearchImage.FindNccModel(tempNCCModel, -0.2, 0.4, 0.5, cameraData->numberOfUps, 0.5, "true", 0, &cameraData->repRowAll, &cameraData->repColumnAll, &cameraData->repAngleAll, &scoreRef);
		}
		catch (HException &ex)
		{
			rowRef = 0.0;
			columnRef = 0.0;
			angleRef = 0.0;
		}
	}
	cameraData->repRowRef = rowRef[0].D();
	cameraData->repColumnRef = columnRef[0].D();
	cameraData->repAngleRef = angleRef[0].D();
	UpdateAllRepRegionsForTheLayer();
}

void ImageWindowDialog::UpdateRadioButtonForTheSelectedRegion()
{
	if (lastSelectedRegionID >= 0)
	{
		switch (cameraData->GetRegionType(lastSelectedLayerID, lastSelectedRegionID))
		{
		case UniqueInspectionRegion:
		case UniqueMaskRegion:
			CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_UNIQUE_REGION);
			break;
		case RepititiveInspectionRegion:
		case RepititiveMaskRegion:
		case StatisticsRegion:
			CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_REP_REGION);
			break;
		default:
			break;
		} 
		UpdateDisplay();
	}
}

HRegion ImageWindowDialog::GetFreeDrawRegion()
{
	ApplicationLogsCollector::GetLogger()->AppendLog("Draw a Freedraw Area with left mouse button & quit with right mouse button", Severity::info);
	mainWindow.SetColor("green");
	HRegion tempRegion;
	GetParent()->PostMessageW(UWM_DISABLE_ALL_OPERATIONS, (WPARAM)NULL, (LPARAM)NULL);
	contGroupBoxRadioButton.SetEnable(FALSE);
	wndToolBar.GetToolBarCtrl().EnableWindow(FALSE);
	tempRegion = mainWindow.DrawRegion();
	wndToolBar.GetToolBarCtrl().EnableWindow(TRUE);
	contGroupBoxRadioButton.SetEnable(TRUE);
	GetParent()->PostMessageW(UWM_ENABLE_ALL_OPERATIONS, (WPARAM)NULL, (LPARAM)NULL);
	ApplicationLogsCollector::GetLogger()->AppendLog("", Severity::none);
	return tempRegion;
}

HRegion ImageWindowDialog::GetRectRegion()
{
	ApplicationLogsCollector::GetLogger()->AppendLog("Draw a Rectangle Area with left mouse button & quit with right mouse button", Severity::info);
	mainWindow.SetColor("green");
	HRegion tempRegion;
	GetParent()->PostMessageW(UWM_DISABLE_ALL_OPERATIONS, (WPARAM)NULL, (LPARAM)NULL);
	contGroupBoxRadioButton.SetEnable(FALSE);
	wndToolBar.GetToolBarCtrl().EnableWindow(FALSE);
	double r1, c1, r2, c2;
	mainWindow.DrawRectangle1(&r1, &c1, &r2, &c2);
	if (r1 == 0.0000 && r2 == 0.0000 && c1 == 0.0000 && c2 == 0.0000)
	{
		r1 = 100.0;
		c1 = 100.0;
		r2 = 200.0;
		c2 = 200.0;
	}
	tempRegion.GenRectangle1(r1, c1, r2, c2);
	wndToolBar.GetToolBarCtrl().EnableWindow(TRUE);
	contGroupBoxRadioButton.SetEnable(TRUE);
	GetParent()->PostMessageW(UWM_ENABLE_ALL_OPERATIONS, (WPARAM)NULL, (LPARAM)NULL);
	ApplicationLogsCollector::GetLogger()->AppendLog("", Severity::none);
	return tempRegion;
}

void ImageWindowDialog::UpdateDisplay()
{
	int checkedButton = GetCheckedRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET);
	HSystem::SetSystem("flush_graphic", "false");
	switch (checkedButton)
	{
	case IDC_RADIO_ANCHOR:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(cameraData->masterImageReduced);
			DisplayAnchor(lastSelectedLayerID);
		}
		break;
	case IDC_RADIO_REP_ANCHOR:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(cameraData->masterImageReduced);
			DisplayRepAnchor(lastSelectedLayerID);
		}
		break;
	case IDC_RADIO_UNIQUE_REGION:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(cameraData->masterImageReduced);
			DisplayUniqueRegions(lastSelectedLayerID);
		}
		break;
	case IDC_RADIO_REP_REGION:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(GetSingleNoteImage());
			DisplayRepRegions(lastSelectedLayerID);
		}
		break;
	case IDC_RADIO_THREAD_REG:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(cameraData->masterImageReduced);
			DisplayThreadRegions();
		}
		break;
	case IDC_RADIO_MEASUREMENT_REG:
		if (cameraData->masterImageReduced.IsInitialized())
		{
			DisplayImage(GetSingleNoteImage());
			DisplayMeasurementRegions();
		}
		break;
	case IDC_RADIO_TRAINING_SET:
		if (lastDisplayedTS.IsInitialized())
		{
			DisplayImage(lastDisplayedTS);
		}
		break;
	default:
		break;
	}
	HSystem::SetSystem("flush_graphic", "true");
	mainWindow.DispCircle(-1.0, -1.0, 1.0);
}

void ImageWindowDialog::DisplayImage(HImage &_imageToDisplay)
{
	mainWindow.ClearWindow();
	mainWindow.AddImage(_imageToDisplay);
}

void ImageWindowDialog::DisplayAnchor(UINT _layerID)
{
	LayerData *layerData = cameraData->GetLayer(_layerID);
	for (auto &regIter: layerData->anchorRegions.regionList)
	{
		if (modeOfOperation == InspectionMode)
		{
			mainWindow.AddNonMovableRegion(regIter, layerData->anchorRegions.regID, "blue", (void *)&layerData->anchorRegions.regType);
		}
		else
		{
			mainWindow.AddNonEditableRegion(regIter, layerData->anchorRegions.regID, "blue", (void *)&layerData->anchorRegions.regType);
		}
	}
	return;
}

void ImageWindowDialog::DisplayRepAnchor(UINT _layerID)
{

	if (modeOfOperation == InspectionMode)
	{
		mainWindow.AddNonMovableRegion(cameraData->repAnchor.regionList.back(), cameraData->repAnchor.regID, "orange", (void *)&cameraData->repAnchor.regType);
		mainWindow.AddNonMovableRegion(cameraData->repAnchor.regionList.front(), cameraData->repAnchor.regID, "orange", (void *)&cameraData->repAnchor.regType);
	}
	else
	{
		mainWindow.AddEditableRegion(cameraData->repAnchor.regionList.back(), cameraData->repAnchor.regID, "orange", (void *)&cameraData->repAnchor.regType);
		mainWindow.AddNonEditableRegion(cameraData->repAnchor.regionList.front(), cameraData->repAnchor.regID, "orange", (void *)&cameraData->repAnchor.regType);
	}


	return;
}

void ImageWindowDialog::DisplayUniqueInspectionRegions(UINT _layerID)
{
	for (auto &insRegIter: this->cameraData->GetLayer(_layerID)->insRegions)
	{
		for (auto &regIter: insRegIter.second.regionList)
		{
			if (insRegIter.second.insRegionType == UniqueInspectionRegion)
			{
				mainWindow.AddEditableRegion(regIter, insRegIter.second.regionID, "green", (void *) &insRegIter.second.insRegionType);
			}
			else
			{
				mainWindow.AddNonMovableRegion(regIter, insRegIter.second.regionID, "green", (void *)&insRegIter.second.insRegionType);
			}
		}
	}
	return;
}

void ImageWindowDialog::DisplayUniqueMaskRegions(UINT _layerID)
{
	for (auto &insRegIter : this->cameraData->GetLayer(_layerID)->maskRegions)
	{
		for (auto &regIter : insRegIter.second.regionList)
		{
			if (insRegIter.second.insRegionType == UniqueMaskRegion)
			{
				mainWindow.AddEditableRegion(regIter, insRegIter.second.regionID, "red", (void *)&insRegIter.second.insRegionType);
			}
			else
			{
				mainWindow.AddNonMovableRegion(regIter, insRegIter.second.regionID, "red", (void *)&insRegIter.second.insRegionType);
			}
		}
	}
	return;
}


void ImageWindowDialog::DisplayUniqueStatisticsRegions(UINT _layerID)
{
	for (auto &insRegIter : this->cameraData->GetLayer(_layerID)->statisticsRegions)
	{
		for (auto &regIter : insRegIter.second.regionList)
		{
			mainWindow.AddNonMovableRegion(regIter, insRegIter.second.regionID, "blue", (void *)&insRegIter.second.insRegionType);
		}
	}
	return;
}

void ImageWindowDialog::DisplayUniqueRegions(UINT _layerID)
{
	DisplayUniqueInspectionRegions(_layerID);
	DisplayUniqueMaskRegions(_layerID);
	DisplayUniqueStatisticsRegions(_layerID);
}


void ImageWindowDialog::DisplayRepInspectionRegions(UINT _layerID)
{
	for (auto &insRegIter : this->cameraData->GetLayer(_layerID)->insRegions)
	{
		if (insRegIter.second.insRegionType == RepititiveInspectionRegion)
		{
			for (auto &regIter : insRegIter.second.repitingPortionList)
			{
				mainWindow.AddEditableRegion(regIter, insRegIter.second.regionID, "green", (void *)&(insRegIter.second.insRegionType));
			}
		}
	}
	return;
}
void ImageWindowDialog::DisplayRepMaskRegions(UINT _layerID)
{
	for (auto &insRegIter : this->cameraData->GetLayer(_layerID)->maskRegions)
	{
		if (insRegIter.second.insRegionType == RepititiveMaskRegion)
		{
			for (auto &regIter : insRegIter.second.repitingPortionList)
			{
				mainWindow.AddEditableRegion(regIter, insRegIter.second.regionID, "red", (void *)&(insRegIter.second.insRegionType));
			}
		}
	}
	return;
}


void ImageWindowDialog::DisplayRepStatisticsRegions(UINT _layerID)
{
	for (auto &insRegIter : this->cameraData->GetLayer(_layerID)->statisticsRegions)
	{
		for (auto &regIter : insRegIter.second.repitingPortionList)
		{
			mainWindow.AddEditableRegion(regIter, insRegIter.second.regionID, "blue", (void *)&(insRegIter.second.insRegionType));
		}
	}
	return;
}

void ImageWindowDialog::DisplayRepRegions(UINT _layerID)
{
	DisplayRepInspectionRegions(_layerID);
	DisplayRepMaskRegions(_layerID);
	DisplayRepStatisticsRegions(_layerID);
}


void ImageWindowDialog::DisplayThreadRegions()
{
	ThreadData *threadData = this->cameraData->GetThread();
	if (threadData != NULL)
	{
		int index = 0;
		for (auto &iter1 : threadData->threadSearchWindows)
		{
			index++;
			if (index == 1)
			{
				continue;
			}
			mainWindow.AddEditableRegion(iter1, 0, "green", (void *)&threadData->regType);
		}
		// purposefully added the thread region at the end
		if (threadData->threadPatternRegions.size() >= 2)
		{
			mainWindow.AddThreadRegion(threadData->threadSearchWindows[0], threadData->threadPatternRegions[0], threadData->threadPatternRegions[1], 0, "green", (void *)&threadData->regType);
		}
	}
}


void ImageWindowDialog::DisplayMeasurementRegions()
{	
	MeasurementData *measurementData = this->cameraData->GetMeasurement();
	if (measurementData != NULL)
	{
		for (auto &iter1 : measurementData->measurementList)
		{
			mainWindow.AddNonEditableRegion(iter1.firstMeasurementPoint.measurementPointRegion, iter1.firstMeasurementPoint.tpData.regID, "green", (void *)&measurementData->regType);
			mainWindow.AddNonEditableRegion(iter1.secondMeasurementPoint.measurementPointRegion, iter1.secondMeasurementPoint.tpData.regID, "red", (void *)&measurementData->regType);
		}
	}
}

void ImageWindowDialog::ClearDisplay()
{
	mainWindow.ClearWindow();
}

LRESULT ImageWindowDialog::OnSetMasterImageMessage(WPARAM wParam, LPARAM lParam)
{
	GetInpectionWindow();
	return 1;
}


//LRESULT ImageWindowDialog::OnDrawUniqueInsRegMessage(WPARAM wParam, LPARAM lParam)
//{
//	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_UNIQUE_REGION);
//	UpdateDisplay();
//	UpdateUniqueInsReg(lastSelectedLayerIndex, (UINT)wParam,  GetRegion());
//	GetParent()->PostMessageW(UWM_COMPLETED_DRAWING_REG, NULL, NULL);
//	return 1;
//}
//
//LRESULT ImageWindowDialog::OnDrawUniqueMaskRegMessage(WPARAM wParam, LPARAM lParam)
//{
//	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_UNIQUE_REGION);
//	UpdateDisplay();
//	AddUniqueMaskReg(lastSelectedLayerIndex, GetRegion());
//	GetParent()->PostMessageW(UWM_COMPLETED_DRAWING_REG, NULL, NULL);
//	return 1;
//}
//
//LRESULT ImageWindowDialog::OnDrawRepInsRegMessage(WPARAM wParam, LPARAM lParam)
//{
//	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_REP_REGION);
//	UpdateDisplay();
//	AddRepInsReg(lastSelectedLayerIndex, GetRegion());
//	GetParent()->PostMessageW(UWM_COMPLETED_DRAWING_REG, NULL, NULL);
//	return 1;
//}
//
//LRESULT ImageWindowDialog::OnDrawRepMaskRegMessage(WPARAM wParam, LPARAM lParam)
//{
//	CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_REP_REGION);
//	UpdateDisplay();
//	AddRepsMaskReg(lastSelectedLayerIndex, GetRegion());
//	GetParent()->PostMessageW(UWM_COMPLETED_DRAWING_REG, NULL, NULL);
//	return 1;
//}

//void ImageWindowDialog::AddAnchorReg(UINT _layerID, HRegion &_anchorReg)
//{
//	bool isAdded = false;
//	lastSelectedLayerIndex = _layerID;
//	std::vector<LayerAnchorRegion>::iterator iter;
//	for (iter = this->anchorRegions.begin(); iter != this->anchorRegions.end(); ++iter)
//	{
//		if (iter->layerID == _layerID)
//		{
//			iter->regionList.push_back(_anchorReg);
//			isAdded = true;
//			break;
//		}
//	}
//	if (!isAdded)
//	{
//		LayerAnchorRegion tempLayerAnchorReg;
//		tempLayerAnchorReg.layerID = _layerID;
//		tempLayerAnchorReg.regionList.push_back(_anchorReg);
//		anchorRegions.push_back(tempLayerAnchorReg);
//	}
//	UpdateDisplay();
//}
//
//void ImageWindowDialog::AddRepAnchorReg(UINT _layerID, HRegion &_repAnchorReg,  int _numberOfNotes)
//{
//	bool isAdded = false;
//	numberOfNotes = _numberOfNotes;
//	lastSelectedLayerIndex = _layerID;
//	std::vector<LayerAnchorRegion>::iterator iter;
//	for (iter = this->repAnchor.begin(); iter != this->repAnchor.end(); ++iter)
//	{
//		if (iter->layerID == _layerID)
//		{
//			iter->regionList.push_back(_repAnchorReg);
//			isAdded = true;
//			break;
//		}
//	}
//	if (!isAdded)
//	{
//		LayerAnchorRegion tempLayerAnchorReg;
//		tempLayerAnchorReg.layerID = _layerID;
//		tempLayerAnchorReg.regionList.push_back(_repAnchorReg);
//		repAnchor.push_back(tempLayerAnchorReg);
//	}
//	UpdateDisplay();
//}


void ImageWindowDialog::UpdateRegion(HRegion &tempRegion)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->insRegions.find(lastSelectedRegionID) != layerData->insRegions.end())
	{
		if (layerData->insRegions[lastSelectedRegionID].insRegionType == UniqueInspectionRegion)
		{
			UpdateUniqueInsReg(lastSelectedLayerID, lastSelectedRegionID, tempRegion);
		}
		else
		{
			UpdateRepInsReg(lastSelectedLayerID, lastSelectedRegionID, tempRegion);
		}
	}
	else if (layerData->maskRegions.find(lastSelectedRegionID) != layerData->maskRegions.end())
	{
		if (layerData->maskRegions[lastSelectedRegionID].insRegionType == UniqueMaskRegion)
		{
			UpdateUniqueMaskReg(lastSelectedLayerID, lastSelectedRegionID, tempRegion);
		}
		else
		{
			UpdateRepsMaskReg(lastSelectedLayerID, lastSelectedRegionID, tempRegion);
		}
	}
	else if (layerData->statisticsRegions.find(lastSelectedRegionID) != layerData->statisticsRegions.end())
	{
		UpdateStatisticsReg(lastSelectedLayerID, lastSelectedRegionID, tempRegion);
	}
}


void ImageWindowDialog::UpdateUniqueInsReg(UINT _layerID, UINT _regID, HRegion &_uniqueInsReg)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->insRegions.find(_regID) != layerData->insRegions.end())
	{
		layerData->insRegions[_regID].regionList.push_back(_uniqueInsReg);
	}
	UpdateDisplay();
}

void ImageWindowDialog::UpdateUniqueMaskReg(UINT _layerID, UINT _regID, HRegion &_uniqueMaskReg)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->maskRegions.find(_regID) != layerData->maskRegions.end())
	{
		layerData->maskRegions[_regID].regionList.push_back(_uniqueMaskReg);
	}	
	UpdateDisplay();
}

void ImageWindowDialog::UpdateRepInsReg(UINT _layerID, UINT _regID, HRegion &_repInsReg)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->insRegions.find(_regID) != layerData->insRegions.end())
	{
		layerData->insRegions[_regID].repitingPortionList.push_back(_repInsReg);
		HRegion uniRepRegion;
		uniRepRegion.GenEmptyRegion();
		HRegion tempReg = _repInsReg;
		int count = cameraData->repRowAll.Length();
		HHomMat2D tempHomMat2D;
		for (int index = 0; index < count; index++)
		{
			tempHomMat2D.VectorAngleToRigid(cameraData->repRowRef, cameraData->repColumnRef, cameraData->repAngleRef,
				cameraData->repRowAll[index], cameraData->repColumnAll[index], cameraData->repAngleAll[index]);
			HRegion affinedReg = tempReg.AffineTransRegion(tempHomMat2D, "nearest_neighbor");
			uniRepRegion = uniRepRegion.Union2(affinedReg);
		}
		layerData->insRegions[_regID].regionList.push_back(uniRepRegion);
	}
	UpdateDisplay();
}


void ImageWindowDialog::UpdateRepsMaskReg(UINT _layerID, UINT _regID, HRegion &_repMaskReg)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->maskRegions.find(_regID) != layerData->maskRegions.end())
	{
		layerData->maskRegions[_regID].repitingPortionList.push_back(_repMaskReg);
		HRegion uniRepRegion;
		uniRepRegion.GenEmptyRegion();
		HRegion tempReg = _repMaskReg;
		int count = cameraData->repRowAll.Length();
		HHomMat2D tempHomMat2D;
		for (int index = 0; index < count; index++)
		{
			tempHomMat2D.VectorAngleToRigid(cameraData->repRowRef, cameraData->repColumnRef, cameraData->repAngleRef,
				cameraData->repRowAll[index], cameraData->repColumnAll[index], cameraData->repAngleAll[index]);
			HRegion affinedReg = tempReg.AffineTransRegion(tempHomMat2D, "nearest_neighbor");
			uniRepRegion = uniRepRegion.Union2(affinedReg);
		}
		layerData->maskRegions[_regID].regionList.push_back(uniRepRegion);
	}
	UpdateDisplay();
}

void ImageWindowDialog::UpdateStatisticsReg(UINT _layerID, UINT _regID, HRegion &_repStatReg)
{
	LayerData *layerData = cameraData->GetLayer(lastSelectedLayerID);
	if (layerData->statisticsRegions.find(_regID) != layerData->statisticsRegions.end())
	{
		layerData->statisticsRegions[_regID].repitingPortionList.push_back(_repStatReg);
		HRegion uniRepRegion;
		uniRepRegion.GenEmptyRegion();
		HRegion tempReg = _repStatReg;
		int count = cameraData->repRowAll.Length();
		HHomMat2D tempHomMat2D;
		for (int index = 0; index < count; index++)
		{
			tempHomMat2D.VectorAngleToRigid(cameraData->repRowRef, cameraData->repColumnRef, cameraData->repAngleRef,
				cameraData->repRowAll[index], cameraData->repColumnAll[index], cameraData->repAngleAll[index]);
			HRegion affinedReg = tempReg.AffineTransRegion(tempHomMat2D, "nearest_neighbor");
			uniRepRegion = uniRepRegion.Union2(affinedReg);
		}
		layerData->statisticsRegions[_regID].regionList.push_back(uniRepRegion);
	}
	UpdateDisplay();
}


void ImageWindowDialog::ChangeSelectedLayerIndex(UINT _layerID)
{
	lastSelectedLayerID = _layerID;
	lastSelectedRegionID = -1;
	UpdateDisplay();
}


void ImageWindowDialog::ChangeSelectedRegionID(int _regID, RegionTypes _regType)
{
	lastSelectedRegionID = _regID;
	if (lastSelectedRegionID > 0)
	{
		switch (_regType)
		{
		case UniqueInspectionRegion:
		case UniqueMaskRegion:
			CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_UNIQUE_REGION);
			break;
		case RepititiveInspectionRegion:
		case RepititiveMaskRegion:
		case StatisticsRegion:
			CheckRadioButton(IDC_RADIO_ANCHOR, IDC_RADIO_TRAINING_SET, IDC_RADIO_REP_REGION);
			break;
		default:
			break;
		}
	}
	UpdateDisplay();
	if (lastSelectedRegionID > 0)
	{
		mainWindow.SetSelectedRegionData(_regID);
	}
}



void ImageWindowDialog::SetOperationMode(OperationMode _modeOfOperation)
{
	modeOfOperation = _modeOfOperation;
	if (modeOfOperation == InspectionMode)
	{
		wndToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE_SELECTED_REGION, false);
	}
	else
	{
		wndToolBar.GetToolBarCtrl().EnableButton(ID_BUTTON_DELETE_SELECTED_REGION, true);
	}
}

void ImageWindowDialog::OnRadioButtonSelectChanged()
{
	// TODO: Add your control notification handler code here
	UpdateDisplay();
}


HImage ImageWindowDialog::GetSingleNoteImage()
{
	HImage tempImage;
	tempImage = cameraData->masterImageReduced.ReduceDomain(cameraData->repAnchor.regionList.back());
	tempImage = tempImage.CropDomain();
	return tempImage;
}





BOOL ImageWindowDialog::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(DialogBackgroundColor);    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);    // restore old brush
	return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}


HBRUSH ImageWindowDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor) {

	case CTLCOLOR_MSGBOX:
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_EDIT:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_LISTBOX:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_BTN:
		// Set color to green on black and return the background
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_DLG:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_SCROLLBAR:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_STATIC:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_MAX:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());

	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}


