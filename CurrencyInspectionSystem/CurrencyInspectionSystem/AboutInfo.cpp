// AboutInfo.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "AboutInfo.h"
#include "afxdialogex.h"
#include "version.h"
#include "Globals.h"

// AboutInfo dialog

IMPLEMENT_DYNAMIC(AboutInfo, CDialogEx)

AboutInfo::AboutInfo(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUT_DIALOG, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
}

AboutInfo::~AboutInfo()
{
	m_pEditBkBrush->DeleteObject();
}

void AboutInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutInfo, CDialog)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()

//	ON_WM_THEMECHANGED()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// AboutInfo message handlers

BOOL AboutInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowText(_T("About Us - Lucid Imaging"));
	((CWnd*)GetDlgItem(IDC_DEVELOPED_BY))->SetWindowText(_T("Lucid Imaging Pvt. Ltd, India"));
	((CWnd*)GetDlgItem(IDC_COPYRIGHT))->SetWindowText(_T(VER_COPYRIGHT_STR));
	((CWnd*)GetDlgItem(IDC_VERSIONDISPLAY))->SetWindowText(_T(VER_FILE_VERSION_STR));
	return TRUE;

}





BOOL AboutInfo::OnEraseBkgnd(CDC* pDC)
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


HBRUSH AboutInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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



