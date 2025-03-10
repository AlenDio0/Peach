#include "peachpch.h"
#include "Log.h"

#include <spdlog/sinks/rotating_file_sink.h>

namespace Peach
{
	void Log::init(std::string_view appName, Log::Level level, Log::Level flushOn, const std::string& pattern)
	{
		spdlog::set_pattern(pattern);

		s_CoreLogger = spdlog::stdout_color_mt("PEACH");
		s_CoreLogger->flush_on((spdlog::level::level_enum)flushOn);

		s_ClientLogger = spdlog::stdout_color_mt(appName.data());
		s_ClientLogger->flush_on((spdlog::level::level_enum)flushOn);

		setLevel(level);

		PEACH_CORE_INFO("Log inizializzati");
	}

	void Log::initFile(const spdlog::filename_t& fileName, size_t maxSizeMb, size_t maxFiles)
	{
		size_t max_size_bytes = maxSizeMb * (size_t)(1024 * 1024);

		auto s_FileLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(fileName, max_size_bytes, maxFiles, true);
		s_FileLogger->set_level(spdlog::level::trace);

		s_CoreLogger->sinks().push_back(s_FileLogger);
		s_ClientLogger->sinks().push_back(s_FileLogger);

		PEACH_CORE_TRACE("------------ INIZIO LOG ------------");
		PEACH_CORE_INFO("Log file inizializzati");
	}

	void Log::setLevel(Log::Level level)
	{
		s_CoreLogger->set_level((spdlog::level::level_enum)level);
		s_ClientLogger->set_level((spdlog::level::level_enum)level);
	}
}
