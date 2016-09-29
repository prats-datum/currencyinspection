#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include ".\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "WaitScreenDialog.h" // For some reason not able to include TextProgressCtrl in two different files. So, including WaitScreenDialog header which includes TextProgressCtrl
#include "Globals.h"

// BuldGoldenDialog dialog

class BuldGoldenDialog : public CDialogEx, public iTrainingSetStatusReceiver
{
	DECLARE_DYNAMIC(BuldGoldenDialog)
	std::vector<TrainingImageData> *trainingImageData;
	CImageList imageList;
	int builtImageCount;

public:
	BuldGoldenDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~BuldGoldenDialog();
	CGridListCtrlGroups listCtrlTrainingSet;
	CustomProgressbar::CTextProgressCtrl progressBarCtrl;


	enum { IDD = IDD_DIALOG_GOLDEN_BUILD_DIALOG };
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GOLDEN_BUILD_DIALOG };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void InitializeTrainingSetListView();
	void UpdateTrainingSetListView();
	DECLARE_MESSAGE_MAP()
public:
	CStatic staticcurrentBuildingStatus;
	CMFCButton buttonCancel;
	afx_msg void OnBnClickedMfcbuttonCancel();
	void SetTrainingSetData(std::vector<TrainingImageData> &trainingImageData);
	virtual void OnTrainingSetExceptionReceived(UINT trainingSetNumber, char *exceptionMessage);
	virtual void OnTrainingSetBuildStaus(UINT trainingSetNumber, bool status);

	afx_msg LRESULT OnImageExtendCompleted(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImageExtendError(WPARAM wParam, LPARAM lParam);
	CStatic staticBuildWindowStatus;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
};
