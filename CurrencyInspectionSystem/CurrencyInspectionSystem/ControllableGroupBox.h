#pragma once


// CheckableGroupBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControllableGroupBox window

class CControllableGroupBox : public CStatic
{
	DECLARE_DYNAMIC(CControllableGroupBox)
public:
	CControllableGroupBox();
	~CControllableGroupBox();
	
	void SetEnable(BOOL isEnabled);
	void SetVisible(BOOL isVisble);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
	afx_msg void OnCustomdraw(NMHDR * pNMHDR, LRESULT * pResult);
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
