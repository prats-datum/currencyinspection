#pragma once
#include "afxcmn.h"
#include "ImageSourceDialog.h"
#include <Vector>
#include "afxwin.h"
#include "afxbutton.h"

// ImageSourceSelectionDialog dialog

class ImageSourceSelectionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ImageSourceSelectionDialog)

public:
	ImageSourceSelectionDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ImageSourceSelectionDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_SOURCE_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CFont font;

	bool isTabCtrlInitialized;
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl tabCtrlCamera;
	std::vector<ImageSourceDialog *> imageSourceDlgList;
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNMClickTabCamera(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic staticImageSourceWindow;
	CMFCButton buttonOkay;
	CMFCButton buttonCancel;
	afx_msg void OnBnClickedMfcbuttonOkayIs();
	afx_msg void OnBnClickedMfcbuttonCancelIs();
	bool IsSettingsModified();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStatic staticImageSourceSelection;
};
