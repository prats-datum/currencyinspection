// ImageSourceDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "ImageSourceDialog.h"
#include "afxdialogex.h"



// ImageSourceDialog dialog

IMPLEMENT_DYNAMIC(ImageSourceDialog, CDialogEx)

ImageSourceDialog::ImageSourceDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_SOURCE, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);

}

ImageSourceDialog::~ImageSourceDialog()
{
	m_pEditBkBrush->DeleteObject();
}

BOOL ImageSourceDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	groupBoxCamera.SetTitleStyle(BS_AUTORADIOBUTTON);
	groupBoxFile.SetTitleStyle(BS_AUTORADIOBUTTON);
	groupBoxCamera.SetGroupID(1);
	groupBoxFile.SetGroupID(1);
	
	groupBoxFile.SetCheck(imgSourceSettings.imageSourceType == ImageSourceType::File);
	groupBoxCamera.SetCheck(imgSourceSettings.imageSourceType == ImageSourceType::Camera);
	editImageFilesPath.SetWindowTextW(CString(imgSourceSettings.imageFilesPath.c_str()));
	editConfigurationFilesPath.SetWindowTextW(CString(imgSourceSettings.configFilePath.c_str()));
	isModified = false;

	SetWindowTheme(groupBoxCamera, L"", L"");
	SetWindowTheme(groupBoxFile, L"", L"");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ImageSourceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_FILE_GROUBBOX, groupBoxFile);
	DDX_Control(pDX, IDC_STATIC_CAMERA_GROUPBOX, groupBoxCamera);
	DDX_Control(pDX, IDC_EDIT_IFL, editImageFilesPath);
	DDX_Control(pDX, IDC_EDIT_CFL, editConfigurationFilesPath);
	DDX_Control(pDX, IDC_STATIC_CFL, staticConfigurationFile);
	DDX_Control(pDX, IDC_STATIC_IFL, staticImageFilePath);
}

BOOL ImageSourceDialog::PreTranslateMessage(MSG* pMsg)
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

BEGIN_MESSAGE_MAP(ImageSourceDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IFL, &ImageSourceDialog::OnBnClickedButtonImageFileLocationSelector)
	ON_BN_CLICKED(IDC_BUTTON_CFL, &ImageSourceDialog::OnBnClickedButtonConfigurationFileSelector)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_FILE_GROUBBOX, &ImageSourceDialog::OnNMClickGroupBox)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_CAMERA_GROUPBOX, &ImageSourceDialog::OnNMClickGroupBox)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ImageSourceDialog message handlers





void ImageSourceDialog::OnBnClickedButtonImageFileLocationSelector()
{
	// TODO: Add your control notification handler code here
	CFolderPickerDialog m_dlg;
	CString m_Folder;
	m_dlg.m_ofn.lpstrTitle = _T("Select Image Files Folder");
	m_dlg.m_ofn.lpstrInitialDir = _T(".\\");
	if (m_dlg.DoModal() != IDOK) return; // failed
	m_Folder = m_dlg.GetPathName(); 
	m_Folder += _T("\\");
	editImageFilesPath.SetWindowTextW(m_Folder);
	imgSourceSettings.imageFilesPath = CW2A(m_Folder);
	isModified = true;
}


void ImageSourceDialog::OnBnClickedButtonConfigurationFileSelector()
{
	CFileDialog fOpenDlg(true, _T("ini"), _T("CameraConfig"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("Camera Configuration Files (*.mcf)|*.mcf|"), this);
	fOpenDlg.m_pOFN->lpstrTitle = _T("Select Camera Configuration File");
	fOpenDlg.m_pOFN->lpstrInitialDir = _T(".\\");
	auto result = fOpenDlg.DoModal();
	if (result != IDOK) return; // failed
	editConfigurationFilesPath.SetWindowTextW(fOpenDlg.GetPathName());
	imgSourceSettings.configFilePath = CW2A(fOpenDlg.GetPathName());
	isModified = true;
}


void ImageSourceDialog::ConfigureDialog(ImageSourceSettings &_imgSourceSettings)
{
	imgSourceSettings = _imgSourceSettings;
}

void ImageSourceDialog::OnNMClickGroupBox(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (groupBoxFile.GetCheck())
	{
		imgSourceSettings.imageSourceType = ImageSourceType::File;
	}
	else
	{
		imgSourceSettings.imageSourceType = ImageSourceType::Camera;
	}
	isModified = true;
}

BOOL ImageSourceDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH ImageSourceDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
