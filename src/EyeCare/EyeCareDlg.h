
// EyeCareDlg.h : header file
//

#pragma once


#include "SystemTrayNoti.h"


class EyeCareSetting;
class TimerManager;


// CEyeCareDlg dialog
class CEyeCareDlg : public CDialogEx
{
// Construction
public:
	CEyeCareDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EYEBREAK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT OnSystemTrayCallback(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnClickEyeCareMenu(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void ShowSystemTrayMenu(const POINT& startPoint);

	void QuitEyeCare();

	void ShowSettingDlg();

	void ShowCountdownDlg();

	void ShowAboutDlg();

	// Manage system tray notification
	SystemTrayNoti m_trayNoti;
};
