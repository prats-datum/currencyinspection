#include "stdafx.h"
#include "ControllableGroupBox.h"
#include "Globals.h"
IMPLEMENT_DYNAMIC(CControllableGroupBox, CStatic)

CControllableGroupBox::CControllableGroupBox()
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
}


CControllableGroupBox::~CControllableGroupBox()
{
	m_pEditBkBrush->DeleteObject();
}


BEGIN_MESSAGE_MAP(CControllableGroupBox, CStatic)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
END_MESSAGE_MAP()


void CControllableGroupBox::SetEnable(BOOL isEnabled)
{
	CRect rcGroupbox;
	GetWindowRect(rcGroupbox);

	// Get first child control
	CWnd* pWnd = GetParent()->GetWindow(GW_CHILD);

	CRect rcWnd, rcTest;

	while (pWnd)
	{
		pWnd->GetWindowRect(rcWnd);
		
		//if (rcTest.IntersectRect(rcGroupbox, rcWnd)
		//	&& pWnd != this)
		if (!rcTest.SubtractRect(rcWnd, rcGroupbox)
			&& pWnd != this)
		{
			bool type = pWnd->IsKindOf(RUNTIME_CLASS(CStatic));
			if (!type)
			{
				pWnd->EnableWindow(isEnabled);
			}
			
		}
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	this->EnableWindow(isEnabled);
}

void CControllableGroupBox::SetVisible(BOOL isVisble)
{
	CRect rcGroupbox;
	GetWindowRect(rcGroupbox);

	// Get first child control
	CWnd* pWnd = GetParent()->GetWindow(GW_CHILD);

	CRect rcWnd, rcTest;

	while (pWnd)
	{
		pWnd->GetWindowRect(rcWnd);

		//if (rcTest.IntersectRect(rcGroupbox, rcWnd)
		//	&& pWnd != this)
		if (!rcTest.SubtractRect(rcWnd, rcGroupbox)
			&& pWnd != this)
		{
			pWnd->ShowWindow(isVisble);
		}
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	this->ShowWindow(isVisble);
}

BOOL CControllableGroupBox::OnEraseBkgnd(CDC * pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(DialogBackgroundColor);    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);    // restore old brush
	return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CControllableGroupBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	
	switch (nCtlColor) {

	case CTLCOLOR_MSGBOX:
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_EDIT:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_LISTBOX:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_BTN:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_DLG:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_SCROLLBAR:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_STATIC:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	case CTLCOLOR_MAX:
		// Set color to green on black and return the background
		pDC->SetTextColor(DialogStaticTextColor);
		pDC->SetBkColor(DialogBackgroundColor);
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());

	default:
		//pDC->SetTextColor(DialogStaticTextColor);
		//pDC->SetBkColor(DialogBackgroundColor);
		return CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}


void CControllableGroupBox::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	switch (pLVCD->nmcd.dwDrawStage) {
	case CDDS_ITEM:
	case CDDS_POSTPAINT:
	case CDDS_PREERASE:
	case CDDS_POSTERASE:
	case CDDS_ITEMPOSTPAINT:
	case CDDS_ITEMPREERASE:
	case CDDS_ITEMPOSTERASE:
		break;
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		pLVCD->clrTextBk = DialogBackgroundColor;
		pLVCD->clrText = DialogStaticTextColor;
		break;
	}
}