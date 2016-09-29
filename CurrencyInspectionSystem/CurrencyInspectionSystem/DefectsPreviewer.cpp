// DefectsPreviewer.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "DefectsPreviewer.h"
#include "afxdialogex.h"


// DefectsPreviewer dialog

IMPLEMENT_DYNAMIC(DefectsPreviewer, CDialogEx)

DefectsPreviewer::DefectsPreviewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DEFECTS_PREVIEWER, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
	extendedTrainingDataList = NULL;
}

DefectsPreviewer::~DefectsPreviewer()
{
	m_pEditBkBrush->DeleteObject();
}

void DefectsPreviewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MAIN_WINDOW_HOLDER, staticMainWindowHolder);
	DDX_Control(pDX, IDC_MFCBUTTON_LEFT_SHIFT, buttonPrevious);
	DDX_Control(pDX, IDC_MFCBUTTON_RIGHT_SHIFT, buttonNext);
	DDX_Control(pDX, IDC_MFCBUTTON_REMOVE_DEFECT, buttonRemove);
	DDX_Control(pDX, IDC_STATIC_DEFECT_COUNT_INDICATOR, staticDefectIndexStatus);
	DDX_Control(pDX, IDC_STATIC_IMAGE_NUMBER_VALUE, staticImageNumberStatus);
	DDX_Control(pDX, IDC_STATIC_CAMERA_ID_VALUE, staticCameraIDStatus);
	DDX_Control(pDX, IDC_STATIC_DEFECT_VALUE_VALUE, staticDefectValueStatus);
	DDX_Control(pDX, IDC_STATIC_DEFECT_SIZE_VALUE, staticDefectSizeStatus);
	DDX_Control(pDX, IDC_STATIC_TITLE, staticLearnPreview);
	DDX_Control(pDX, IDC_STATIC_GROUP_DEFCT_DETAILS, staticGroupDefectDetails);
	DDX_Control(pDX, IDC_MFCBUTTON_OK, buttonClose);
}


BEGIN_MESSAGE_MAP(DefectsPreviewer, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_LEFT_SHIFT, &DefectsPreviewer::OnBnClickedMfcbuttonLeftShift)
	ON_BN_CLICKED(IDC_MFCBUTTON_RIGHT_SHIFT, &DefectsPreviewer::OnBnClickedMfcbuttonRightShift)
	ON_BN_CLICKED(IDC_MFCBUTTON_OK, &DefectsPreviewer::OnBnClickedMfcbuttonOk)
	ON_BN_CLICKED(IDC_MFCBUTTON_REMOVE_DEFECT, &DefectsPreviewer::OnBnClickedMfcbuttonRemoveDefect)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DefectsPreviewer message handlers

BOOL DefectsPreviewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	staticMainWindowHolder.GetClientRect(&rect);
	mainWindow.OpenWindow(0, 0, rect.Width(), rect.Height(), (int)staticMainWindowHolder.m_hWnd, "visible", "");
	if (extendedTrainingDataList != NULL && extendedTrainingDataList->size() > 0)
	{	
		imgIndex = 0;
		defectIndex = 0;
		UpdateDisplay();
	}
	else
	{
		buttonNext.EnableWindow(FALSE);
		buttonPrevious.EnableWindow(FALSE);
		buttonRemove.EnableWindow(FALSE);
	}
	

	font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_ROMAN, _T("MS Serif"));
	staticLearnPreview.SetFont(&font);

	SetWindowTheme(staticGroupDefectDetails, L"", L"");
	return true;
}

BOOL DefectsPreviewer::PreTranslateMessage(MSG* pMsg)
{
	//CRect rect;
	//staticMainWindowHolder.GetWindowRect(rect);
	//POINT pt = pMsg->pt;

	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		bRet = TRUE; // do not dispatch message
	}
	//else if (rect.PtInRect(pt))
	//{
	//	mainWindow.eventhandler(pMsg);
	//	bRet = TRUE; // do not dispatch message
	//	SetFocus();
	//	bRet = CDialogEx::PreTranslateMessage(pMsg);
	//}
	else
	{
		bRet = CDialogEx::PreTranslateMessage(pMsg);
	}
	return bRet;
}

void DefectsPreviewer::SetTrainingDataList(std::map<ULONG, ExtendedTrainingData> &_extendedTrainingDataList)
{
	extendedTrainingDataList = &_extendedTrainingDataList;
	tolalLearningsCount = 0;
	currentLeariningIndex = 0;
	for (auto &e : *extendedTrainingDataList)
	{
		tolalLearningsCount += e.second.GetTotalLearningsCount();
	}
	if (tolalLearningsCount)
	{
		currentLeariningIndex = 1;
	}
}


void DefectsPreviewer::UpdateDisplay()
{
	UpdateUI();
	HSystem::SetSystem("flush_graphic", "false");
	mainWindow.ClearWindow();
	CString temp;
	if (extendedTrainingDataList->size() > 0)
	{
		std::map<ULONG, ExtendedTrainingData>::iterator iter = extendedTrainingDataList->begin();
		std::advance(iter, imgIndex);
		LearningType learningType;
		int cameraID;
		HImage displayImage = iter->second.GetDisplayDetails(defectIndex, defectRegion, defectValue, defectSize, learningType, cameraID);
		mainWindow.AddImage(displayImage);
		mainWindow.AddNonEditableRegion(defectRegion, defectIndex, "red", NULL);
		if (defectValue >= 0)
		{
			temp.Format(_T("%.0f"), defectValue);
		}
		else
		{
			temp = _T("NA");
		}
		staticDefectValueStatus.SetWindowTextW(temp);
		if (defectSize >= 0)
		{
			temp.Format(_T("%.0f"), defectSize);
		}
		else
		{
			temp = _T("NA");
		}
		staticDefectSizeStatus.SetWindowTextW(temp);
		temp.Format(_T("%d"), iter->first);
		staticImageNumberStatus.SetWindowTextW(temp);
		temp.Format(_T("%d"), cameraID);
		staticCameraIDStatus.SetWindowTextW(temp);
		mainWindow.SetTposition(10, 10);
		mainWindow.SetColor("green");
		switch (learningType)
		{
		case LearnMajorBlob:
			mainWindow.WriteString("Major Defect");
			break;
		case LearnDominantBlob:
			mainWindow.WriteString("Dominant Defect");
			break;
		case LearnCompleteImage:
			mainWindow.WriteString("Complete Image");
			break;
		default:
			break;
		}
	}
	else
	{

		temp = _T("NA");
		staticDefectValueStatus.SetWindowTextW(temp);
		staticDefectSizeStatus.SetWindowTextW(temp);
		staticImageNumberStatus.SetWindowTextW(temp);
		staticCameraIDStatus.SetWindowTextW(temp);
	}
	HSystem::SetSystem("flush_graphic", "true");
}


void DefectsPreviewer::UpdateUI()
{
	buttonPrevious.EnableWindow(TRUE);
	buttonNext.EnableWindow(TRUE);
	buttonRemove.EnableWindow(TRUE);
	if (!extendedTrainingDataList->size())
	{
		buttonPrevious.EnableWindow(FALSE);
		buttonNext.EnableWindow(FALSE);
		buttonRemove.EnableWindow(FALSE);
	}
	else if (imgIndex == 0 & defectIndex == 0)
	{
		buttonPrevious.EnableWindow(FALSE);
	}
	else if (imgIndex >= extendedTrainingDataList->size() - 1 &&
		defectIndex >= (extendedTrainingDataList->rbegin()->second.GetTotalLearningsCount() - 1))
	{
		buttonNext.EnableWindow(FALSE);
	}
	CString defectPositionStatus;
	defectPositionStatus.Format(_T("%d of %d"), currentLeariningIndex, tolalLearningsCount);
	staticDefectIndexStatus.SetWindowTextW(defectPositionStatus);
}

void DefectsPreviewer::OnBnClickedMfcbuttonLeftShift()
{
	// TODO: Add your control notification handler code here
	
	if (defectIndex > 0)
	{
		defectIndex--;
		currentLeariningIndex--;
	}
	else if (imgIndex > 0)
	{
		imgIndex--;
		std::map<ULONG, ExtendedTrainingData>::iterator iter = extendedTrainingDataList->begin();
		std::advance(iter, imgIndex);
		defectIndex = iter->second.GetTotalLearningsCount() - 1;
		currentLeariningIndex--;
	}
	UpdateDisplay();
}


void DefectsPreviewer::OnBnClickedMfcbuttonRightShift()
{
	// TODO: Add your control notification handler code here

	std::map<ULONG, ExtendedTrainingData>::iterator iter = extendedTrainingDataList->begin();
	std::advance(iter, imgIndex);

	if (defectIndex < iter->second.GetTotalLearningsCount() - 1)
	{
		defectIndex++;
		currentLeariningIndex++;
	}
	else if (imgIndex < extendedTrainingDataList->size() - 1)
	{
		imgIndex++;
		defectIndex = 0;
		currentLeariningIndex++;
	}
	UpdateDisplay();
}


void DefectsPreviewer::OnBnClickedMfcbuttonOk()
{
	// TODO: Add your control notification handler code here
	extendedTrainingDataList = NULL;
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


void DefectsPreviewer::OnBnClickedMfcbuttonRemoveDefect()
{
	// TODO: Add your control notification handler code here
	std::map<ULONG, ExtendedTrainingData>::iterator iter = extendedTrainingDataList->begin();
	std::advance(iter, imgIndex);
	iter->second.RemoveTrainingData(defectIndex);
	if (!iter->second.GetTotalLearningsCount())
	{
		GetParent()->PostMessageW(UWM_CHANGE_IMAGE_TRAININGSTATUS, iter->first, NotTrained);
		extendedTrainingDataList->erase(iter);
		if (imgIndex >= extendedTrainingDataList->size())
		{
			imgIndex = extendedTrainingDataList->size() - 1;
		}		
		defectIndex = 0;
	}
	else
	{
		GetParent()->PostMessageW(UWM_CHANGE_IMAGE_TRAININGSTATUS, iter->first, iter->second.GetTrainingStatus());
		defectIndex++;
		if (defectIndex >= iter->second.GetTotalLearningsCount())
		{
			defectIndex = iter->second.GetTotalLearningsCount() - 1;
		}
	}
	tolalLearningsCount--;
	if (currentLeariningIndex > tolalLearningsCount)
	{
		currentLeariningIndex = tolalLearningsCount;
	}
	UpdateDisplay();
}


BOOL DefectsPreviewer::OnEraseBkgnd(CDC* pDC)
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


HBRUSH DefectsPreviewer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
