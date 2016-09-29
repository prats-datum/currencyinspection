#pragma once
#include "afxwin.h"
#include "CheckableGroupBox\CheckableGroupBox.h"
#include "Globals.h"

// ImageSourceDialog dialog

class ImageSourceDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ImageSourceDialog)

public:
	ImageSourceDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ImageSourceDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_SOURCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CCheckableGroupBox groupBoxFile;
	CCheckableGroupBox groupBoxCamera;
	CEdit editImageFilesPath;
	CEdit editConfigurationFilesPath;
	bool isModified;
	ImageSourceSettings imgSourceSettings;
	afx_msg void OnBnClickedButtonImageFileLocationSelector();
	afx_msg void OnBnClickedButtonConfigurationFileSelector();
	afx_msg void OnNMClickGroupBox(NMHDR *pNMHDR, LRESULT *pResult);

	void ConfigureDialog(ImageSourceSettings &_imgSourceSettings);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStaticEx staticConfigurationFile;
	CStaticEx staticImageFilePath;
};
