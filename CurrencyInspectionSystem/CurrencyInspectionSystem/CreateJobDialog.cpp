// CreateJobDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "CreateJobDialog.h"
#include "afxdialogex.h"
#include "ApplicationSettingsReader.h"


// CreateJobDialog dialog

IMPLEMENT_DYNAMIC(CreateJobDialog, CDialogEx)

CreateJobDialog::CreateJobDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CREATEJOB, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
}

CreateJobDialog::~CreateJobDialog()
{
	m_pEditBkBrush->DeleteObject();
}

void CreateJobDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, buttonClose);
	DDX_Control(pDX, IDC_MFCBUTTON_OKAY, buttonOkay);
	DDX_Control(pDX, IDC_COMBO_GOLDEN_LIST, comboBoxGoldenList);
	DDX_Control(pDX, IDC_COMBO_SHIFT_LIST, comboBoxShiftID);
	DDX_Control(pDX, IDC_STATIC_NEW_GOLDEN, staticShiftDetails);
}


BEGIN_MESSAGE_MAP(CreateJobDialog, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &CreateJobDialog::OnBnClickedMfcbuttonClose)
	ON_BN_CLICKED(IDC_MFCBUTTON_OKAY, &CreateJobDialog::OnBnClickedMfcbuttonOkay)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CreateJobDialog::OnInitDialog()
{
	BOOL returnValue = CDialogEx::OnInitDialog();
	comboBoxGoldenList.ResetContent();
	for (auto &e: goldenList)
	{
		comboBoxGoldenList.AddString(CString(e.c_str()));
	}
	comboBoxGoldenList.SetCurSel(0);
	
	comboBoxShiftID.ResetContent();
	shiftList = ApplicationSettingsReader::GetInstance()->shifConfig;
	for (auto &e: shiftList)
	{
		comboBoxShiftID.AddString(CString(e.shiftName.c_str()));
	}
	comboBoxShiftID.SetCurSel(0);

	font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_ROMAN, _T("MS Serif"));
	
	staticShiftDetails.SetFont(&font);
	return returnValue;
}

void CreateJobDialog::OnBnClickedMfcbuttonClose()
{
	// TODO: Add your control notification handler code here
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}

void CreateJobDialog::OnBnClickedMfcbuttonOkay()
{
	// TODO: Add your control notification handler code here

	if (goldenList.size() > 0)
	{
		CString selectedGoldenName;
		comboBoxGoldenList.GetLBText(comboBoxGoldenList.GetCurSel(), selectedGoldenName);
		ShiftData *shiftData = new ShiftData(comboBoxShiftID.GetCurSel(),shiftList[comboBoxShiftID.GetCurSel()].shiftName, (std::string) (CW2A(selectedGoldenName)),
			shiftList[comboBoxShiftID.GetCurSel()].shiftStartHour, shiftList[comboBoxShiftID.GetCurSel()].totalShiftHours, shiftList[comboBoxShiftID.GetCurSel()].perHourTarget);
		GetParent()->PostMessageW(UWM_START_SHIFT_RECEIVED, (WPARAM)shiftData, NULL);
	}
	else
	{
		MessageBoxA(this->GetSafeHwnd(), "There is no Golden available!!", "OptiCheck - Intaglio Inspection", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}
	this->PostMessageW(WM_CLOSE, NULL, NULL);
	this->CloseWindow();
}

void CreateJobDialog::ConfigureDialog(std::vector<std::string> &_goldenList)
{
	goldenList = _goldenList;
}


BOOL CreateJobDialog::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedMfcbuttonOkay();
		bRet = TRUE; // do not dispatch message
	}
	else
	{
		bRet = CDialog::PreTranslateMessage(pMsg);
	}
	return bRet;
}



BOOL CreateJobDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CreateJobDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
