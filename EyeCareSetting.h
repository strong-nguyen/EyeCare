#pragma once



class EyeCareSetting
{
public:
	friend class EyeCareSettingDlg;

	EyeCareSetting(float breakTimeMinute = 0.0f, float relaxTimeMinute = 0.0f, BOOL isAutoStart = FALSE);

	int GetBreakTimeMilliSecond() const;

	int GetRelaxTimeMilliSecond() const;

	BOOL IsAutoStart() const;

private:
	float m_breakTimeMinute;

	float m_relaxTimeMinute;

	BOOL m_isAutoStart;
};

