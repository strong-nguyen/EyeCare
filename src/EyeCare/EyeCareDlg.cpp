
// EyeCareDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EyeCare.h"
#include "EyeCareDlg.h"
#include "afxdialogex.h"
#include "MessageDefine.h"
#include "Common.h"

#include <memory>
#include <thread>
#include <PipeClient.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEyeCareDlg dialog

CEyeCareDlg::CEyeCareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EYEBREAK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EYECARE);
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
	ON_MESSAGE(WM_EYEBREAK_SYSTEM_TRAY, &CEyeCareDlg::OnSystemTrayCallback)
	ON_MESSAGE(WM_EYEBREAK_MENU, &CEyeCareDlg::OnClickEyeBreakMenu)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEyeCareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
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
	DestroyWindow();
}

void CEyeCareDlg::ShowSettingDlg()
{
	if (PipeClient client; client.Connect(L"EyeCareUIPipe"))
	{
		client.Notify("showSettingWindow");
	}
}

void CEyeCareDlg::ShowCountdownDlg()
{
	if (PipeClient client; client.Connect(L"EyeCareUIPipe"))
	{
		client.Notify("showCountdownWindow");
	}
}

void CEyeCareDlg::ShowAboutDlg()
{
	if (PipeClient client; client.Connect(L"EyeCareUIPipe"))
	{
		client.Notify("showAboutWindow");
	}
}

void CEyeCareDlg::OnClose()
{
	ShowWindow(SW_HIDE);
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
		ShowCountdownDlg();
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

void CEyeCareDlg::ShowSystemTrayMenu(const POINT& startPoint)
{
	SetForegroundWindow();

	HMENU menu = ::CreatePopupMenu();

	AppendMenu(menu, MF_STRING, MIT_SHOW_EYEBREAK, L"Take A Break");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_SETTING, L"Setting");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_ABOUT, L"About");
	AppendMenu(menu, MF_STRING, MIT_EYEBREAK_QUIT, L"Quit");

	int ret = TrackPopupMenuEx(menu, TPM_CENTERALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, startPoint.x, startPoint.y, GetSafeHwnd(), nullptr);

	PostMessageW(WM_EYEBREAK_MENU, ret, 0);
}
