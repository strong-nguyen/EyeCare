#pragma once

#include "IPipe.h"

// PipeClient -> used in process that connects to the Pipe
class __declspec(dllexport) PipeClient : public IPipe
{
public:
	bool Connect(const std::wstring& pipeServerName);

	bool Notify(const std::string& message);

	~PipeClient();

private:
	HANDLE m_pipe = nullptr;
};

