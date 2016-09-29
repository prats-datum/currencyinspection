#pragma once
#include "afxwin.h"


// AboutInfo dialog

class AboutInfo : public CDialog
{
	DECLARE_DYNAMIC(AboutInfo)

public:
	AboutInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~AboutInfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINWINDOW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
};
