#include "pch.h"
#include "EyeCareSetting.h"

EyeCareSetting::EyeCareSetting(int breakTimeMinute /*= 0*/, BOOL isAutoStart /*= FALSE*/)
	: m_breakTimeMinute(breakTimeMinute), m_isAutoStart(isAutoStart)
{
}

int EyeCareSetting::GetBreakTimeMinute() const
{
	return m_breakTimeMinute;
}

BOOL EyeCareSetting::IsAutoStart() const
{
	return m_isAutoStart;
}
