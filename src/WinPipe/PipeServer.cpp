#include "pch.h"
#include "PipeServer.h"
#include <thread>


PipeServer::PipeServer(const std::wstring& pipeName)
	: 
	m_pipeName(pipeName)
{

}

void PipeServer::Start()
{
	std::wstring pipeName = std::format(L"\\\\.\\pipe\\{}", m_pipeName);
	HANDLE pipeHandle = CreateNamedPipeW(
		pipeName.c_str(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		1,
		1024,  // Out buffer size
		1024,  // In buffer size
		0,  // Default timeout -> default 50 ms
		nullptr);

	if (pipeHandle == INVALID_HANDLE_VALUE)
	{
		Log(std::format(L"Failed to create named pipe, error: {}", ::GetLastError()));
		return;
	}

	std::thread task([this, pipeHandle]()
		{
			BOOL isConnected = ConnectNamedPipe(pipeHandle, nullptr);
			if (!isConnected)
			{
				Log(std::format(L"Failed to connect named pipe, error: {}", ::GetLastError()));
				return;
			}

			while (true)
			{
				char buffer[1024] = {};
				DWORD bytesRead;
				BOOL result = ReadFile(pipeHandle, buffer, sizeof(buffer), &bytesRead, NULL);
				if (!result)
				{
					Log(std::format(L"Failed to read from named pipe, error: {}", ::GetLastError()));
					return;
				}
			}
		});
	task.detach();
}
