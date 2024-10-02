#include "pch.h"
#include "SystemTrayNoti.h"
#include "resource.h"


SystemTrayNoti::SystemTrayNoti()
	:
	m_listenWnd(nullptr),
	m_callbackMessage(0)
{

}

void SystemTrayNoti::Setup(HWND listenWnd, UINT callbackMessage)
{
	m_listenWnd = listenWnd;
	m_callbackMessage = callbackMessage;
}

BOOL SystemTrayNoti::SendStartNoti()
{
	NOTIFYICONDATAW trayNotifyData;
	ZeroMemory(&trayNotifyData, sizeof(NOTIFYICONDATAW));
	trayNotifyData.cbSize = sizeof(NOTIFYICONDATAW);
	trayNotifyData.uID = 100;
	trayNotifyData.hWnd = m_listenWnd;
	trayNotifyData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	trayNotifyData.uCallbackMessage = m_callbackMessage;

	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	HICON icon = ::LoadIconW(hInstance, MAKEINTRESOURCE(IDI_ICON_EYECARE));
	trayNotifyData.hIcon = icon;
	trayNotifyData.uVersion = NOTIFYICON_VERSION_4;

	wmemcpy(trayNotifyData.szTip, L"EyeBreak is running", 20);

	BOOL ret = ::Shell_NotifyIconW(NIM_ADD, &trayNotifyData);
	::Shell_NotifyIconW(NIM_SETVERSION, &trayNotifyData);

	return ret;
}

BOOL SystemTrayNoti::SendCloseNoti()
{
	NOTIFYICONDATAW trayNotifyData;
	ZeroMemory(&trayNotifyData, sizeof(NOTIFYICONDATAW));
	trayNotifyData.cbSize = sizeof(NOTIFYICONDATAW);
	trayNotifyData.uID = 100;
	trayNotifyData.hWnd = m_listenWnd;

	Shell_NotifyIconW(NIM_DELETE, &trayNotifyData);
	return TRUE;
}
