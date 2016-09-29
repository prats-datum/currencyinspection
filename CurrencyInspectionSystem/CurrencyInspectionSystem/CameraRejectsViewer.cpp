// CameraRejectsViewer.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "CameraRejectsViewer.h"
#include "afxdialogex.h"


// CameraRejectsViewer dialog

IMPLEMENT_DYNAMIC(CameraRejectsViewer, CDialogEx)

CameraRejectsViewer::CameraRejectsViewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CAMERA_REJECTS_VIEWER, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
	isHWindowInitialized = false;
	selectedDefectData = NULL;
	majorBlobsList.clear();
	dominantBlobsList.clear();
	displayImage.Clear();
	isDisplayImageTrained = false;
}

CameraRejectsViewer::~CameraRejectsViewer()
{
	m_pEditBkBrush->DeleteObject();
	majorBlobsList.clear();
	dominantBlobsList.clear(); 
	displayImage.Clear();
	isDisplayImageTrained = false;
}

void CameraRejectsViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHEET_WINDOW, staticMainWindowHolder);
	DDX_Control(pDX, IDC_STATIC_ZOOM_WINDOW, staticZoomWindowHolder);
	DDX_Control(pDX, IDC_STATIC_DEFECT_VALUE, selectedDefectValue);
	DDX_Control(pDX, IDC_STATIC_DEFECT_SIZE, selectedDefectSize);
	DDX_Control(pDX, IDC_STATIC_VERTICAL_MEASUREMENT_RESULT, verticalMeasurementValue);
	DDX_Control(pDX, IDC_STATIC_HORIZONTAL_MEASUREMENT_RESULT, horizontalMeasurementValue);
	DDX_Control(pDX, IDC_STATIC_THREAD_INSPECTION_RESULT_VALUE, threadInspectionResult);
	DDX_Control(pDX, IDC_STATIC_DEFECT_PROPERTIES2, staticGroupSelectedDefectDetails);
	DDX_Control(pDX, IDC_STATIC_REGISTRATION_DETAILS, staticGroupRegistration);
	DDX_Control(pDX, IDC_STATIC_THREAD_DETAILS, staticGroupThreadDetection);
}


BOOL CameraRejectsViewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	staticMainWindowHolder.GetClientRect(&rect);
	mainWindow.OpenWindow(0, 0, rect.Width(), rect.Height(), (int)staticMainWindowHolder.m_hWnd, "visible", "");
	staticZoomWindowHolder.GetClientRect(&rect);
	zoomWindow.OpenWindow(0, 0, rect.Width(), rect.Height(), (int)staticZoomWindowHolder.m_hWnd, "visible", "");
	mainWindow.RegisterForHalconWindowEvents(this);
	isHWindowInitialized = true;
	selectedDefectSize.SetWindowTextW(_T("NA"));
	selectedDefectValue.SetWindowTextW(_T("NA"));
	verticalMeasurementValue.SetWindowTextW(_T("NA"));
	horizontalMeasurementValue.SetWindowTextW(_T("NA"));
	selectedDefectData = NULL;
	majorBlobsList.clear();
	dominantBlobsList.clear();
	displayImage.Clear();
	isDisplayImageTrained = false;

	SetWindowTheme(staticGroupRegistration, L"", L"");
	SetWindowTheme(staticGroupThreadDetection, L"", L"");
	SetWindowTheme(staticGroupSelectedDefectDetails, L"", L"");
	return true;
}


void CameraRejectsViewer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (isHWindowInitialized)
	{
		CRect rect;
		staticMainWindowHolder.GetClientRect(&rect);
		mainWindow.SetWindowExtents(0, 0, rect.Width(), rect.Height());
		staticZoomWindowHolder.GetClientRect(&rect);
		zoomWindow.SetWindowExtents(0, 0, rect.Width(), rect.Height());
		SetFocus();
		zoomWindow.ClearWindow();
		mainWindow.ClearWindow();
		UpdateDisplay();
	}
}

void CameraRejectsViewer::DisplayCameraResults(shared_ptr<CameraResultData>camResultData, bool isImageTrained, std::list<int> learnedMajorBlobsID, std::list<int> learnedDominantBlobsID)
{
	try
	{
		MeasurementResultData *tempMeasurementResultData = camResultData->GetMeasurementResults();
		if (tempMeasurementResultData != NULL && tempMeasurementResultData->verticleDiff.Length() > 0 && tempMeasurementResultData->horizontalDiff.Length() > 0)
		{

			double verticalMeasurement = (floor(tempMeasurementResultData->verticleDiff[0].D() * 100.0)) / 100.0;
			double horizontalMeasurement = (floor(tempMeasurementResultData->horizontalDiff[0].D() * 100.0)) / 100.0;
			CString verticalMeasurementString;
			verticalMeasurementString.Format(_T("%0.2f"), verticalMeasurement);
			CString horizontalMeasurementString;
			horizontalMeasurementString.Format(_T("%0.2f"), horizontalMeasurement);
			verticalMeasurementValue.SetWindowTextW(verticalMeasurementString);
			horizontalMeasurementValue.SetWindowTextW(horizontalMeasurementString);
		}
		else
		{
			verticalMeasurementValue.SetWindowTextW(_T("NA"));
			horizontalMeasurementValue.SetWindowTextW(_T("NA"));
		}
		ThreadResultData *tempThreadResultData = camResultData->GetThreadResults();
		if (tempThreadResultData != NULL)
		{
			CString resultStatus;
			switch (tempThreadResultData->result)
			{
			case Pass:
				resultStatus = _T("Pass");
				break;
			case Fail:
				resultStatus = _T("Fail");
				break;
			case Error:
				resultStatus = _T("Error");
				break;
			default:
				resultStatus = _T("NA");
				break;
			} 
			threadInspectionResult.SetWindowTextW(resultStatus);
		}
		else
		{
			threadInspectionResult.SetWindowTextW(_T("NA"));
		}
		selectedDefectData = NULL;
		displayImage.Clear();
		majorBlobsList.clear();
		dominantBlobsList.clear();
		isDisplayImageTrained = false;
		BlobAnalyzerResultData *tempBlobResultData = camResultData->GetBlobAnalysisResults();
		if (tempBlobResultData != NULL)
		{
			displayImage = camResultData->GetInspectionWindowImage();
			isDisplayImageTrained = isImageTrained;
			ParseAndStoreDefectData(tempBlobResultData->disconnectedMajorBlob, tempBlobResultData->disconnectedMajorBlobEnergy, MajorBlob, majorBlobsList, isImageTrained, learnedMajorBlobsID);
			ParseAndStoreDefectData(tempBlobResultData->dominantBlob, tempBlobResultData->dominantBlobEnergy, DominantBlob, dominantBlobsList, isImageTrained, learnedDominantBlobsID);
			if (majorBlobsList.size() > 0)
			{
				selectedDefectData = &majorBlobsList[0];
			}
			else if (dominantBlobsList.size() > 0)
			{
				selectedDefectData = &dominantBlobsList[0];
			}
		}
	}
	catch (HException &ex)
	{
		CString x;
		x.Format(_T("%S"), ex.ErrorMessage().Text());
		MessageBoxW(x);
	}
	catch (CException &ex)
	{
		MessageBoxW(_T("Error"));
	}
	UpdateDisplay();
}

void CameraRejectsViewer::ClearCameraResults()
{
	zoomWindow.ClearWindow();
	mainWindow.ClearWindow();
	selectedDefectData = NULL;
	displayImage.Clear();
	isDisplayImageTrained = false;
	majorBlobsList.clear();
	dominantBlobsList.clear();
}

void CameraRejectsViewer::ParseAndStoreDefectData(HRegion &defectRegion, HTuple &defectValue, DefectBlobType _defectType, std::vector<DefectData> &defectDataList, bool isImageTrained, std::list<int> addedBlobIDs)
{
	if (defectRegion.CountObj() > 0)
	{
		HRegion unionBlobRegion = defectRegion.Union1();
		HRegion joinedBlobRegion = unionBlobRegion.ClosingCircle(20.0);
		HRegion connectedBlobs = joinedBlobRegion.Connection();
		connectedBlobs = connectedBlobs.Intersection(unionBlobRegion);
		int connectedBlobsCount = connectedBlobs.CountObj();
		for (int blobIndex = 1; blobIndex <= connectedBlobsCount; blobIndex++)
		{
			try
			{
				HRegion tempDefectRegion = connectedBlobs.SelectObj(blobIndex);
				HRegion tempRegion = defectRegion.Intersection(tempDefectRegion);
				HTuple area = tempRegion.Area();
				area = area.TupleGreaterElem(0);
				area = area.TupleFind(1);
				if (area[0] != -1)
				{
					HTuple energy = defectValue.TupleSelect(area);
					energy = energy.TupleSum();
					DefectData tempDefectData;
					double energyValue = energy[0].D();
					bool isDefectLearned = std::find(addedBlobIDs.begin(), addedBlobIDs.end(), (blobIndex - 1)) != addedBlobIDs.end();
					tempDefectData.Set(tempDefectRegion, energyValue, blobIndex - 1, _defectType, isImageTrained || isDefectLearned);
					defectDataList.push_back(tempDefectData);
				}
			}
			catch (HException &ex)
			{
				CString x;
				x.Format(_T("%S, %d"), ex.ErrorMessage().Text(), blobIndex);
				MessageBoxW(x);
			}
		}
	}
}

void CameraRejectsViewer::UpdateDisplay()
{
	HSystem::SetSystem("flush_graphic", "false");
	UpdateMainWindowImage();
	UpdateMainWindowHighlightRegion();
	UpdateMainWindowDefectRegions();
	UpdateZoomWindow();
	HSystem::SetSystem("flush_graphic", "true");
}

void CameraRejectsViewer::UpdateMainWindowImage()
{
	mainWindow.ClearWindow();
	if (displayImage.IsInitialized())
	{
		mainWindow.AddImage(displayImage);
	}
}
void CameraRejectsViewer::UpdateMainWindowHighlightRegion()
{
	if (selectedDefectData != NULL)
	{
		mainWindow.AddHightlightRectangleRegion(selectedDefectData->highlightingRegion, 0, "green", (void *)HighlightingRegion);
		CString	selectedDefectSizeString, selectedDefectValueString;
		selectedDefectValueString.Format(_T("%.0f"), selectedDefectData->defectValue);
		selectedDefectSizeString.Format(_T("%.0f"), selectedDefectData->defectSize);
		selectedDefectSize.SetWindowTextW(selectedDefectSizeString);
		selectedDefectValue.SetWindowTextW(selectedDefectValueString);
	}
}


void CameraRejectsViewer::UpdateZoomWindow()
{
	zoomWindow.ClearWindow();
	if (selectedDefectData != NULL)
	{
		zoomWindow.AddImage(displayImage.ReduceDomain(selectedDefectData->highlightingRegion).CropDomain());
		zoomWindow.AddNonMovableRegion(selectedDefectData->zoomWindowRegion, 0, "magenta", (void *)HighlightingRegion);
		if (selectedDefectData->isTrained)
		{
			zoomWindow.SetTposition(10, 10);
			zoomWindow.SetColor("green");
			zoomWindow.WriteString("Defect Added");
		}
	}
}

void CameraRejectsViewer::UpdateMainWindowDefectRegions()
{
	int regionIndex = 0;
	for (auto &e : majorBlobsList)
	{
		mainWindow.AddNonMovableRegion(e.defectRegion, regionIndex, "blue", (void *)MajorBlob);
		regionIndex++;
	}
	regionIndex = 0;
	for (auto &e : dominantBlobsList)
	{
		mainWindow.AddNonMovableRegion(e.defectRegion, regionIndex, "red", (void *)DominantBlob);
		regionIndex++;
	}
}


BOOL CameraRejectsViewer::PreTranslateMessage(MSG* pMsg)
{
	CRect rect;
	staticMainWindowHolder.GetWindowRect(rect);
	POINT pt = pMsg->pt;

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

BEGIN_MESSAGE_MAP(CameraRejectsViewer, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MFCBUTTON_NAVIGATE_LEFT, &CameraRejectsViewer::OnBnClickedMfcbuttonNavigateLeft)
	ON_BN_CLICKED(IDC_MFCBUTTON_NAVIGATE_RIGHT, &CameraRejectsViewer::OnBnClickedMfcbuttonNavigateRight)
	ON_BN_CLICKED(IDC_MFCBUTTON_ADD_DEFECT, &CameraRejectsViewer::OnBnClickedMfcbuttonAddDefect)
	ON_BN_CLICKED(IDC_MFCBUTTON_ADD_ALL_DEFECT, &CameraRejectsViewer::OnBnClickedMfcbuttonAddAllDefect)
	ON_BN_CLICKED(IDC_MFCBUTTON_ADD_IMAGE, &CameraRejectsViewer::OnBnClickedMfcbuttonAddImage)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CameraRejectsViewer message handlers

void CameraRejectsViewer::OnRegionSelectedEvent(UINT regID, void *tag)
{	
	DefectBlobType defectBlobType = (DefectBlobType)(Hlong)tag;
	switch (defectBlobType)
	{
	case MajorBlob:
		selectedDefectData = &majorBlobsList[regID];
		break;
	case DominantBlob:
		selectedDefectData = &dominantBlobsList[regID];
		break;
	case HighlightingRegion:
		break;
	default:
		break;
	}
	UpdateDisplay();
}

void CameraRejectsViewer::OnRegionModifiedEvent(UINT regID, void *tag)
{
	
}

void CameraRejectsViewer::OnBnClickedMfcbuttonNavigateLeft()
{
	// TODO: Add your control notification handler code here
	if (selectedDefectData != NULL)
	{
		int defectRegID = selectedDefectData->defectID;
		DefectBlobType defectBlobType = selectedDefectData->defectBlobType;
		switch (defectBlobType)
		{
		case MajorBlob:
			if (defectRegID > 0 || dominantBlobsList.size() == 0)
			{
				defectRegID--;
				defectRegID = (defectRegID < 0) ? (majorBlobsList.size() - 1) : defectRegID;
				selectedDefectData = &majorBlobsList[defectRegID];
			}
			else
			{
				selectedDefectData = &dominantBlobsList[dominantBlobsList.size() - 1];
			}
			break;
		case DominantBlob:
			if (defectRegID > 0 || majorBlobsList.size() == 0)
			{
				defectRegID--;
				defectRegID = (defectRegID < 0) ? (dominantBlobsList.size() - 1) : defectRegID;
				selectedDefectData = &dominantBlobsList[defectRegID];
			}
			else
			{
				selectedDefectData = &majorBlobsList[majorBlobsList.size() - 1];
			}
			break;
		default:
			break;
		}
		UpdateDisplay();
	}
}


void CameraRejectsViewer::OnBnClickedMfcbuttonNavigateRight()
{
	// TODO: Add your control notification handler code here

	if (selectedDefectData != NULL)
	{
		int defectRegID = selectedDefectData->defectID;
		DefectBlobType defectBlobType = selectedDefectData->defectBlobType;
		switch (defectBlobType)
		{
		case MajorBlob:
			if (defectRegID < majorBlobsList.size() || dominantBlobsList.size() == 0)
			{
				defectRegID++;
				defectRegID = (defectRegID >= majorBlobsList.size()) ? 0 : defectRegID;
				selectedDefectData = &majorBlobsList[defectRegID];
			}
			else
			{
				selectedDefectData = &dominantBlobsList[0];
			}
			break;
		case DominantBlob:
			if (defectRegID < dominantBlobsList.size() || majorBlobsList.size() == 0)
			{
				defectRegID++;
				defectRegID = (defectRegID >= dominantBlobsList.size()) ? (0) : defectRegID;
				selectedDefectData = &dominantBlobsList[defectRegID];
			}
			else
			{
				selectedDefectData = &majorBlobsList[0];
			}
			break;
		default:
			break;
		}
		UpdateDisplay();
	}
}


void CameraRejectsViewer::OnBnClickedMfcbuttonAddDefect()
{
	// TODO: Add your control notification handler code here
	if (selectedDefectData != NULL)
	{
		if (!selectedDefectData->isTrained)
		{
			GetParent()->PostMessageW(UWM_SEND_LEARN_DEFECT, (WPARAM)selectedDefectData, (LPARAM)(selectedDefectData->defectBlobType == MajorBlob) ? LearnMajorBlob : LearnDominantBlob);
			selectedDefectData->isTrained = true;
			UpdateDisplay();
			MessageBoxA(this->GetSafeHwnd(), "Defect is added to Extension List", "OptiCheck - Intaglio Inspection", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
		}
		else
		{
			MessageBoxA(this->GetSafeHwnd(), "Defect is already added to Extension List!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
		}
	}
	else
	{
		MessageBoxA(this->GetSafeHwnd(), "No Defect is available to add!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
}


void CameraRejectsViewer::OnBnClickedMfcbuttonAddAllDefect()
{
	// TODO: Add your control notification handler code here
	int count = majorBlobsList.size() + dominantBlobsList.size();
	if (count)
	{
		bool isAdded = false;
		for (auto &e : majorBlobsList)
		{
			if (!e.isTrained)
			{
				GetParent()->PostMessageW(UWM_SEND_LEARN_DEFECT, (WPARAM)&e, (LPARAM)LearnMajorBlob);
				e.isTrained = true;
				isAdded |= true;
			}
		}

		for (auto &e : dominantBlobsList)
		{
			if (!e.isTrained)
			{
				GetParent()->PostMessageW(UWM_SEND_LEARN_DEFECT, (WPARAM)&e, (LPARAM)LearnDominantBlob);
				e.isTrained = true;
				isAdded |= true;
			}
		}
		UpdateDisplay();
		if (isAdded)
		{
			MessageBoxA(this->GetSafeHwnd(), "All the Defects are added to Extension List", "OptiCheck - Intaglio Inspection", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
		}
		else
		{
			MessageBoxA(this->GetSafeHwnd(), "All the Defects are already added to Extension List!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
		}
	}
	else
	{
		MessageBoxA(this->GetSafeHwnd(), "No Defect is available to add!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
}


void CameraRejectsViewer::OnBnClickedMfcbuttonAddImage()
{
	// TODO: Add your control notification handler code here

	if (displayImage.IsInitialized())
	{
		if (!isDisplayImageTrained)
		{
			GetParent()->PostMessageW(UWM_SEND_LEARN_DEFECT, NULL, (LPARAM)LearnCompleteImage);
			isDisplayImageTrained = true;
			for (auto &e : majorBlobsList)
			{
				if (!e.isTrained)
				{
					e.isTrained = true;
				}
			}
			for (auto &e : dominantBlobsList)
			{
				if (!e.isTrained)
				{
					e.isTrained = true;
				}
			}
			MessageBoxA(this->GetSafeHwnd(), "Complete Image is added to Extension List", "OptiCheck - Intaglio Inspection", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
		}
		else
		{
			MessageBoxA(this->GetSafeHwnd(), "Complete Image is already added to Extension List!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
		}
	}
	else
	{
		MessageBoxA(this->GetSafeHwnd(), "No Image is available to add!", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_OK | MB_TOPMOST);
	}
}


BOOL CameraRejectsViewer::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CameraRejectsViewer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
