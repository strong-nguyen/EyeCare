
// EyeCareDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EyeCare.h"
#include "EyeCareDlg.h"
#include "afxdialogex.h"
#include "MessageDefine.h"
#include "EyeCareSettingDlg.h"
#include "SettingManager.h"
#include "Common.h"

#include <memory>
#include <thread>

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


// CEyeCareDlg dialog

CEyeCareDlg::CEyeCareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EYEBREAK_DIALOG, pParent)
	, m_appSetting(SettingManager::GetInstance()->GetSetting())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EYECARE);
	m_relaxTime = m_appSetting->GetRelaxTimeMilliSecond() / 1000;
	m_appState = AppState{ WorkingMode::Working, m_appSetting->GetBreakTimeMilliSecond() / 1000 };
}

void CEyeCareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_RELAX_COUNTDOWN_STATIC, m_countdownTime);
}

BEGIN_MESSAGE_MAP(CEyeCareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONTINUE_WORKING, &CEyeCareDlg::OnBnClickedContinueWorking)
	ON_MESSAGE(WM_EYEBREAK_SYSTEM_TRAY, &CEyeCareDlg::OnSystemTrayCallback)
	ON_MESSAGE(WM_EYEBREAK_MENU, &CEyeCareDlg::OnClickEyeBreakMenu)
	ON_MESSAGE(WM_EYECARE_SETTING_APPLY, &CEyeCareDlg::OnApplySetting)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CEyeCareDlg message handlers

BOOL CEyeCareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_trayNoti.Setup(GetSafeHwnd(), WM_EYEBREAK_SYSTEM_TRAY);
	m_trayNoti.SendStartNoti();

	SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
	SetTimer(EYECARE_APP_STATE_COUNTDONW_TIMER, 1000, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEyeCareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEyeCareDlg::OnPaint()
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
HCURSOR CEyeCareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CEyeCareDlg::OnSystemTrayCallback(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case NIN_SELECT:
		// Left click on system tray
		break;
	case WM_CONTEXTMENU:
	{
		// Right click on system tray
		POINT const pt = { LOWORD(wParam), HIWORD(wParam) };
		ShowSystemTrayMenu(pt);
		break;
	}
	case WM_MOUSEMOVE:
	{
		// Hover on system tray
		//m_trayNoti.SendStatusNoti(m_appState.GetAppStatus());
		break;
	}
	}
	return TRUE;
}

void CEyeCareDlg::QuitEyeCare()
{
	m_trayNoti.SendCloseNoti();
	BOOL ret = KillTimer(EYECARE_DISPLAY_TIMER);
	KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	DestroyWindow();
}

void CEyeCareDlg::ShowSettingDlg()
{
	EyeCareSettingDlg dlg;
	INT_PTR response = dlg.DoModal();

	if (response == IDOK)
	{
		EyeCareSetting* setting = new EyeCareSetting(dlg.GetSetting());
		PostMessageW(WM_EYECARE_SETTING_APPLY, (WPARAM)setting, 0);
	}
}

void CEyeCareDlg::ShowFullScreenTopMost()
{
	int screenWidth = ::GetSystemMetrics(SM_CXMAXIMIZED);
	int screenHeight = ::GetSystemMetrics(SM_CYMAXIMIZED);

	RECT rect{};
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &rect, 0);

#ifdef _DEBUG
	HWND hWndInsertAfter = HWND_TOP;
#else
	HWND hWndInsertAfter = HWND_TOPMOST;
#endif
	::SetWindowPos(GetSafeHwnd(), hWndInsertAfter, 0, 0, rect.right, rect.bottom, SWP_SHOWWINDOW);  // Show window as top-most

	KillTimer(EYECARE_DISPLAY_TIMER);
	KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	SetTimer(EYECARE_RELAX_COUNTDONW_TIMER, 1000, nullptr);
}

void CEyeCareDlg::ShowAboutDlg()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CEyeCareDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

void CEyeCareDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == EYECARE_DISPLAY_TIMER)
	{
		m_appState = { WorkingMode::Relax, m_appSetting->GetRelaxTimeMilliSecond() / 1000 };
		ShowFullScreenTopMost();
	}
	else if (nIDEvent == EYECARE_RELAX_COUNTDONW_TIMER)
	{
		--m_relaxTime;
		m_countdownTime.Format(L"Relax time: %s", Common::FormatTime(m_relaxTime).c_str());
		UpdateData(FALSE);

		if (m_relaxTime == 0)
		{
			ShowWindow(SW_HIDE);
			KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
			SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
			m_relaxTime = m_appSetting->GetRelaxTimeMilliSecond() / 1000;  // Reset
			m_appState = { WorkingMode::Working, m_appSetting->GetBreakTimeMilliSecond() / 1000 };
		}
	}
	else if (nIDEvent == EYECARE_APP_STATE_COUNTDONW_TIMER)
	{
		--m_appState.remainTimeSeconds;
	}
}

void CEyeCareDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd* continueWorkingBtn = GetDlgItem(IDC_CONTINUE_WORKING);
	CWnd* countdownText = GetDlgItem(IDC_RELAX_COUNTDOWN_STATIC);
	if (!continueWorkingBtn || !countdownText)
	{
		return;
	}

	// Adapt position of continue working button when dialog size has changed
	CRect rect;
	continueWorkingBtn->GetWindowRect(&rect);
	continueWorkingBtn->SetWindowPos(nullptr, cx / 2, cy / 2, rect.Width(), rect.Height(), SWP_SHOWWINDOW);

	countdownText->GetWindowRect(&rect);
	countdownText->SetWindowPos(nullptr, cx / 2, cy / 2 + 50, rect.Width(), rect.Height(), SWP_SHOWWINDOW);

	return;
}

LRESULT CEyeCareDlg::OnClickEyeBreakMenu(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case MIT_EYEBREAK_QUIT:
		QuitEyeCare();
		break;
	case MIT_SHOW_EYEBREAK:
		m_appState = { WorkingMode::Relax, m_appSetting->GetRelaxTimeMilliSecond() / 1000 };
		ShowFullScreenTopMost();
		break;
	case MIT_EYEBREAK_SETTING:
		ShowSettingDlg();
		break;
	case MIT_EYEBREAK_ABOUT:
		ShowAboutDlg();
		break;
	}

	return TRUE;
}

LRESULT CEyeCareDlg::OnApplySetting(WPARAM wParam, LPARAM lParam)
{
	auto new_setting = std::unique_ptr<EyeCareSetting>(reinterpret_cast<EyeCareSetting*>(wParam));
	if (!new_setting)
	{
		return FALSE;
	}

	KillTimer(EYECARE_DISPLAY_TIMER);  // Kill default timer first
	SetTimer(EYECARE_DISPLAY_TIMER, new_setting->GetBreakTimeMilliSecond(), nullptr);
	m_relaxTime = new_setting->GetRelaxTimeMilliSecond() / 1000;

	return LRESULT();
}

void CEyeCareDlg::OnBnClickedContinueWorking()
{
	ShowWindow(SW_HIDE);
	KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
	m_relaxTime = m_appSetting->GetRelaxTimeMilliSecond() / 1000;  // Reset
	m_appState = { WorkingMode::Working, m_appSetting->GetBreakTimeMilliSecond() / 1000 };

	m_countdownTime = "";
	UpdateData(FALSE);
}

void CEyeCareDlg::ShowSystemTrayMenu(const POINT& startPoint)
{
	SetForegroundWindow();

	HMENU menu = ::CreatePopupMenu();

	AppendMenu(menu, MF_STRING, MIT_SHOW_EYEBREAK, L"Show EyeCare");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_SETTING, L"Setting");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_ABOUT, L"About");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_QUIT, L"Quit");

	int ret = TrackPopupMenuEx(menu, TPM_CENTERALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, startPoint.x, startPoint.y, GetSafeHwnd(), nullptr);

	CStringA log;
	log.Format("menu item: %d\n", ret);
	OutputDebugStringA(log.GetString());

	PostMessageW(WM_EYEBREAK_MENU, ret, 0);
}
