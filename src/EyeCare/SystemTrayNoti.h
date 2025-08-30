#pragma once

#include <string>

class SystemTrayNoti
{
public:
	SystemTrayNoti();

	~SystemTrayNoti();

	void Setup(HWND listenWnd, UINT callbackMessage);

	BOOL SendStartNoti();

	BOOL SendCloseNoti();

	BOOL SendStatusNoti(const std::wstring& status);

private:
	HWND m_listenWnd;

	UINT m_callbackMessage;
};