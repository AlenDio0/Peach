#include "peachpch.h"
#include "Log.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Peach
{
	void Log::init()
	{
		spdlog::set_pattern("[%T] %^[%l] <%n> %v.%$");

		s_CoreLogger = spdlog::stdout_color_mt("PEACH");
		s_ClientLogger = spdlog::stdout_color_mt("APP");

		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);

		PEACH_CORE_INFO("Log inizializzati");
	}

	void Log::initFile(const spdlog::filename_t& filename, size_t maxsizemb, size_t maxfiles)
	{
		size_t max_size_bytes = maxsizemb * (1024 * 1024);

		auto s_FileLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, max_size_bytes, maxfiles, true);

		s_CoreLogger->sinks().push_back(s_FileLogger);
		s_ClientLogger->sinks().push_back(s_FileLogger);

		PEACH_CORE_TRACE("------------ INIZIO LOG ------------");
		PEACH_CORE_INFO("Log file inizializzati");
	}
}
