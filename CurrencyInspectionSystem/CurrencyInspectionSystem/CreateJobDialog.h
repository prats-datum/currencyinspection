#pragma once
#include "Globals.h"
#include <list>
#include "afxwin.h"
#include "ShiftManager.h"

// CreateJobDialog dialog

class CreateJobDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreateJobDialog)

public:
	CreateJobDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CreateJobDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATEJOB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	std::vector<std::string> goldenList;
	std::vector<ShiftTypes> shiftList;
	DECLARE_MESSAGE_MAP()
	CFont font;
public:
	CMFCButton buttonClose;
	CMFCButton buttonOkay;
	CComboBox comboBoxGoldenList;
	CComboBox comboBoxShiftID;
	void ConfigureDialog(std::vector<std::string> &_goldenList);
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg void OnBnClickedMfcbuttonOkay();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	CStatic staticShiftDetails;
};
