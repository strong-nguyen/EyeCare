#pragma once


class EyeCareSetting
{
public:
	EyeCareSetting(int breakTimeMinute = 0, BOOL isAutoStart = FALSE);

	int GetBreakTimeMinute() const;

	BOOL IsAutoStart() const;

private:
	int m_breakTimeMinute;

	BOOL m_isAutoStart;
};

