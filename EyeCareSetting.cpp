#include "pch.h"
#include "EyeCareSetting.h"

EyeCareSetting::EyeCareSetting(float breakTimeMinute /*= 0.0f*/, float relaxTimeMinute /*= 0.0f*/, BOOL isAutoStart /*= FALSE*/)
	:
	m_breakTimeMinute(breakTimeMinute),
	m_relaxTimeMinute(relaxTimeMinute),
	m_isAutoStart(isAutoStart)
{
}

int EyeCareSetting::GetBreakTimeMilliSecond() const
{
	return round(m_breakTimeMinute * 60 * 1000);
}

int EyeCareSetting::GetRelaxTimeMilliSecond() const
{
	return round(m_relaxTimeMinute * 60 * 1000);
}

BOOL EyeCareSetting::IsAutoStart() const
{
	return m_isAutoStart;
}
