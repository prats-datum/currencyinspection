
// OISEmulatorDlg.h : header file
//

#pragma once
#include "MachineCommunicator.h"
#include "afxbutton.h"
#include "afxwin.h"
#include "afxcmn.h"

// COISEmulatorDlg dialog
class COISEmulatorDlg : public CDialogEx, public DIONotificationReceiver
{
// Construction
public:
	COISEmulatorDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OISEMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG *pMsg);

// Implementation
protected:
	HICON m_hIcon;
	CFont font;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	bool isPreparationCompleted;
	bool isInspectionAvailable;
	bool isSystemAbnormal;
	bool isTowerLampBlue;
	bool isTowerLampYellow;
	bool isTowerLampRed;
	bool machineState;
	bool inspectionState;

	ULONG imageNumber;
	ULONG ejectorCount;
public:
	CMFCButton buttonPreparationCompleted;
	CMFCButton buttonInspectionAvailable;
	CMFCButton buttonSystemAbnormal;
	CMFCButton buttonTowerLampBlue;
	CMFCButton buttonTowerLampYellow;
	CMFCButton buttonTowerLampRed;
	afx_msg void OnBnClickedMfcbuttonPreparationcompleted();
	afx_msg void OnBnClickedMfcbuttonInspectionavailable();
	afx_msg void OnBnClickedMfcbuttonAbnormalstate();
	afx_msg void OnBnClickedMfcbuttonTowerlampblue();
	afx_msg void OnBnClickedMfcbuttonTowerlampyellow();
	afx_msg void OnBnClickedMfcbuttonTowerlampred();

	virtual void OnDIONotificationReceived(SignalName dioSignalName);
	CEdit logViewer;

	void AppendLog(CString _log);
	CStatic staticMachineState;
	CStatic staticInspectionState;
	afx_msg void OnBnClickedSetRGBLight1();
	afx_msg void OnBnClickedSetRGBLight2();
	afx_msg void OnBnClickedIRLight1();
	afx_msg void OnBnClickedIRLight2();
	CSpinButtonCtrl spinRGBLight1;
	CSpinButtonCtrl spinRGBLight2;
	CSpinButtonCtrl spinIRLight1;
	CSpinButtonCtrl spinIRLight2;
	CEdit editRGBValue1;
	CEdit editRGBValue2;
	CEdit editIRValue1;
	CEdit editIRValue2;
};
