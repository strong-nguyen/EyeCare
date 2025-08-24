#include "pch.h"
#include "PipeClient.h"
#include <iostream>


bool PipeClient::Connect(const std::wstring& pipeServerName)
{
	std::wstring pipeName = std::format(L"\\\\.\\pipe\\{}", pipeServerName);
	m_pipe = CreateFile(
		pipeName.c_str(),               // pipe name
		GENERIC_WRITE,          // write access
		0,                      // no sharing
		NULL,                   // default security attributes
		OPEN_EXISTING,          // opens existing pipe
		0,                      // default attributes
		NULL);                  // no template file

	if (m_pipe == INVALID_HANDLE_VALUE) {
		Log(std::format(L"Failed to connect to pipe. Error: {}", GetLastError()).c_str());
		return false;
	}

	return true;
}

bool PipeClient::Notify(const std::string& message)
{
	DWORD dwWritten = 0;
	BOOL success = WriteFile(
		m_pipe,                  // pipe handle
		message.c_str(),                // message
		message.size(),        // message length
		&dwWritten,             // bytes written
		NULL);                  // not overlapped

	FlushFileBuffers(m_pipe);

	if (!success) {
		Log(std::format(L"Failed to write to pipe.Error: {}", GetLastError()).c_str());
		return false;
	}
	else {
		return true;
	}
}

PipeClient::~PipeClient()
{
	if (m_pipe)
	{
		CloseHandle(m_pipe);
	}
}