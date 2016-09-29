#pragma once
#include "Region Editor\RegionEditor.h"
#include "ExtendedTrainingData.h"
#include "afxwin.h"
#include "afxbutton.h"

// DefectsPreviewer dialog

class DefectsPreviewer : public CDialogEx
{
	DECLARE_DYNAMIC(DefectsPreviewer)

public:
	DefectsPreviewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~DefectsPreviewer();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEFECTS_PREVIEWER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	HwindowAdv mainWindow;
	std::map<ULONG, ExtendedTrainingData> *extendedTrainingDataList;
	CFont font;
	int imgIndex;
	int defectIndex;
	int tolalLearningsCount;
	int currentLeariningIndex;
	void UpdateDisplay();

	void UpdateUI();
	HRegion defectRegion;
	double defectValue, defectSize;

	DECLARE_MESSAGE_MAP()
public:
	CStatic staticMainWindowHolder;
	void SetTrainingDataList(std::map<ULONG, ExtendedTrainingData> &_extendedTrainingDataList);
	CMFCButton buttonPrevious;
	CMFCButton buttonNext;
	CMFCButton buttonRemove;
	CStatic staticDefectIndexStatus;
	CStatic staticImageNumberStatus;
	CStatic staticCameraIDStatus;
	CStatic staticDefectValueStatus;
	CStatic staticDefectSizeStatus;
	afx_msg void OnBnClickedMfcbuttonLeftShift();
	afx_msg void OnBnClickedMfcbuttonRightShift();
	afx_msg void OnBnClickedMfcbuttonOk();
	afx_msg void OnBnClickedMfcbuttonRemoveDefect();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStatic staticLearnPreview;
	CStatic staticGroupDefectDetails;
	CMFCButton buttonClose;
};
