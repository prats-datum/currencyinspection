// BuldGoldenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "BuldGoldenDialog.h"
#include "afxdialogex.h"
#include ".\CGridListCtrlEx\CGridColumnTraitText.h"
#include ".\CGridListCtrlEx\CGridColumnTraitImage.h"
#include ".\CGridListCtrlEx\CGridRowTraitXP.h"
#include ".\CGridListCtrlEx\ViewConfigSection.h"


// BuldGoldenDialog dialog

IMPLEMENT_DYNAMIC(BuldGoldenDialog, CDialogEx)

BuldGoldenDialog::BuldGoldenDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GOLDEN_BUILD_DIALOG, pParent)
{
m_pEditBkBrush = new CBrush(DialogBackgroundColor);

}

BuldGoldenDialog::~BuldGoldenDialog()
{
	m_pEditBkBrush->DeleteObject();
}

void BuldGoldenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BUILDING_STATUS, staticcurrentBuildingStatus);
	DDX_Control(pDX, IDC_MFCBUTTON_CANCEL, buttonCancel);
	DDX_Control(pDX, IDC_LIST_TRAINING_SET_STATUS, listCtrlTrainingSet);
	DDX_Control(pDX, IDC_PROGRESS, progressBarCtrl);
	DDX_Control(pDX, IDC_STATIC_GOLDEN_BUILD_STATUS, staticBuildWindowStatus);
}

BOOL BuldGoldenDialog::OnInitDialog()
{
	BOOL returnValue = CDialogEx::OnInitDialog();
	InitializeTrainingSetListView();
	CenterWindow();
	buttonCancel.SetWindowTextW(_T("Cancel"));
	staticBuildWindowStatus.SetWindowTextW(_T("Golden Build is in progress..."));
	return returnValue;
}

BOOL BuldGoldenDialog::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		bRet = TRUE; // do not dispatch message
	}
	else
	{
		bRet = CDialog::PreTranslateMessage(pMsg);
	}
	return bRet;
}


BEGIN_MESSAGE_MAP(BuldGoldenDialog, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_CANCEL, &BuldGoldenDialog::OnBnClickedMfcbuttonCancel)
	ON_MESSAGE(UWM_IMAGE_EXTEND_COMPLETED, &BuldGoldenDialog::OnImageExtendCompleted)
	ON_MESSAGE(UWM_IMAGE_EXTEND_ERROR, &BuldGoldenDialog::OnImageExtendError)
	//ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// BuldGoldenDialog message handlers


void BuldGoldenDialog::OnBnClickedMfcbuttonCancel()
{
	// TODO: Add your control notification handler code here
	this->PostMessageW(WM_CLOSE, NULL, NULL);
	GetParent()->PostMessageW(UWM_IMAGE_MODEL_BUILD_ENDED, NULL, NULL);
	this->CloseWindow();
}


void BuldGoldenDialog::InitializeTrainingSetListView()
{
	imageList.Create(24, 24, ILC_COLOR24 | ILC_MASK, 1, 0);

	COLORREF rgbTransparentColor = RGB(0, 0, 0);
	CBitmap bmp1;
	bmp1.LoadBitmapW(IDB_BITMAP_UNTRAINED);
	imageList.Add(&bmp1, rgbTransparentColor);
	CBitmap bmp2;
	bmp2.LoadBitmapW(IDB_BITMAP_TRAINED);
	imageList.Add(&bmp2, rgbTransparentColor);

	listCtrlTrainingSet.SetImageList(&imageList, LVSIL_SMALL);

	listCtrlTrainingSet.SetCellMargin(1);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	listCtrlTrainingSet.SetDefaultRowTrait(pRowTrait);
	listCtrlTrainingSet.EnableVisualStyles(true);

	listCtrlTrainingSet.InsertHiddenLabelColumn();	// Requires one never uses column 0

	CString title = L"";
	CGridColumnTrait* pTrait = NULL;
	CGridColumnTraitImage* pImageTrait = NULL;

	int columnIndex = 1;

	title = L"*";
	pImageTrait = new CGridColumnTraitImage();
	pImageTrait->AddImageIndex(0);
	pImageTrait->AddImageIndex(1);
	pImageTrait->GetColumnState().m_Editable = false;

	pTrait = pImageTrait;
	listCtrlTrainingSet.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 24, columnIndex - 1, pTrait);
	columnIndex++;


	title = L"Image Number";
	pTrait = new CGridColumnTraitText;
	pTrait->GetColumnState().m_AlwaysHidden = true;
	listCtrlTrainingSet.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 10, columnIndex - 1, pTrait);
	columnIndex++;


	title = L"Training Set";
	pTrait = new CGridColumnTraitText;
	listCtrlTrainingSet.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 120, columnIndex - 1, pTrait);
	columnIndex++;


	title = L"Details";
	pTrait = new CGridColumnTraitText;
	listCtrlTrainingSet.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 220, columnIndex - 1, pTrait);
	columnIndex++;
}


void BuldGoldenDialog::UpdateTrainingSetListView()
{
	listCtrlTrainingSet.DeleteAllItems();
	int itemIndex = 0;
	for (auto &e : *trainingImageData)
	{
		CString tsName = _T("");
		if (e.type == BasicTrainingSet)
		{
			tsName.Format(_T("Base TrainingSet %d"), e.imgNumber);
		}
		else
		{
			tsName.Format(_T("Extended TrainingSet %d"), e.imgNumber);
		}
		listCtrlTrainingSet.InsertItem(itemIndex, tsName);
		listCtrlTrainingSet.SetItemData(itemIndex, itemIndex);
		int columnIndex = 1;
		listCtrlTrainingSet.SetCellImage(itemIndex, columnIndex, (int)e.isTrained);
		columnIndex++;
		CString imgNumber;
		imgNumber.Format(_T("%d"), e.imgNumber);
		listCtrlTrainingSet.SetItemText(itemIndex, columnIndex, imgNumber);
		columnIndex++;
		listCtrlTrainingSet.SetItemText(itemIndex, columnIndex, tsName);
		columnIndex++;
		itemIndex++;
	}
}


void BuldGoldenDialog::SetTrainingSetData(std::vector<TrainingImageData> &_trainingImageData)
{
	trainingImageData = &_trainingImageData;
	UpdateTrainingSetListView();
	builtImageCount = 0;
	CString temp;
	temp.Format(_T("Building Image %d of %d"), builtImageCount, trainingImageData->size());
	staticcurrentBuildingStatus.SetWindowTextW(temp);
	progressBarCtrl.SetWindowText(_T("Completed "));
	progressBarCtrl.SetRange(builtImageCount, trainingImageData->size());
	progressBarCtrl.SetPos(builtImageCount);
	buttonCancel.SetWindowTextW(_T("Cancel"));
	staticBuildWindowStatus.SetWindowTextW(_T("Golden Build is in progress..."));
	buttonCancel.SetFocus();
}


void BuldGoldenDialog::OnTrainingSetExceptionReceived(UINT trainingSetNumber, char *exceptionMessage)
{
	this->PostMessageW(UWM_IMAGE_EXTEND_ERROR, (WPARAM)trainingSetNumber, (LPARAM)exceptionMessage);
}


void BuldGoldenDialog::OnTrainingSetBuildStaus(UINT trainingSetNumber, bool status)
{
	this->PostMessageW(UWM_IMAGE_EXTEND_COMPLETED, (WPARAM)trainingSetNumber, (LPARAM)status);
}


LRESULT BuldGoldenDialog::OnImageExtendCompleted(WPARAM wParam, LPARAM lParam)
{
	UINT trainingSetImageNumber = wParam;
	bool status = lParam;	
	int index = 0;
	for (auto &e : *trainingImageData)
	{
		if (e.imgNumber == trainingSetImageNumber)
		{
			break;
		}
		index++;
	}
	listCtrlTrainingSet.SetCellImage(index, 1, (int)status);
	listCtrlTrainingSet.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	listCtrlTrainingSet.SetSelectionMark(index);
	builtImageCount++;
	CString temp;
	temp.Format(_T("Building Image %d of %d"), builtImageCount, trainingImageData->size());
	staticcurrentBuildingStatus.SetWindowTextW(temp);
	progressBarCtrl.SetPos(builtImageCount);
	if (trainingImageData->rbegin()->imgNumber == trainingSetImageNumber)
	{
		staticBuildWindowStatus.SetWindowTextW(_T("Golden Build Completed!!"));
		this->SetFocus();
		this->SetActiveWindow();
		buttonCancel.SetWindowTextW(_T("Close"));
		buttonCancel.SetFocus();
		buttonCancel.SetActiveWindow();
	}
	return 1;
}


LRESULT BuldGoldenDialog::OnImageExtendError(WPARAM wParam, LPARAM lParam)
{
	char *ex = (char *)lParam;
	UINT trainingSetImageNumber = wParam;
	int index = 0;
	for (auto &e : *trainingImageData)
	{
		if (e.imgNumber == trainingSetImageNumber)
		{
			break;
		}
		index++;
	}
	listCtrlTrainingSet.SetItemText(index, 4, CString(ex));
	delete ex;
	return 1;
}

BOOL BuldGoldenDialog::OnEraseBkgnd(CDC* pDC)
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


HBRUSH BuldGoldenDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}
