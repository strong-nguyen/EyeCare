#pragma once

#include "IPipe.h"


// PipeServer -> used in process that creates the Pipe
class __declspec(dllexport) PipeServer : public IPipe
{
public:
	PipeServer(const std::wstring& pipeName);

	void Start();

private:
	std::wstring m_pipeName;
};

