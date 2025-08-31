
// EyeCare.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "EyeCare.h"
#include "EyeCareDlg.h"
#include "AppDataManager.h"
#include <Logger.h>
#include <PipeServer.h>
#include <PipeClient.h>
#include "UIProcessManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEyeCareApp

BEGIN_MESSAGE_MAP(CEyeCareApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CommonLib::Logger CommonLib::log;

// CEyeCareApp construction

CEyeCareApp::CEyeCareApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CEyeCareApp object

CEyeCareApp theApp;

static void Log(const std::wstring& tag, const std::wstring& msg)
{
	CommonLib::log(tag).Error(msg.c_str());
}


// CEyeCareApp initialization

BOOL CEyeCareApp::InitInstance()
{
	CWinApp::InitInstance();

	HANDLE appEvent = ::CreateEventW(nullptr, FALSE, TRUE, L"TakeABreakApp");
	if (appEvent != nullptr && ::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// Block multiple instances of process
		::CloseHandle(appEvent);
		return FALSE;
	}

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// Initialize app data
	AppDataManager::GetInstance();

	// Initialize logger
	CommonLib::LoggerBuilder builder;
	builder.SetRootPath(AppDataManager::GetInstance()->GetAppDataPath());
	CommonLib::log = builder.BuildLogger();

	PipeClient::SetLoggerInterface(&Log);

	UIProcessManager::GetInstance()->StartUIProcess();

	CEyeCareDlg dlg;
	if (dlg.Create(IDD_EYEBREAK_DIALOG))
	{
		dlg.ShowWindow(SW_HIDE);
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.RunModalLoop();
	}

	UIProcessManager::GetInstance()->StopUIProcess();

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	::CloseHandle(appEvent);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CEyeCareApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

