// EyeCareSettingDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "EyeCareSettingDlg.h"
#include "resource.h"
#include "MessageDefine.h"
#include "SettingManager.h"


// EyeCareSettingDlg dialog

IMPLEMENT_DYNAMIC(EyeCareSettingDlg, CDialogEx)

EyeCareSettingDlg::EyeCareSettingDlg(CWnd* pParent /*=nullptr*/)
	:
	CDialogEx(IDD_EYECARE_SETTING_DLG, pParent),
	m_setting(kDefaultEyeCareTimer, kDefaultRelaxTimer, TRUE)
{
	SettingManager::GetInstance()->LoadSetting(m_setting);
}

EyeCareSettingDlg::~EyeCareSettingDlg()
{
}

EyeCareSetting EyeCareSettingDlg::GetSetting() const
{
	return m_setting;
}

void EyeCareSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_BREAK_TIME_EDIT, m_setting.m_breakTimeMinute);
	DDX_Text(pDX, IDC_RELAX_TIME_EDIT, m_setting.m_relaxTimeMinute);
	DDX_Check(pDX, IDC_AUTOSTART_CHECKBOX, m_setting.m_isAutoStart);
}

BOOL EyeCareSettingDlg::OnInitDialog()
{
	UpdateData(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(EyeCareSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EyeCareSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EyeCareSettingDlg message handlers


void EyeCareSettingDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	SettingManager::GetInstance()->SaveSetting(m_setting);
}
