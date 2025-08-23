#pragma once

#include <string>

enum class WorkingMode
{
	Working = 0,
	Relax
};

/*
* The state of EyeCare app.
* It has 2 states: Working -> user is working/ Relax -> user is relaxing
*/
struct AppState
{
	WorkingMode mode;
	long remainTimeSeconds;

	AppState();

	AppState(WorkingMode mode_, long remainTimeSeconds_);

	std::wstring GetAppStatus() const;
};

