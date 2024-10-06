#pragma once
#include "afxdialogex.h"
#include "EyeCareSetting.h"


// EyeCareSettingDlg dialog

class EyeCareSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EyeCareSettingDlg)

public:
	EyeCareSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EyeCareSettingDlg();

	EyeCareSetting GetSetting() const;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EYECARE_SETTING_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	EyeCareSetting m_setting;
};
