#include "pch.h"
#include "IPipe.h"


void IPipe::SetLoggerInterface(LoggerCallback logger)
{
	_logger = logger;
}

void IPipe::Log(const std::wstring& msg)
{
	if (_logger)
	{
		_logger(L"Pipe", msg);
	}
}

