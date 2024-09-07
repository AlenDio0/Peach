#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Peach
{
	class PEACH_API Log
	{
	public:
		static void init();
		static void initFile(spdlog::filename_t filename, const size_t& maxsizemb, const size_t& maxfiles);

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
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
