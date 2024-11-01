#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Peach
{
	class PEACH_API Log
	{
	public:
		enum class Level
		{
			Trace = SPDLOG_LEVEL_TRACE,
			Info = SPDLOG_LEVEL_INFO,
			Warn = SPDLOG_LEVEL_WARN,
			Error = SPDLOG_LEVEL_ERROR,
			Fatal = SPDLOG_LEVEL_CRITICAL,
			Off = SPDLOG_LEVEL_OFF
		};
	public:
		static void init(const std::string& appname = "APP", Log::Level level = Level::Trace, Log::Level flushon = Level::Error, const std::string& pattern = "[%T] <%n> %^[%l] %v.%$");
		static void initFile(const spdlog::filename_t& filename, size_t maxsizemb, size_t maxfiles);

		static void setLevel(Log::Level level);

		inline static Ref<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		inline static Ref<spdlog::logger> s_CoreLogger;
		inline static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define PEACH_CORE_TRACE(...)  ::Peach::Log::getCoreLogger()->trace(__VA_ARGS__)
#define PEACH_CORE_INFO(...)   ::Peach::Log::getCoreLogger()->info(__VA_ARGS__)
#define PEACH_CORE_WARN(...)   ::Peach::Log::getCoreLogger()->warn(__VA_ARGS__)
#define PEACH_CORE_ERROR(...)  ::Peach::Log::getCoreLogger()->error(__VA_ARGS__)
#define PEACH_CORE_FATAL(...)  ::Peach::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PEACH_TRACE(...)       ::Peach::Log::getClientLogger()->trace(__VA_ARGS__)
#define PEACH_INFO(...)        ::Peach::Log::getClientLogger()->info(__VA_ARGS__)
#define PEACH_WARN(...)        ::Peach::Log::getClientLogger()->warn(__VA_ARGS__)
#define PEACH_ERROR(...)       ::Peach::Log::getClientLogger()->error(__VA_ARGS__)
#define PEACH_FATAL(...)       ::Peach::Log::getClientLogger()->critical(__VA_ARGS__)
