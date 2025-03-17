
// EyeBreakDlg.h : header file
//

#pragma once


#include "SystemTrayNoti.h"
#include "AppState.h"


class EyeCareSetting;


// CEyeBreakDlg dialog
class CEyeBreakDlg : public CDialogEx
{
// Construction
public:
	CEyeBreakDlg(CWnd* pParent = nullptr);	// standard constructor

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

	afx_msg void OnClose();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg LRESULT OnClickEyeBreakMenu(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnApplySetting(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedContinueWorking();

private:
	void ShowSystemTrayMenu(const POINT& startPoint);

	void QuitEyeCare();

	void ShowSettingDlg();

	void ShowFullScreenTopMost();

	SystemTrayNoti m_trayNoti;

	CString m_countdownTime;

	int m_relaxTime;

	EyeCareSetting* m_app_setting;

	AppState m_appState;
};
