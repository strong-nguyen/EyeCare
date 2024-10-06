
// EyeBreakDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EyeBreak.h"
#include "EyeBreakDlg.h"
#include "afxdialogex.h"
#include "MessageDefine.h"
#include "EyeCareSettingDlg.h"

#include <memory>

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


// CEyeBreakDlg dialog



CEyeBreakDlg::CEyeBreakDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EYEBREAK_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EYECARE);
}

void CEyeBreakDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEyeBreakDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONTINUE_WORKING, &CEyeBreakDlg::OnBnClickedContinueWorking)
	ON_MESSAGE(WM_EYEBREAK_SYSTEM_TRAY, &CEyeBreakDlg::OnSystemTrayCallback)
	ON_MESSAGE(WM_EYEBREAK_MENU, &CEyeBreakDlg::OnClickEyeBreakMenu)
	ON_MESSAGE(WM_EYECARE_SETTING_APPLY, &CEyeBreakDlg::OnApplySetting)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEyeBreakDlg message handlers

BOOL CEyeBreakDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	m_trayNoti.Setup(GetSafeHwnd(), WM_EYEBREAK_SYSTEM_TRAY);

	m_trayNoti.SendStartNoti();

	SetTimer(EYECARE_DISPLAY_TIMER, kDefaultEyeCareTimer * 60 * 1000, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEyeBreakDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEyeBreakDlg::OnPaint()
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
HCURSOR CEyeBreakDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CEyeBreakDlg::OnSystemTrayCallback(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case NIN_SELECT:
		//MessageBoxW(L"click on system tray", L"Eye Break");
		break;
	case WM_CONTEXTMENU:
	{
		POINT const pt = { LOWORD(wParam), HIWORD(wParam) };
		ShowSystemTrayMenu(pt);
		break;
	}
	}
	return TRUE;
}

void CEyeBreakDlg::ShowEyeBreak()
{
	ShowWindow(SW_SHOW);
}

void CEyeBreakDlg::QuitEyeCare()
{
	BOOL ret = KillTimer(EYECARE_DISPLAY_TIMER);
	DestroyWindow();
}

void CEyeBreakDlg::ShowSettingDlg()
{
	EyeCareSettingDlg dlg;
	INT_PTR response = dlg.DoModal();

	if (response == IDOK)
	{
		EyeCareSetting* setting = new EyeCareSetting(dlg.GetSetting());
		PostMessageW(WM_EYECARE_SETTING_APPLY, (WPARAM)setting, 0);
	}
}

void CEyeBreakDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CEyeBreakDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent != EYECARE_DISPLAY_TIMER)
	{
		return;
	}


	int screenWidth = ::GetSystemMetrics(SM_CXMAXIMIZED);
	int screenHeight = ::GetSystemMetrics(SM_CYMAXIMIZED);
	RECT rect{ 0, 0, screenWidth, screenHeight };
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);  // Show window as top-most
}

LRESULT CEyeBreakDlg::OnClickEyeBreakMenu(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case MIT_EYEBREAK_QUIT:
		QuitEyeCare();
		break;
	case MIT_SHOW_EYEBREAK:
		ShowEyeBreak();
		break;
	case MIT_EYEBREAK_SETTING:
		ShowSettingDlg();
		break;
	}

	return TRUE;
}

LRESULT CEyeBreakDlg::OnApplySetting(WPARAM wParam, LPARAM lParam)
{
	auto new_setting = std::unique_ptr<EyeCareSetting>(reinterpret_cast<EyeCareSetting*>(wParam));
	if (!new_setting)
	{
		return FALSE;
	}

	KillTimer(EYECARE_DISPLAY_TIMER);  // Kill default timer first
	SetTimer(EYECARE_DISPLAY_TIMER, new_setting->GetBreakTimeMilliSecond(), nullptr);

	return LRESULT();
}

void CEyeBreakDlg::OnBnClickedContinueWorking()
{
	ShowWindow(SW_HIDE);
}

void CEyeBreakDlg::ShowSystemTrayMenu(const POINT& startPoint)
{
	SetForegroundWindow();

	HMENU menu = ::CreatePopupMenu();

	AppendMenu(menu, MF_STRING, MIT_SHOW_EYEBREAK, L"Show EyeCare");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_SETTING, L"Setting");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_QUIT, L"Quit");

	int ret = TrackPopupMenuEx(menu, TPM_CENTERALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, startPoint.x, startPoint.y, GetSafeHwnd(), nullptr);

	CStringA log;
	log.Format("menu item: %d\n", ret);
	OutputDebugStringA(log.GetString());

	PostMessageW(WM_EYEBREAK_MENU, ret, 0);
}
