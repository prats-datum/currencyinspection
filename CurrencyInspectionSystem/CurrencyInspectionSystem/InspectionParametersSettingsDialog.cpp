// InspectionParametersSettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyInspectionSystem.h"
#include "InspectionParametersSettingsDialog.h"
#include "afxdialogex.h"
#include ".\CGridListCtrlEx\CGridColumnTraitText.h"
#include ".\CGridListCtrlEx\CGridColumnTraitEdit.h"
#include ".\CGridListCtrlEx\CGridColumnTraitImage.h"
#include ".\CGridListCtrlEx\CGridRowTraitXP.h"
#include ".\CGridListCtrlEx\ViewConfigSection.h"
#include "ApplicationSettingsReader.h"


// InspectionParametersSettingsDialog dialog

IMPLEMENT_DYNAMIC(InspectionParametersSettingsDialog, CDialogEx)

InspectionParametersSettingsDialog::InspectionParametersSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PARAMETER_SETTINGS, pParent)
{
	m_pEditBkBrush = new CBrush(DialogBackgroundColor);
	imagesListBlobParameters.Create(24, 24, ILC_COLOR24 | ILC_MASK, 1, 0);

	COLORREF rgbTransparentColor = RGB(255, 255, 255);
	CBitmap bmp1;
	bmp1.LoadBitmapW(IDB_BITMAP_ONE_STAR);
	imagesListBlobParameters.Add(&bmp1, rgbTransparentColor);
	CBitmap bmp2;
	bmp2.LoadBitmapW(IDB_BITMAP_TWO_STAR);
	imagesListBlobParameters.Add(&bmp2, rgbTransparentColor);
	CBitmap bmp3;
	bmp3.LoadBitmapW(IDB_BITMAP_THREE_STAR);
	imagesListBlobParameters.Add(&bmp3, rgbTransparentColor);

}

InspectionParametersSettingsDialog::~InspectionParametersSettingsDialog()
{
	m_pEditBkBrush->DeleteObject();
}

void InspectionParametersSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REGION_TOLERANCE, listCtrlRegionTolerance);
	DDX_Control(pDX, IDC_LIST_REGION_GAIN, listCtrlRegionGain);
	DDX_Control(pDX, IDC_LIST_REGION_LIMIT, listCtrlRegionLimit);
	DDX_Control(pDX, IDC_LIST_BLOB_PARAMETERS, listCtrlBlobParameters);
	DDX_Control(pDX, IDC_MFCBUTTON_OKAY, buttonOkay);
	DDX_Control(pDX, IDC_MFCBUTTON_CLOSE, buttonClose);

	DDX_Control(pDX, IDC_STATIC_TITLE, staticInsParamSettings);
	DDX_Control(pDX, IDC_STATIC_REGION_PARAMETERS, staticRegParams);
	DDX_Control(pDX, IDC_STATIC_BLOB_PARAMETERS, staticBlobParams);
}
BOOL InspectionParametersSettingsDialog::PreTranslateMessage(MSG* pMsg)
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
BOOL InspectionParametersSettingsDialog::OnInitDialog()
{
	BOOL returnValue = CDialogEx::OnInitDialog();
	InitializeParametersList();
	UpdateParametersToList();
	isModified = false;
	font.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		FIXED_PITCH | FF_ROMAN, _T("MS Serif"));
	staticInsParamSettings.SetFont(&font);
	staticBlobParams.SetFont(&font);
	staticRegParams.SetFont(&font);
	return returnValue;
}


BEGIN_MESSAGE_MAP(InspectionParametersSettingsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_OKAY, &InspectionParametersSettingsDialog::OnBnClickedMfcbuttonOkay)
	ON_BN_CLICKED(IDC_MFCBUTTON_CLOSE, &InspectionParametersSettingsDialog::OnBnClickedMfcbuttonClose)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_REGION_TOLERANCE, &InspectionParametersSettingsDialog::OnLvnEndlabeleditAnyParameter)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_REGION_GAIN, &InspectionParametersSettingsDialog::OnLvnEndlabeleditAnyParameter)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_REGION_LIMIT, &InspectionParametersSettingsDialog::OnLvnEndlabeleditAnyParameter)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_BLOB_PARAMETERS, &InspectionParametersSettingsDialog::OnLvnEndlabeleditAnyParameter)
	////ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// InspectionParametersSettingsDialog message handlers

void InspectionParametersSettingsDialog::InitializeParametersList()
{
	CString title = L""; 
	CGridRowTraitXP* pRowTrait = NULL;
	CGridColumnTrait* pTrait = NULL;
	CGridColumnTraitEdit* pTraitEdit = NULL;
	CGridColumnTraitImage* pImageTrait = NULL;
	int columnIndex;
	// Initialize Region Tolerance Settings View
	listCtrlRegionTolerance.SetCellMargin(1);
	pRowTrait = new CGridRowTraitXP;
	listCtrlRegionTolerance.SetDefaultRowTrait(pRowTrait);
	listCtrlRegionTolerance.EnableVisualStyles(true);
	listCtrlRegionTolerance.InsertHiddenLabelColumn();	// Requires one never uses column 0
	columnIndex = 1;
	title = _T("Tolerance");
	pTrait = new CGridColumnTraitText;
	listCtrlRegionTolerance.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 60, columnIndex - 1, pTrait);
	columnIndex++;
	int numOfColorChennels = ApplicationSettingsReader::GetInstance()->GetNumOfColorChennelforCamera(1);
	for (int channelID = 0; channelID < numOfColorChennels; channelID++)
	{
		ColorChannel thisColorChannelConfig = ApplicationSettingsReader::GetInstance()->GetColorChannelConfigforCamera(1, channelID);
		title = CString(thisColorChannelConfig.name.c_str());
		pTraitEdit = new CGridColumnTraitEdit;
		pTraitEdit->GetColumnState().m_Sortable = false;
		pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
		pTraitEdit->SetLimitText(3);
		pTraitEdit->SetMinMaxValueLimt(0, 100);
		listCtrlRegionTolerance.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 50, columnIndex - 1, pTraitEdit);
		columnIndex++;
	}


	// Initialize Region Gain Settings View
	listCtrlRegionGain.SetCellMargin(1);
	pRowTrait = new CGridRowTraitXP;
	listCtrlRegionGain.SetDefaultRowTrait(pRowTrait);
	listCtrlRegionGain.EnableVisualStyles(true);
	listCtrlRegionGain.InsertHiddenLabelColumn();	// Requires one never uses column 0
	columnIndex = 1;
	title = _T("Gain");
	pTrait = new CGridColumnTraitText;
	listCtrlRegionGain.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 60, columnIndex - 1, pTrait);
	columnIndex++;
	for (int channelID = 0; channelID < numOfColorChennels; channelID++)
	{
		ColorChannel thisColorChannelConfig = ApplicationSettingsReader::GetInstance()->GetColorChannelConfigforCamera(1, channelID);
		title = CString(thisColorChannelConfig.name.c_str());
		pTraitEdit = new CGridColumnTraitEdit;
		pTraitEdit->GetColumnState().m_Sortable = false;
		pTraitEdit->SetLimitText(3);
		pTraitEdit->SetMinMaxValueLimt(0, 10);
		pTraitEdit->AcceptOnlyNumbersAndDecimals(true);
		listCtrlRegionGain.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 50, columnIndex - 1, pTraitEdit);
		columnIndex++;
	}


	// Initialize Region Limit Settings View
	listCtrlRegionLimit.SetCellMargin(1);
	pRowTrait = new CGridRowTraitXP;
	listCtrlRegionLimit.SetDefaultRowTrait(pRowTrait);
	listCtrlRegionLimit.EnableVisualStyles(true);
	listCtrlRegionLimit.InsertHiddenLabelColumn();	// Requires one never uses column 0
	columnIndex = 1;
	title = _T("Limit");
	pTrait = new CGridColumnTraitText;
	listCtrlRegionLimit.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 60, columnIndex - 1, pTrait);
	columnIndex++;
	for (int channelID = 0; channelID < numOfColorChennels; channelID++)
	{
		ColorChannel thisColorChannelConfig = ApplicationSettingsReader::GetInstance()->GetColorChannelConfigforCamera(1, channelID);
		title = CString(thisColorChannelConfig.name.c_str());
		pTraitEdit = new CGridColumnTraitEdit;
		pTraitEdit->GetColumnState().m_Sortable = false;
		pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
		pTraitEdit->SetLimitText(3);
		pTraitEdit->SetMinMaxValueLimt(0, 100);
		listCtrlRegionLimit.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 50, columnIndex - 1, pTraitEdit);
		columnIndex++;
	}



	
	listCtrlBlobParameters.SetImageList(&imagesListBlobParameters, LVSIL_SMALL);
	// Initialize Blob Parameters Settings View
	listCtrlBlobParameters.SetCellMargin(1);
	pRowTrait = new CGridRowTraitXP;
	listCtrlBlobParameters.SetDefaultRowTrait(pRowTrait);
	listCtrlBlobParameters.EnableVisualStyles(true);
	listCtrlBlobParameters.InsertHiddenLabelColumn();	// Requires one never uses column 0
	columnIndex = 1;
	title = _T("*");
	//pTrait = new CGridColumnTraitText;
	//listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 60, columnIndex - 1, pTrait);

	pImageTrait = new CGridColumnTraitImage;

	pImageTrait->AddImageIndex(0);
	pImageTrait->AddImageIndex(1);
	pImageTrait->AddImageIndex(2);
	pImageTrait->GetColumnState().m_Editable = false;

	pTrait = pImageTrait;
	listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 24, columnIndex - 1, pTrait);


	columnIndex++;

	title = _T("Global Tolerance");
	pTraitEdit = new CGridColumnTraitEdit;
	pTraitEdit->GetColumnState().m_Sortable = false;
	pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
	pTraitEdit->SetLimitText(2);
	pTraitEdit->SetMinMaxValueLimt(0, 10);
	listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 100, columnIndex - 1, pTraitEdit);
	columnIndex++;

	title = _T("Major Blob Threshold");
	pTraitEdit = new CGridColumnTraitEdit;
	pTraitEdit->GetColumnState().m_Sortable = false;
	pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
	pTraitEdit->SetLimitText(4);
	pTraitEdit->SetMinMaxValueLimt(1, 1000);
	listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 100, columnIndex - 1, pTraitEdit);
	columnIndex++;

	title = _T("Dominant Blob Threshold");
	pTraitEdit = new CGridColumnTraitEdit;
	pTraitEdit->GetColumnState().m_Sortable = false;
	pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
	pTraitEdit->SetLimitText(5);
	pTraitEdit->SetMinMaxValueLimt(30, 10000);
	listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 150, columnIndex - 1, pTraitEdit);
	columnIndex++;

	title = _T("Group of Blob Threshold");
	pTraitEdit = new CGridColumnTraitEdit;
	pTraitEdit->GetColumnState().m_Sortable = false;
	pTraitEdit->SetStyle(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_BORDER | ES_NUMBER);
	pTraitEdit->SetLimitText(5);
	pTraitEdit->SetMinMaxValueLimt(100, 10000);
	listCtrlBlobParameters.InsertColumnTrait(columnIndex, title, LVCFMT_LEFT, 150, columnIndex - 1, pTraitEdit);
	columnIndex++;
}

void InspectionParametersSettingsDialog::UpdateParametersToList()
{
	int itemIndex = 0;
	for (auto &e : InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup)
	{
		itemIndex = listCtrlRegionTolerance.InsertItem(itemIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		itemIndex = listCtrlRegionGain.InsertItem(itemIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		itemIndex = listCtrlRegionLimit.InsertItem(itemIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		
		listCtrlRegionTolerance.SetItemData(itemIndex, itemIndex);
		listCtrlRegionGain.SetItemData(itemIndex, itemIndex);
		listCtrlRegionLimit.SetItemData(itemIndex, itemIndex);

		int columnIndex = 1;
		listCtrlRegionTolerance.SetItemText(itemIndex, columnIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		listCtrlRegionGain.SetItemText(itemIndex, columnIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		listCtrlRegionLimit.SetItemText(itemIndex, columnIndex, CString(InspectionParametersConfigReader::GetReader()->SensitivityLevelStringMap[(SensitivityLevels)(itemIndex)].c_str()));
		columnIndex++;
		for (int channelID = 0; channelID < MAX_NUM_OF_COLOR_CHANNELS; channelID++)
		{
			CString tolerance;
			tolerance.Format(_T("%d"), InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].tolerance[channelID].L());
			listCtrlRegionTolerance.SetItemText(itemIndex, columnIndex, tolerance);


			CString gain;
			gain.Format(_T("%0.1f"), InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].gain[channelID].D());
			listCtrlRegionGain.SetItemText(itemIndex, columnIndex, gain);

			CString limit;
			limit.Format(_T("%d"), InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].limit[channelID].L());
			listCtrlRegionLimit.SetItemText(itemIndex, columnIndex, limit);

			columnIndex++;
		}
		itemIndex++;
	}

	itemIndex = 0;
	for (auto &e : InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup)
	{
		itemIndex = listCtrlBlobParameters.InsertItem(itemIndex, _T("*"));
		listCtrlBlobParameters.SetItemData(itemIndex, itemIndex);
		int columnIndex = 1;
		//listCtrlBlobParameters.SetItemText(itemIndex, columnIndex, _T("*"));

		listCtrlBlobParameters.SetCellImage(itemIndex, columnIndex, (int)itemIndex);
		columnIndex++;

		CString globalTolerance;
		globalTolerance.Format(_T("%d"), e.globalTolerance);
		listCtrlBlobParameters.SetItemText(itemIndex, columnIndex, globalTolerance);
		columnIndex++;
		CString majorBlobThreshold;
		majorBlobThreshold.Format(_T("%d"), e.majorBlobThreshold);
		listCtrlBlobParameters.SetItemText(itemIndex, columnIndex, majorBlobThreshold);
		columnIndex++;
		CString dominantBlobThreshold;
		dominantBlobThreshold.Format(_T("%d"), e.dominantBlobThreshold);
		listCtrlBlobParameters.SetItemText(itemIndex, columnIndex, dominantBlobThreshold);
		columnIndex++;
		CString groupOfBlobThreshold;
		groupOfBlobThreshold.Format(_T("%d"), e.groupOfBlobThreshold);
		listCtrlBlobParameters.SetItemText(itemIndex, columnIndex, groupOfBlobThreshold);
		columnIndex++;
		itemIndex++;
	}
}

void InspectionParametersSettingsDialog::UpdateParametersFromList()
{
	int itemIndex = 0;
	for (auto &e : InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup)
	{
		InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].tolerance.Clear();
		InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].gain.Clear();
		InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].limit.Clear();
		int columnIndex = 2;
		for (int channelID = 0; channelID < MAX_NUM_OF_COLOR_CHANNELS; channelID++)
		{
			InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].tolerance = InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].tolerance.Append(_wtoi(listCtrlRegionTolerance.GetItemText(itemIndex, columnIndex)));
			InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].gain = InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].gain.Append(_wtof(listCtrlRegionGain.GetItemText(itemIndex, columnIndex)));
			InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].limit = InspectionParametersConfigReader::GetReader()->parametersLookup.sensitivityLevelParameterLookup[itemIndex].limit.Append(_wtoi(listCtrlRegionLimit.GetItemText(itemIndex, columnIndex)));
			columnIndex++;
		}
		itemIndex++;
	}

	itemIndex = 0;
	for (auto &e : InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup)
	{
		int columnIndex = 2;
		InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[itemIndex].globalTolerance = _wtoi(listCtrlBlobParameters.GetItemText(itemIndex, columnIndex));
		columnIndex++;
		InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[itemIndex].majorBlobThreshold = _wtoi(listCtrlBlobParameters.GetItemText(itemIndex, columnIndex));
		columnIndex++;
		InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[itemIndex].dominantBlobThreshold = _wtoi(listCtrlBlobParameters.GetItemText(itemIndex, columnIndex));
		columnIndex++;
		InspectionParametersConfigReader::GetReader()->parametersLookup.blobParameterLookup[itemIndex].groupOfBlobThreshold = _wtoi(listCtrlBlobParameters.GetItemText(itemIndex, columnIndex));
		itemIndex++;
	}
}

void InspectionParametersSettingsDialog::OnBnClickedMfcbuttonOkay()
{
	// TODO: Add your control notification handler code here
	if (isModified && IDYES == MessageBoxA(this->GetSafeHwnd(), "Do you want to Save the changes?", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_YESNO | MB_TOPMOST))
	{
		UpdateParametersFromList();
		InspectionParametersConfigReader::GetReader()->WriteConfiguration();
	}
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


void InspectionParametersSettingsDialog::OnBnClickedMfcbuttonClose()
{
	// TODO: Add your control notification handler code here
	if (isModified && IDNO == MessageBoxA(this->GetSafeHwnd(), "Do you want to Discard the changes?", "OptiCheck - Intaglio Inspection", MB_ICONWARNING | MB_YESNO | MB_TOPMOST))
	{
			return;
	}
	this->PostMessageW(WM_CLOSE, NULL, NULL);
}


void InspectionParametersSettingsDialog::OnLvnEndlabeleditAnyParameter(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	isModified = true;
}


BOOL InspectionParametersSettingsDialog::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(DialogBackgroundColor);    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);    // restore old brush
	return bRes;                       // CDialog::OnEraseBkgnd(pDC);
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH InspectionParametersSettingsDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
