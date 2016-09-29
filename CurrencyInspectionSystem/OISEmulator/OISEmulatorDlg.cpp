
// OISEmulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OISEmulator.h"
#include "OISEmulatorDlg.h"
#include "afxdialogex.h"
#include <bitset>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COISEmulatorDlg dialog



COISEmulatorDlg::COISEmulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OISEMULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COISEmulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_PREPARATIONCOMPLETED, buttonPreparationCompleted);
	DDX_Control(pDX, IDC_MFCBUTTON_INSPECTIONAVAILABLE, buttonInspectionAvailable);
	DDX_Control(pDX, IDC_MFCBUTTON_ABNORMALSTATE, buttonSystemAbnormal);
	DDX_Control(pDX, IDC_MFCBUTTON_TOWERLAMPBLUE, buttonTowerLampBlue);
	DDX_Control(pDX, IDC_MFCBUTTON_TOWERLAMPYELLOW, buttonTowerLampYellow);
	DDX_Control(pDX, IDC_MFCBUTTON_TOWERLAMPRED, buttonTowerLampRed);
	DDX_Control(pDX, IDC_EDIT_LOGS, logViewer);
	DDX_Control(pDX, IDC_STATIC_MACHINE_STATE, staticMachineState);
	DDX_Control(pDX, IDC_STATIC_INSPECTION_STATE, staticInspectionState);
	DDX_Control(pDX, IDC_SPIN4, spinRGBLight1);
	DDX_Control(pDX, IDC_SPIN5, spinRGBLight2);
	DDX_Control(pDX, IDC_SPIN2, spinIRLight1);
	DDX_Control(pDX, IDC_SPIN3, spinIRLight2);
	DDX_Control(pDX, IDC_EDIT_RGB_LIGHT1, editRGBValue1);
	DDX_Control(pDX, IDC_EDIT_RGB_LIGHT2, editRGBValue2);
	DDX_Control(pDX, IDC_EDIT_IR_LIGHT1, editIRValue1);
	DDX_Control(pDX, IDC_EDIT_IR_LIGHT2, editIRValue2);
}


BOOL COISEmulatorDlg::PreTranslateMessage(MSG *pMsg)
{
	BOOL bRet;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		bRet = TRUE; // do not dispatch message
	}
	else
	{
		bRet = CDialog::PreTranslateMessage(pMsg);
	}

	return bRet;
}


BEGIN_MESSAGE_MAP(COISEmulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON_PREPARATIONCOMPLETED, &COISEmulatorDlg::OnBnClickedMfcbuttonPreparationcompleted)
	ON_BN_CLICKED(IDC_MFCBUTTON_INSPECTIONAVAILABLE, &COISEmulatorDlg::OnBnClickedMfcbuttonInspectionavailable)
	ON_BN_CLICKED(IDC_MFCBUTTON_ABNORMALSTATE, &COISEmulatorDlg::OnBnClickedMfcbuttonAbnormalstate)
	ON_BN_CLICKED(IDC_MFCBUTTON_TOWERLAMPBLUE, &COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampblue)
	ON_BN_CLICKED(IDC_MFCBUTTON_TOWERLAMPYELLOW, &COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampyellow)
	ON_BN_CLICKED(IDC_MFCBUTTON_TOWERLAMPRED, &COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampred)
	ON_BN_CLICKED(IDC_BUTTON1, &COISEmulatorDlg::OnBnClickedSetRGBLight1)
	ON_BN_CLICKED(IDC_BUTTON2, &COISEmulatorDlg::OnBnClickedSetRGBLight2)
	ON_BN_CLICKED(IDC_BUTTON4, &COISEmulatorDlg::OnBnClickedIRLight1)
	ON_BN_CLICKED(IDC_BUTTON3, &COISEmulatorDlg::OnBnClickedIRLight2)
END_MESSAGE_MAP()


// COISEmulatorDlg message handlers

BOOL COISEmulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	isPreparationCompleted = false;
	isInspectionAvailable = false;
	isSystemAbnormal = false;
	isTowerLampBlue = false;
	isTowerLampYellow = false;
	isTowerLampRed = false;

	buttonPreparationCompleted.SetIcon(AfxGetApp()->LoadIconW(isPreparationCompleted? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
	buttonInspectionAvailable .SetIcon(AfxGetApp()->LoadIconW(isInspectionAvailable ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
	buttonSystemAbnormal      .SetIcon(AfxGetApp()->LoadIconW(isSystemAbnormal ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
	buttonTowerLampBlue       .SetIcon(AfxGetApp()->LoadIconW(isTowerLampBlue ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
	buttonTowerLampYellow     .SetIcon(AfxGetApp()->LoadIconW(isTowerLampYellow ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
	buttonTowerLampRed        .SetIcon(AfxGetApp()->LoadIconW(isTowerLampRed ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));

	MachineCommunicator::GetInstance()->AddEjectorSignalListener(this);
	MachineCommunicator::GetInstance()->AddImageTriggerListener(this);
	MachineCommunicator::GetInstance()->AddMachineStateStatusChangeListener(this);
	MachineCommunicator::GetInstance()->AddStartInspectionStatusChangeListener(this);
	imageNumber = 0;
	ejectorCount = 0;

	spinRGBLight1.SetRange(0, 100);
	spinRGBLight2.SetRange(0, 100);
	spinIRLight1.SetRange(0, 100);
	spinIRLight2.SetRange(0, 100);

	font.CreateFont(22, 0, 0, 0, FW_HEAVY, false, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Courier New"));


	editRGBValue1.SetFont(&font);
	editRGBValue2.SetFont(&font);
	editIRValue1.SetFont(&font);
	editIRValue2.SetFont(&font);


	editRGBValue1.SetWindowTextW(_T("40"));
	editRGBValue2.SetWindowTextW(_T("40"));
	editIRValue1.SetWindowTextW(_T("40"));
	editIRValue2.SetWindowTextW(_T("40"));

	try
	{
		MachineCommunicator::GetInstance()->SetPreparationCompletedSignal(isPreparationCompleted);
		MachineCommunicator::GetInstance()->SetInspectionAvailableSignal(isInspectionAvailable);
		MachineCommunicator::GetInstance()->SetSystemAbnormalSignal(isSystemAbnormal);
		MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(isTowerLampBlue);
		MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(isTowerLampYellow);
		MachineCommunicator::GetInstance()->SetTowerLampRedSignal(isTowerLampRed);

		machineState = MachineCommunicator::GetInstance()->GetMachineState();
		inspectionState = MachineCommunicator::GetInstance()->GetStartInspectionSignalState();
	}
	catch (exception &ex)
	{
		MessageBox(_T("Failed to Access Digital IO; Check Configuration File and Hardware"));
	}
	CString log;

	log.Format(_T("Machine State : %S"), machineState ? "High" : "Low");
	AppendLog(log);
	staticMachineState.SetWindowTextW(machineState ? _T("High") : _T("Low"));

	log.Format(_T("Start Inspection Signal State: %S"), inspectionState ? "High" : "Low");
	AppendLog(log);
	staticInspectionState.SetWindowTextW(inspectionState ? _T("High") : _T("Low"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COISEmulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COISEmulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COISEmulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COISEmulatorDlg::OnBnClickedMfcbuttonPreparationcompleted()
{
	// TODO: Add your control notification handler code here
	isPreparationCompleted = !isPreparationCompleted;
	if (MachineCommunicator::GetInstance()->SetPreparationCompletedSignal(isPreparationCompleted))
	{
		buttonPreparationCompleted.SetIcon(AfxGetApp()->LoadIconW(isPreparationCompleted ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("Preparation Completed Signal State Changed; State: %d"), isPreparationCompleted);
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isPreparationCompleted = !isPreparationCompleted;
		CString log;
		log.Format(_T("Preparation Completed Signal State Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedMfcbuttonInspectionavailable()
{
	// TODO: Add your control notification handler code here
	isInspectionAvailable = !isInspectionAvailable;
	if (MachineCommunicator::GetInstance()->SetInspectionAvailableSignal(isInspectionAvailable))
	{
		buttonInspectionAvailable.SetIcon(AfxGetApp()->LoadIconW(isInspectionAvailable ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("Inspection Available Signal State Changed; State: %d"), isInspectionAvailable);
		AppendLog(log);
		imageNumber = 0;
		ejectorCount = 0;
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isInspectionAvailable = !isInspectionAvailable;
		CString log;
		log.Format(_T("Inspection Available Signal State Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedMfcbuttonAbnormalstate()
{
	// TODO: Add your control notification handler code here
	isSystemAbnormal = !isSystemAbnormal;
	if (MachineCommunicator::GetInstance()->SetSystemAbnormalSignal(isSystemAbnormal))
	{
		buttonSystemAbnormal.SetIcon(AfxGetApp()->LoadIconW(isSystemAbnormal ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("System Abnormal Signal State Changed; State: %d"), isSystemAbnormal);
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isSystemAbnormal = !isSystemAbnormal;
		CString log;
		log.Format(_T("System Abnormal Signal State Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampblue()
{
	// TODO: Add your control notification handler code here
	isTowerLampBlue = !isTowerLampBlue;
	if (MachineCommunicator::GetInstance()->SetTowerLampBlueSignal(isTowerLampBlue))
	{
		buttonTowerLampBlue.SetIcon(AfxGetApp()->LoadIconW(isTowerLampBlue ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("Tower Lamp Blue State Changed; State: %d"), isTowerLampBlue);
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isTowerLampBlue = !isTowerLampBlue;
		CString log;
		log.Format(_T("Tower Lamp Blue State Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampyellow()
{
	// TODO: Add your control notification handler code here
	isTowerLampYellow = !isTowerLampYellow;
	if (MachineCommunicator::GetInstance()->SetTowerLampYellowSignal(isTowerLampYellow))
	{
		buttonTowerLampYellow.SetIcon(AfxGetApp()->LoadIconW(isTowerLampYellow ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("Tower Lamp Yellow State Changed; State: %d"), isTowerLampYellow);
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isTowerLampYellow = !isTowerLampYellow;
		CString log;
		log.Format(_T("Tower Lamp Yellow State Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedMfcbuttonTowerlampred()
{
	// TODO: Add your control notification handler code here
	isTowerLampRed = !isTowerLampRed;
	if (MachineCommunicator::GetInstance()->SetTowerLampRedSignal(isTowerLampRed))
	{
		buttonTowerLampRed.SetIcon(AfxGetApp()->LoadIconW(isTowerLampRed ? IDI_ICON_CHECK : IDI_ICON_UNCHECK));
		CString log;
		log.Format(_T("Tower Lamp Red State Changed; State: %d"), isTowerLampRed);
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change the State"));
		isTowerLampRed = !isTowerLampRed;
		CString log;
		log.Format(_T("Tower Lamp Red State Change Failed"));
		AppendLog(log);
	}
}

void COISEmulatorDlg::OnDIONotificationReceived(SignalName dioSignalName)
{
	long encoderCount;
	CString log;
	switch (dioSignalName)
	{
	case DebouncedImageTrigger:
		imageNumber++;
		encoderCount = MachineCommunicator::GetInstance()->GetEncoderCount();
		log.Format(_T("Image Trigger Received; Image Number: %d"), imageNumber);
		AppendLog(log);
		log.Format(_T("Encoder Count: %d"), encoderCount);
		AppendLog(log);
		break;
	case MachineStateSignal:
		machineState = MachineCommunicator::GetInstance()->GetMachineState();
		log.Format(_T("Machine State Changed; State: %S"), machineState? "High" : "Low");
		AppendLog(log);
		staticMachineState.SetWindowTextW(machineState ? _T("High") : _T("Low"));
		break;
	case StartInspectionSignal:
		inspectionState = MachineCommunicator::GetInstance()->GetStartInspectionSignalState();
		log.Format(_T("Start Inspection Signal State Changed; State: %S"), inspectionState ? "High" : "Low");		
		AppendLog(log);
		staticInspectionState.SetWindowTextW(inspectionState ? _T("High") : _T("Low"));
		break;
	case EjectorSensorEvent:
		ejectorCount++;
		encoderCount = MachineCommunicator::GetInstance()->GetEncoderCount();
		log.Format(_T("Ejector Trigger Received; Image Number: %d"), ejectorCount);
		AppendLog(log);
		log.Format(_T("Encoder Count: %d"), encoderCount);
		AppendLog(log);
		MachineCommunicator::GetInstance()->ResetEncoderCount();
		break;
	default:
		break;
	}
}


void COISEmulatorDlg::AppendLog(CString _log)
{
	CString logText;
	logViewer.GetWindowTextW(logText);
	logText.Format(_T("%s\r\n%s"), logText, _log);
	logViewer.SetWindowTextW(logText);
}

void COISEmulatorDlg::OnBnClickedSetRGBLight1()
{
	// TODO: Add your control notification handler code here
	CString text;
	editRGBValue1.GetWindowTextW(text);

	if (MachineCommunicator::GetInstance()->SetLightStickIntensityPercentage(0, _wtoi(text.GetBuffer())))
	{
		CString log;
		log.Format(_T("RGB Light1 Intensity Changed; New Value: %d"), _wtoi(text.GetBuffer()));
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change RGB Light1 Intensity"));
		CString log;
		log.Format(_T("RGB Light1 Intensity Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedSetRGBLight2()
{
	// TODO: Add your control notification handler code here
	CString text;
	editRGBValue2.GetWindowTextW(text);

	if (MachineCommunicator::GetInstance()->SetLightStickIntensityPercentage(1, _wtoi(text.GetBuffer())))
	{
		CString log;
		log.Format(_T("RGB Light2 Intensity Changed; New Value: %d"), _wtoi(text.GetBuffer()));
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change RGB Light1 Intensity"));
		CString log;
		log.Format(_T("RGB Light2 Intensity Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedIRLight1()
{
	// TODO: Add your control notification handler code here
	CString text;
	editIRValue1.GetWindowTextW(text);


	if (MachineCommunicator::GetInstance()->SetLightStickIntensityPercentage(2, _wtoi(text.GetBuffer())))
	{
		CString log;
		log.Format(_T("IR Light1 Intensity Changed; New Value: %d"), _wtoi(text.GetBuffer()));
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change IR Light1 Intensity"));
		CString log;
		log.Format(_T("IR Light1 Intensity Change Failed"));
		AppendLog(log);
	}
}


void COISEmulatorDlg::OnBnClickedIRLight2()
{
	// TODO: Add your control notification handler code here
	CString text;
	editIRValue2.GetWindowTextW(text);
	if (MachineCommunicator::GetInstance()->SetLightStickIntensityPercentage(3, _wtoi(text.GetBuffer())))
	{
		CString log;
		log.Format(_T("IR Light2 Intensity Changed; New Value: %d"), _wtoi(text.GetBuffer()));
		AppendLog(log);
	}
	else
	{
		MessageBox(_T("Failed to Set Change IR Light2 Intensity"));
		CString log;
		log.Format(_T("IR Light2 Intensity Change Failed"));
		AppendLog(log);
	}
}
