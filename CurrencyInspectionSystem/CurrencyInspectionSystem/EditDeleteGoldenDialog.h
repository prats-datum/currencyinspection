#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "afxcmn.h"
#include "Globals.h"
#include <list>

// EditDeleteGoldenDialog dialog

class EditDeleteGoldenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(EditDeleteGoldenDialog)

public:
	EditDeleteGoldenDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditDeleteGoldenDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT_GOLDEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	std::vector<std::string> goldenList;
	GoldenModifyOperation modifyOperation;
	CFont font;

	DECLARE_MESSAGE_MAP()
public:
	CStatic staticTitle;
	CMFCButton buttonClose;
	CMFCButton buttonOkay;
	CComboBox comboBoxGoldenList;

	void ConfigureDialog(std::vector<std::string> &_goldenList, GoldenModifyOperation _modifyOperation);
	afx_msg void OnBnClickedMfcbuttonClose();
	afx_msg void OnBnClickedMfcbuttonOkay();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush* m_pEditBkBrush;
};
