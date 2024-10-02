// EyeCareSettingDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "EyeCareSettingDlg.h"
#include "resource.h"


// EyeCareSettingDlg dialog

IMPLEMENT_DYNAMIC(EyeCareSettingDlg, CDialogEx)

EyeCareSettingDlg::EyeCareSettingDlg(CWnd* pParent /*=nullptr*/)
	:
	CDialogEx(IDD_EYECARE_SETTING_DLG, pParent),
	m_breakTimeMinute(0),
	m_isAutoStartChecked(FALSE)
{

}

EyeCareSettingDlg::~EyeCareSettingDlg()
{
}

EyeCareSetting EyeCareSettingDlg::GetSetting() const
{
	return EyeCareSetting(m_breakTimeMinute, m_isAutoStartChecked);
}

void EyeCareSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_BREAK_TIME_EDIT, m_breakTimeMinute);
	DDX_Check(pDX, IDC_AUTOSTART_CHECKBOX, m_isAutoStartChecked);
}


BEGIN_MESSAGE_MAP(EyeCareSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EyeCareSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EyeCareSettingDlg message handlers


void EyeCareSettingDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
