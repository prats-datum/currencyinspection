// EditDeleteGoldenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "EditDeleteGoldenDialog.h"
#include "afxdialogex.h"


// EditDeleteGoldenDialog dialog

IMPLEMENT_DYNAMIC(EditDeleteGoldenDialog, CDialogEx)

EditDeleteGoldenDialog::EditDeleteGoldenDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EDIT_GOLDEN, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);

}

EditDeleteGoldenDialog::~EditDeleteGoldenDialog()
{
	m_pEditBkBrush->DeleteObject();
}

void EditDeleteGoldenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NEW_GOLDEN, staticTitle);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, buttonClose);
	DDX_Control(pDX, IDC_MFCBUTTON_OKAY, buttonOkay);
	DDX_Control(pDX, IDC_COMBO_GOLDEN_LIST, comboBoxGoldenList);
}

BEGIN_MESSAGE_MAP(EditDeleteGoldenDialog, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &EditDeleteGoldenDialog::OnBnClickedMfcbuttonClose)
	ON_BN_CLICKED(IDC_MFCBUTTON_OKAY, &EditDeleteGoldenDialog::OnBnClickedMfcbuttonOkay)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL EditDeleteGoldenDialog::OnInitDialog()
{
	BOOL returnValue = CDialogEx::OnInitDialog();
	CString title;
	CString buttonName;
	UINT iconID;
	if (modifyOperation == GoldenModifyOperation::Edit)
	{
		title = _T("Edit Golden");
		buttonName = _T("OK");
		iconID = IDI_ICON_CHECKED;
	}
	else
	{
		title = _T("Delete Golden");
		buttonName = _T("Delete");
		iconID = IDI_ICON_UNCHECKED;
	}
	staticTitle.SetWindowTextW(title);
	buttonOkay.SetWindowTextW(buttonName);
	buttonOkay.SetIcon(AfxGetApp()->LoadIconW(iconID));
	for (auto &e :goldenList)
	{
		comboBoxGoldenList.AddString(CString(e.c_str()));
	}
	comboBoxGoldenList.SetCurSel(0);

	font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_ROMAN, _T("MS Serif"));
	staticTitle.SetFont(&font);
	return returnValue;
}

void EditDeleteGoldenDialog::OnBnClickedMfcbuttonClose()
{
	// TODO: Add your control notification handler code here
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


void EditDeleteGoldenDialog::OnBnClickedMfcbuttonOkay()
{
	// TODO: Add your control notification handler code here	
	if (goldenList.size() > 0)
	{
		if (modifyOperation == GoldenModifyOperation::Edit)
		{
			this->PostMessageW(WM_CLOSE, NULL, NULL);
			GetParent()->PostMessageW(UWM_MODIFY_GOLDEN_RECEIVED, (WPARAM)modifyOperation, (LPARAM)comboBoxGoldenList.GetCurSel());
			this->CloseWindow();
		}
		else
		{
			if (IDYES == MessageBoxA(this->GetSafeHwnd(), "Are you sure you want to delete the selected Golden?", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_YESNO | MB_TOPMOST))
			{
				GetParent()->PostMessageW(UWM_MODIFY_GOLDEN_RECEIVED, (WPARAM)modifyOperation, (LPARAM)comboBoxGoldenList.GetCurSel());
				int selectedIndex = comboBoxGoldenList.GetCurSel();
				goldenList.erase(goldenList.begin()+selectedIndex);
				comboBoxGoldenList.DeleteString(selectedIndex);
				comboBoxGoldenList.SetCurSel(0);
			}

		}
	}
	else
	{
		MessageBoxA(this->GetSafeHwnd(), "There is no Golden available!!", "OptiCheck - Intaglio Inspection", MB_ICONERROR | MB_OK | MB_TOPMOST);
		this->PostMessageW(WM_CLOSE, NULL, NULL);
		this->CloseWindow();
	}
}


void EditDeleteGoldenDialog::ConfigureDialog(std::vector<std::string> &_goldenList, GoldenModifyOperation _modifyOperation)
{
	modifyOperation = _modifyOperation;
	goldenList = _goldenList;
}

BOOL EditDeleteGoldenDialog::PreTranslateMessage(MSG* pMsg)
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



// EditDeleteGoldenDialog message handlers


BOOL EditDeleteGoldenDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH EditDeleteGoldenDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
