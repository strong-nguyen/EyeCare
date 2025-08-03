#include "pch.h"
#include "Logger.h"

#include <format>
#include <ctime>
#include <fstream>

#pragma warning(disable : 4996)

namespace CommonLib
{
	std::map<Logger::LogLevel, std::wstring> Logger::s_logLevelMap
	{
		{Logger::LogLevel::Error, L"Error"},
		{Logger::LogLevel::Warn, L"Warn"},
		{Logger::LogLevel::Info, L"Info"}
	};

	Logger& Logger::operator()(const std::wstring& tag)
	{
		m_logTag = tag;
		return *this;
	}

	void Logger::SetRootPath(const std::filesystem::path& rootPath)
	{
		m_rootPath = rootPath;
	}

	void Logger::WriteLog(LogLevel logLevel, const std::wstring& tag, const std::wstring& msg)
	{
		std::time_t currentTime = std::time(nullptr);
		tm* localTime = std::localtime(&currentTime);
		std::wstring logFileName = std::format(L"{:02}-{:02}-{}.log", localTime->tm_mday, localTime->tm_mon, localTime->tm_year + 1900);
		std::filesystem::path logFilePath = m_rootPath / logFileName;

		std::lock_guard lock(s_logMutex);
		std::wofstream logFile(logFilePath, std::ios::app);
		std::wstring log = std::format(L"{:02}:{:02}:{:02}  [{}][{}] {}", localTime->tm_hour, localTime->tm_min, localTime->tm_sec, tag, s_logLevelMap[logLevel], msg);
		logFile << log << std::endl;
		logFile.close();
	}

	Logger& LoggerBuilder::BuildLogger()
	{
		return m_logger;
	}

	LoggerBuilder& LoggerBuilder::SetRootPath(const std::filesystem::path& rootPath)
	{
		m_logger.SetRootPath(rootPath);
		return *this;
	}

}