#include "pch.h"
#include "AppState.h"
#include <format>


AppState::AppState()
	:
	AppState(WorkingMode::Working, 0)
{

}

AppState::AppState(WorkingMode mode_, long remainTimeSeconds_)
	:
	mode(mode_),
	remainTimeSeconds(remainTimeSeconds_)
{

}

std::wstring AppState::GetAppStatus() const
{
	if (mode == WorkingMode::Working)
	{
		return std::format(L"Take a break in {} seconds", remainTimeSeconds);
	}
	else
	{
		return std::format(L"Continue working in {} seconds", remainTimeSeconds);
	}
}
