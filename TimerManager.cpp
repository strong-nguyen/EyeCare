#include "pch.h"
#include "TimerManager.h"
#include "MessageDefine.h"
#include "EyeCareSetting.h"
#include "SettingManager.h"

TimerManager::TimerManager(CWnd* mainDlg)
	: m_mainDlg(mainDlg)
	, m_appSetting(SettingManager::GetInstance()->GetSetting())
{
}

void TimerManager::OnStart()
{
	m_mainDlg->SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
	m_mainDlg->SetTimer(EYECARE_APP_STATE_COUNTDONW_TIMER, 1000, nullptr);
}

void TimerManager::OnQuit()
{
	m_mainDlg->KillTimer(EYECARE_DISPLAY_TIMER);
	m_mainDlg->KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	m_mainDlg->KillTimer(EYECARE_APP_STATE_COUNTDONW_TIMER);
}

void TimerManager::OnShowingEyeCare()
{
	m_mainDlg->KillTimer(EYECARE_DISPLAY_TIMER);
	m_mainDlg->KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	m_mainDlg->SetTimer(EYECARE_RELAX_COUNTDONW_TIMER, 1000, nullptr);
}

void TimerManager::OnHideEyeCare()
{
	m_mainDlg->KillTimer(EYECARE_RELAX_COUNTDONW_TIMER);
	m_mainDlg->SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
}

void TimerManager::OnApplyNewSetting()
{
	m_mainDlg->KillTimer(EYECARE_DISPLAY_TIMER);
	m_mainDlg->SetTimer(EYECARE_DISPLAY_TIMER, m_appSetting->GetBreakTimeMilliSecond(), nullptr);
}