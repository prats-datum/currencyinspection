#pragma once
#include "HalconCpp.h"
#include "afxwin.h"
#include "Globals.h"
#include "GoldenData.h"
#include "ControllableGroupBox.h"
#include "Region Editor\RegionEditor.h"

// ImageWindowDialog dialog

using namespace HalconCpp;

class ImageWindowDialog : public CDialogEx, iHalconWindowEventReceiver
{
	DECLARE_DYNAMIC(ImageWindowDialog)

public:
	ImageWindowDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ImageWindowDialog();
	enum { IDD = IDD_DIALOG_IMAGE_WINDOW};
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_WINDOW };
#endif
protected:
	CToolTipCtrl toolTipCtrl;
	HwindowAdv mainWindow;
	bool isHWindowInitialized = false;
	OperationMode modeOfOperation;
	int lastSelectedLayerID, lastSelectedRegionID;
	CameraData *cameraData;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	HImage lastDisplayedTS;
	CToolBar wndToolBar;


	DECLARE_MESSAGE_MAP()

	void DisplayImage(HImage &img);
	void DisplayAnchor(UINT _layerID);
	void DisplayRepAnchor(UINT _layerID);
	void DisplayUniqueInspectionRegions(UINT _layerID);
	void DisplayUniqueMaskRegions(UINT _layerID);
	void DisplayRepInspectionRegions(UINT _layerID);
	void DisplayRepMaskRegions(UINT _layerID);
	void DisplayUniqueRegions(UINT _layerID);
	void DisplayRepRegions(UINT _layerID);
	void DisplayThreadRegions();
	void DisplayUniqueStatisticsRegions(UINT _layerID);
	void DisplayRepStatisticsRegions(UINT _layerID);
	void DisplayMeasurementRegions();
	
	void GetInpectionWindow();
	HRegion GetFreeDrawRegion();
	HRegion GetRectRegion();
	HImage GetSingleNoteImage();
	void UpdateRadioButtonForTheSelectedRegion();


	void HandleAnchorRegionClickEvent(Hlong row, Hlong column);
	void HandleRepAnchorRegionClickEvent(Hlong row, Hlong column);
	void HandleUniqueRegionClickEvent(Hlong row, Hlong column);
	void HandleRepititiveRegionClickEvent(Hlong row, Hlong column);
	void HandleThreadRegionClickEvent(Hlong row, Hlong column);


	void UpdateRegion(HRegion &tempRegion);
	void UpdateUniqueInsReg(UINT _layerID, UINT _regID, HRegion &_uniqueInsReg);
	void UpdateUniqueMaskReg(UINT _layerID, UINT _regID, HRegion &_uniqueMaskReg);
	void UpdateRepInsReg(UINT _layerID, UINT _regID, HRegion &_repInsReg);
	void UpdateRepsMaskReg(UINT _layerID, UINT _regID, HRegion &_repMaskReg);
	void UpdateStatisticsReg(UINT _layerID, UINT _regID, HRegion &_repStatReg);

	void UpdateRepeatingPortion(LayerRegion *reg);
	void UpdateMeasurementCoordinates(Measurement *measurement);
	void UpdateAllMeasurementCoordinates();
	void UpdateMeasurementReferenceCoordinates(LayerData *layerData);
	void UpdateAllRepRegionsForTheLayer();

	void UpdateAllRepLocations();


	void OnRegionSelectedEvent(UINT regID, void *tag);
	void OnRegionModifiedEvent(UINT regID, void *tag);

public:

	void SetCameraGoldenData(CameraData &cameraData);

	void DisplayTrainingSet(HImage &_tsImage);
	CStatic staticImageWindow;
	CControllableGroupBox contGroupBoxRadioButton;

	afx_msg LRESULT OnSetMasterImageMessage(WPARAM wParam, LPARAM lParam);

	void UpdateDisplay();
	void ClearDisplay();
	void ChangeSelectedLayerIndex(UINT _layerID);
	void ChangeSelectedRegionID(int _regID, RegionTypes _regType);
	void SetOperationMode(OperationMode _modeOfOperation);
	afx_msg void OnRadioButtonSelectChanged();
	afx_msg void OnClickDrawRectRegion();
	afx_msg void OnClickDrawFreeRegion();
	afx_msg void OnClickDeleteRegion();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
};
