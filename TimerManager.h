#pragma once

class EyeCareSetting;


class TimerManager
{
public:
	TimerManager(CWnd* mainDlg);

	void OnStart();

	void OnQuit();

	void OnShowingEyeCare();

	void OnHideEyeCare();

	void OnApplyNewSetting();

private:
	CWnd* m_mainDlg;

	EyeCareSetting* m_appSetting;
};

