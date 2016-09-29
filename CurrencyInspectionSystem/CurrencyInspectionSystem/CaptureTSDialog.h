#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "Globals.h"


// CaptureTSDialog dialog

class CaptureTSDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CaptureTSDialog)

public:
	CaptureTSDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CaptureTSDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAPTURE_TRAINING_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	bool isGrabbingStarted;

	DECLARE_MESSAGE_MAP()
public:
	CEdit editNoOfImagesToCapture;
	CMFCButton buttonStartCapturing;
	CMFCButton buttonStopCapturing;
	CStatic staticCaptureStatus;
	afx_msg void OnBnClickedMfcbuttonStart();
	afx_msg void OnBnClickedMfcbuttonStop();
	afx_msg LRESULT OnImageCaptureStatusReceived(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImageCaptureFailureStatusReceived(WPARAM wParam, LPARAM lParam);
	int GetNoOfImagesToGrabCount();
	CMFCButton buttonClose;
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
};
