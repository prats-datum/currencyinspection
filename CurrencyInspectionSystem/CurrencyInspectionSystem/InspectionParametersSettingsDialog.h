#pragma once
#include "Globals.h"
#include ".\CGridListCtrlEx\CGridListCtrlGroups.h"
#include "InspectionParametersConfigReader.h"
#include "afxwin.h"

// InspectionParametersSettingsDialog dialog

class InspectionParametersSettingsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(InspectionParametersSettingsDialog)

private:
	CGridListCtrlGroups listCtrlRegionTolerance, listCtrlRegionLimit, listCtrlRegionGain, listCtrlBlobParameters;
	bool isModified;
	CImageList imagesListBlobParameters;
	CFont font;
public:
	InspectionParametersSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~InspectionParametersSettingsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PARAMETER_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InitializeParametersList();
	void UpdateParametersToList();
	void UpdateParametersFromList();
	DECLARE_MESSAGE_MAP()
public:
	CMFCButton buttonOkay, buttonClose;
	afx_msg void OnBnClickedMfcbuttonOkay();
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg void OnLvnEndlabeleditAnyParameter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStatic staticInsParamSettings;
	CStatic staticRegParams;
	CStatic staticBlobParams;
};
