#pragma once

#include <afxmt.h>
#include "resource.h"
#include "ResultStatsWindow.h"
#include "GraphObject.h"
#include "ControllableGroupBox.h"
#include "HalconCpp.h"
#include "Globals.h"
#include "GoldenData.h"
#include "Region Editor\RegionEditor.h"
#include "afxcmn.h"
#include "ResultData.h"
#include "ChartDataManager.h"
#include "ShiftManager.h"
#include "ShiftData.h"
#include "afxwin.h"
// CameraResultViewer dialog
using namespace HalconCpp;


class CameraResultViewer : public CDialogEx, public iCameraResultReceiver
{
	DECLARE_DYNAMIC(CameraResultViewer)

public:
	CameraResultViewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CameraResultViewer();
	CFont m_Font;
	int camID;
	enum { IDD = IDD_DIALOG_CAMERA_RESULT_VIEWER };
	CRITICAL_SECTION                 imageMutex,resultMutex;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERA_RESULT_VIEWER };
#endif
	
	ResultStatsWindow resultstatswindow;
//	int OnGraphInitialUpdate();
protected:
	HwindowAdv imageWindow;
	bool isHWindowInitialized = false;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CStatic staticImageWindow;
	DECLARE_MESSAGE_MAP()
	CControllableGroupBox contGroupBoxStatsWindow;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DisplayGraphicalResults(int taskID,bool isCollaged);
	ULONG *elapsedTime;
protected:
	HICON m_hIcon;
	HACCEL  m_hAccelTable;
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString GetElapsedTime(time_t &startTime, time_t &elapsedTime);
	afx_msg void OnMouseMovePlotArea();
	void OnClickStrip();
	// Draw chart
	void drawChart(CChartViewer *viewer);
	void realtimeStripChart(XYChart *c);
	void selectStripTask(XYChart * c, int mouseX, int mouseY);
	void trackBoxLegend(XYChart * c, int mouseX, int mouseY,bool isMouseOnPlotArea);
	virtual BOOL OnInitDialog();
	CGraphObject *m_pGraphObject1, *m_pGraphObject2, *m_pGraphObject3;
public:
	CStatic staticPieChart;
	CStatic staticBarChart;
	CStatic staticLineChart;
	CEdit editDashBrdTitle;
	CStaticEx staticTemp;
	CameraData thisCameraModelData;
	HRegion inspectionWindow;
	LayerResultData *layerResult;
	BlobAnalyzerResultData *baResult;
	ThreadResultData *thResult;
	HRegion UpWisePartition, failedUpRegions;
	HTuple failedUpIndex, upWiseStatus,upArray,temp;
	shared_ptr<CameraResultData>camResultData;
	HTREEITEM hParent, hchild;
public:
	
	// //Add InspectionTask under a specific camera
	
	virtual void OnCameraResultReceived(ULONG _imageNumber, weak_ptr<CameraResultData> _camResultData);
	void SetCameraModelData(string cameraDataLocation);
	void setShiftData(ShiftData & _shiftData);
	void SetShiftData(ShiftData &shiftData);
	void EndShift(ShiftData &shiftData);
	bool resultReceived, isShift;
	//SimpleTreeCtrl declarations

	int lastDisplayTaskID;
	void DisplayResultRegion();
	afx_msg LRESULT OnCameraResultReceivedMessage(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL CreateFontObject(int nOption, CFont* pFont);
	void OnViewPortChanged();
	HBRUSH OnCtlColor(CDC* pDC, CWnd *pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	shared_ptr< ChartDataManager> chartData;
	CControllableGroupBox contGroupBoxStripChart;
	CRect stripRect;
	CChartViewer m_ResultHistoryViewer;
	int	m_UpdatePeriod;
	int selectedStripboxLeft;
	int selectedStripboxRight;
	int selectedStripIndex;
	int startdocCount;
	// Displays the current image number
	CString m_imagenumber;
	CStatic imageNumberStaticCtrl;
	// //Shows shift info
	CString m_shiftInfo;
	afx_msg void OnBnClickedButton1();
};
