#pragma once
#include "Globals.h"
#include "afxwin.h"
#include "Region Editor\RegionEditor.h"
#include "ResultData.h"

// CameraRejectsViewer dialog


class CameraRejectsViewer : public CDialogEx, iHalconWindowEventReceiver
{
	DECLARE_DYNAMIC(CameraRejectsViewer)

public:
	CameraRejectsViewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CameraRejectsViewer();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA_REJECTS_VIEWER };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateDisplay();
	void UpdateMainWindowImage();
	void UpdateMainWindowDefectRegions();
	void UpdateMainWindowHighlightRegion();
	void UpdateZoomWindow();
	void ParseAndStoreDefectData(HRegion &defectRegion, HTuple &defectValue, DefectBlobType _defectType, std::vector<DefectData> &defectDataList, bool isImageTrained, std::list<int> addedBlobIDs);
	DefectData *selectedDefectData;
	std::vector<DefectData> majorBlobsList;
	std::vector<DefectData> dominantBlobsList;
	HImage displayImage;
	bool isDisplayImageTrained;


	bool isHWindowInitialized;
	HwindowAdv mainWindow, zoomWindow;
	void OnRegionSelectedEvent(UINT regID, void *tag);
	void OnRegionModifiedEvent(UINT regID, void *tag);
		

	DECLARE_MESSAGE_MAP()
public:
	CStatic staticMainWindowHolder;
	CStatic staticZoomWindowHolder;
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void DisplayCameraResults(shared_ptr<CameraResultData>camResultData, bool isImageTrained, std::list<int> learnedMajorBlobsID, std::list<int> learnedDominantBlobsID);
	void ClearCameraResults();
	CStatic selectedDefectSize;
	CStatic selectedDefectValue;
	CStatic verticalMeasurementValue;
	CStatic horizontalMeasurementValue;
	afx_msg void OnBnClickedMfcbuttonNavigateLeft();
	afx_msg void OnBnClickedMfcbuttonNavigateRight();
	afx_msg void OnBnClickedMfcbuttonAddDefect();
	afx_msg void OnBnClickedMfcbuttonAddAllDefect();
	afx_msg void OnBnClickedMfcbuttonAddImage();
	CStatic threadInspectionResult;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStatic staticGroupSelectedDefectDetails;
	CStatic staticGroupRegistration;
	CStatic staticGroupThreadDetection;
};
