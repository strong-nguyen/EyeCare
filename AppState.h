#pragma once

#include <string>

enum class WorkingMode
{
	Working = 0,
	Relax
};

struct AppState
{
	WorkingMode mode;
	long remainTimeSeconds;

	AppState();

	AppState(WorkingMode mode_, long remainTimeSeconds_);

	std::wstring GetAppStatus() const;
};

