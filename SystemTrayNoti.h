#pragma once


class SystemTrayNoti
{
public:
	SystemTrayNoti();

	void Setup(HWND listenWnd, UINT callbackMessage);

	BOOL SendStartNoti();

	BOOL SendCloseNoti();


private:
	HWND m_listenWnd;

	UINT m_callbackMessage;
};