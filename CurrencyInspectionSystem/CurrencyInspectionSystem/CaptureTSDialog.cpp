// CaptureTSDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "CaptureTSDialog.h"
#include "afxdialogex.h"


// CaptureTSDialog dialog

IMPLEMENT_DYNAMIC(CaptureTSDialog, CDialogEx)

CaptureTSDialog::CaptureTSDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CAPTURE_TRAINING_SET, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
}

CaptureTSDialog::~CaptureTSDialog()
{
	m_pEditBkBrush->DeleteObject();
}


void CaptureTSDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NO_OF_IMAGES, editNoOfImagesToCapture);
	DDX_Control(pDX, IDC_MFCBUTTON_START, buttonStartCapturing);
	DDX_Control(pDX, IDC_MFCBUTTON_STOP, buttonStopCapturing);
	DDX_Control(pDX, IDC_STATIC_CAPTURE_STATUS, staticCaptureStatus);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, buttonClose);
}


BOOL CaptureTSDialog::OnInitDialog()
{
	BOOL returnValue = CDialogEx::OnInitDialog();
	editNoOfImagesToCapture.SetWindowTextW(_T("30"));
	buttonStopCapturing.EnableWindow(FALSE);
	staticCaptureStatus.SetWindowTextW(_T(""));
	isGrabbingStarted = false;
	return returnValue;
}

BOOL CaptureTSDialog::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (isGrabbingStarted)
		{
			OnBnClickedMfcbuttonStop();
		}
		else
		{
			OnBnClickedMfcbuttonStart();
		}
		bRet = TRUE; // do not dispatch message
	}
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		bRet = TRUE; // do not dispatch message
	}
	else
	{
		bRet = CDialog::PreTranslateMessage(pMsg);
	}
	return bRet;
}


BEGIN_MESSAGE_MAP(CaptureTSDialog, CDialogEx)
	ON_MESSAGE(UWM_TS_CAPTURE_STATUS, &CaptureTSDialog::OnImageCaptureStatusReceived)
	ON_MESSAGE(UWM_TS_CAPTURE_FAILURE, &CaptureTSDialog::OnImageCaptureFailureStatusReceived)

	ON_BN_CLICKED(IDC_MFCBUTTON_START, &CaptureTSDialog::OnBnClickedMfcbuttonStart)
	ON_BN_CLICKED(IDC_MFCBUTTON_STOP, &CaptureTSDialog::OnBnClickedMfcbuttonStop)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &CaptureTSDialog::OnBnClickedMfcbuttonClose)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CaptureTSDialog message handlers


void CaptureTSDialog::OnBnClickedMfcbuttonStart()
{
	// TODO: Add your control notification handler code here
	CString tsCountString;
	editNoOfImagesToCapture.GetWindowTextW(tsCountString);
	if (tsCountString != _T(""))
	{
		int tsCount = _wtoi(tsCountString);
		if (tsCount != 0)
		{
			GetParent()->PostMessageW(UWM_START_CAPTURE_TS, (WPARAM)tsCount, NULL);
			editNoOfImagesToCapture.EnableWindow(FALSE);
			buttonStartCapturing.EnableWindow(FALSE);
			buttonStopCapturing.EnableWindow(TRUE);
			buttonClose.EnableWindow(FALSE);
			isGrabbingStarted = true;
			return;
		}
	}
	AfxMessageBox(_T("Please enter the no. Of training Set images to capture"));
}


void CaptureTSDialog::OnBnClickedMfcbuttonStop()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessageW(UWM_STOP_CAPTURE_TS, NULL, NULL);
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


LRESULT CaptureTSDialog::OnImageCaptureStatusReceived(WPARAM wParam, LPARAM lParam)
{
	int noOfImagesCaptured = (int)wParam;

	CString tsCountString;
	editNoOfImagesToCapture.GetWindowTextW(tsCountString);
	int tsCount = _wtoi(tsCountString);

	CString status;
	status.Format(_T("Capturing %d of %d images.."), noOfImagesCaptured, tsCount);
	staticCaptureStatus.SetWindowTextW(status);
	if (noOfImagesCaptured == tsCount)
	{
		Sleep(500);
		this->PostMessageW(WM_CLOSE, NULL, NULL);
	}
	return 1;
}


LRESULT CaptureTSDialog::OnImageCaptureFailureStatusReceived(WPARAM wParam, LPARAM lParam)
{
	CString status;
	status.Format(_T("Error: Failed To Capture Training Set..!"));
	staticCaptureStatus.SetWindowTextW(status);
	return 1;
}


int CaptureTSDialog::GetNoOfImagesToGrabCount()
{
	int tsCount = 0;
	CString tsCountString;
	editNoOfImagesToCapture.GetWindowTextW(tsCountString);
	if (tsCountString != _T(""))
	{
		tsCount = _wtoi(tsCountString);
	}
	return tsCount;
}

void CaptureTSDialog::OnBnClickedMfcbuttonClose()
{
	// TODO: Add your control notification handler code here
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


BOOL CaptureTSDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CaptureTSDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
