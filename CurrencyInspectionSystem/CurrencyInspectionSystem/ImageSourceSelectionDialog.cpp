// ImageSourceSelectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "ImageSourceSelectionDialog.h"
#include "afxdialogex.h"
#include "ImageSourceSettingsReader.h"


// ImageSourceSelectionDialog dialog

IMPLEMENT_DYNAMIC(ImageSourceSelectionDialog, CDialogEx)

ImageSourceSelectionDialog::ImageSourceSelectionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_SOURCE_SETTINGS, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
	isTabCtrlInitialized = false;
}

ImageSourceSelectionDialog::~ImageSourceSelectionDialog()
{
	m_pEditBkBrush->DeleteObject();
	for (auto &e : imageSourceDlgList)
	{
		delete e;
	}
	imageSourceDlgList.clear();
}

void ImageSourceSelectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CAMERA, tabCtrlCamera);
	DDX_Control(pDX, IDC_STATIC_IMAGE_SOURCE_WINDoW, staticImageSourceWindow);
	DDX_Control(pDX, IDC_MFCBUTTON_OKAY_IS, buttonOkay);
	DDX_Control(pDX, IDC_MFCBUTTON_CANCEL_IS, buttonCancel);
	DDX_Control(pDX, IDC_STATIC_TITLE, staticImageSourceSelection);
}

BOOL ImageSourceSelectionDialog::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		bRet = TRUE; // do not dispatch message
	}
	else
	{
		bRet = CDialog::PreTranslateMessage(pMsg);
	}
	return bRet;
}

BOOL ImageSourceSelectionDialog::OnInitDialog()
{
	TC_ITEM tci;
	CString strCaption;

	BOOL returnValue = CDialogEx::OnInitDialog();

	for (auto &e : imageSourceDlgList)
	{
		delete e;
	}
	imageSourceDlgList.clear();

	for (auto &e : ImageSourceSettingsReader::GetReader()->imageSourceSettingsList)
	{
		ImageSourceDialog *temp = new ImageSourceDialog();
		temp->ConfigureDialog(e.second);
		temp->Create(IDD_DIALOG_IMAGE_SOURCE, this);
		imageSourceDlgList.push_back(temp);

		tci.mask = TCIF_TEXT;
		strCaption = CString(e.second.cameraName.c_str());
		tci.pszText = strCaption.GetBuffer();
		tci.cchTextMax = strCaption.GetLength();
		tabCtrlCamera.InsertItem(0, &tci);
	}
	isTabCtrlInitialized = true;

	font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_ROMAN, _T("MS Serif"));
	staticImageSourceSelection.SetFont(&font);
	return returnValue;
}

void ImageSourceSelectionDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	CRect r;
	CDialog *p;
	p = imageSourceDlgList[0];
	staticImageSourceWindow.GetWindowRect(r);
	ScreenToClient(r);
	p->SetWindowPos(&CWnd::wndBottom, r.left + 1, r.top + 1, r.Width() - 2, r.Height() - 2, SWP_SHOWWINDOW);
	p->ShowWindow(SW_SHOW);
	//tabCtrlCamera.SetDefaultPane(0);
}

void ImageSourceSelectionDialog::OnMove(int x, int y)
{
	if (isTabCtrlInitialized)
	{
		int iTab = tabCtrlCamera.GetCurSel();
		CRect r;
		CDialog *p;
		p = imageSourceDlgList[iTab];
		staticImageSourceWindow.GetClientRect(r);
		p->SetWindowPos(&CWnd::wndBottom, r.left + 1, r.top + 1, r.Width() - 2, r.Height() - 2, SWP_SHOWWINDOW);
		p->ShowWindow(SW_SHOW);
	}
	//tabCtrlCamera.OnMove(x, y);
}

BEGIN_MESSAGE_MAP(ImageSourceSelectionDialog, CDialogEx)
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CLICK, IDC_TAB_CAMERA, &ImageSourceSelectionDialog::OnNMClickTabCamera)
	ON_BN_CLICKED(IDC_MFCBUTTON_OKAY_IS, &ImageSourceSelectionDialog::OnBnClickedMfcbuttonOkayIs)
	ON_BN_CLICKED(IDC_MFCBUTTON_CANCEL_IS, &ImageSourceSelectionDialog::OnBnClickedMfcbuttonCancelIs)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ImageSourceSelectionDialog message handlers




void ImageSourceSelectionDialog::OnNMClickTabCamera(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect r;
	int iTab = tabCtrlCamera.GetCurSel();
	CDialog *p;
	for (auto &e : imageSourceDlgList)
	{
		e->ShowWindow(SW_HIDE);
	}
	p = imageSourceDlgList[iTab];
	staticImageSourceWindow.GetWindowRect(r);
	ScreenToClient(r);
	p->SetWindowPos(&CWnd::wndBottom, r.left + 1, r.top + 1, r.Width() - 2, r.Height() - 2, SWP_SHOWWINDOW);
	p->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void ImageSourceSelectionDialog::OnBnClickedMfcbuttonOkayIs()
{
	// TODO: Add your control notification handler code here
	if (IsSettingsModified() && IDYES == MessageBoxA(this->GetSafeHwnd(), "Do you want to Save the changes?", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_YESNO | MB_TOPMOST))
	{
		int index = 1;
		for (auto &e : imageSourceDlgList)
		{
			ImageSourceSettingsReader::GetReader()->imageSourceSettingsList[index] = e->imgSourceSettings;
			index++;
		}
		ImageSourceSettingsReader::GetReader()->WriteConfiguration();
	}
	for (auto &e : imageSourceDlgList)
	{
		delete e;
	}
	imageSourceDlgList.clear();
	isTabCtrlInitialized = false;
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


void ImageSourceSelectionDialog::OnBnClickedMfcbuttonCancelIs()
{
	// TODO: Add your control notification handler code here
	if (IsSettingsModified() && IDNO == MessageBoxA(this->GetSafeHwnd(), "Do you want to Discard the changes?", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_YESNO | MB_TOPMOST))
	{
		return;
	}
	for (auto &e : imageSourceDlgList)
	{
		delete e;
	}
	imageSourceDlgList.clear();
	isTabCtrlInitialized = false;
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


bool ImageSourceSelectionDialog::IsSettingsModified()
{
	bool isModified = false;
	for (auto &e : imageSourceDlgList)
	{
		isModified |= e->isModified;
	}
	return isModified;
}



BOOL ImageSourceSelectionDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH ImageSourceSelectionDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
