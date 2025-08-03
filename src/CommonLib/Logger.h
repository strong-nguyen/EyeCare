#pragma once

#include <filesystem>
#include <map>
#include <mutex>
#include <atlstr.h>

namespace CommonLib
{
	class __declspec(dllexport) Logger
	{
	public:
		friend class LoggerBuilder;

		Logger() = default;

		template <typename... Args>
		void Info(const wchar_t* formatMsg, Args... args)
		{
			CStringW msg;
			msg.Format(formatMsg, args...);
			WriteLog(LogLevel::Info, m_logTag, msg.GetString());
		}

		template <typename... Args>
		void Warn(const wchar_t* formatMsg, Args... args)
		{
			CStringW msg;
			msg.Format(formatMsg, args...);
			WriteLog(LogLevel::Warn, m_logTag, msg.GetString());
		}

		template <typename... Args>
		void Error(const wchar_t* formatMsg, Args... args)
		{
			CStringW msg;
			msg.Format(formatMsg, args...);
			WriteLog(LogLevel::Error, m_logTag, msg.GetString());
		}

		Logger& operator()(const std::wstring& tag);

	private:
		void SetRootPath(const std::filesystem::path& rootPath);

		enum class LogLevel
		{
			Error,
			Warn,
			Info
		};

		void WriteLog(LogLevel logLevel, const std::wstring& tag, const std::wstring& msg);

		std::filesystem::path m_rootPath;

		std::wstring m_logTag;  // Each thread will have different tag

		static std::map<LogLevel, std::wstring> s_logLevelMap;

		inline static std::mutex s_logMutex;
	};


	class __declspec(dllexport) LoggerBuilder
	{
	public:
		Logger& BuildLogger();

		LoggerBuilder& SetRootPath(const std::filesystem::path& rootPath);

	private:
		std::filesystem::path m_rootPath;

		inline static Logger m_logger;
	};

	extern __declspec(dllexport) Logger log;
}
