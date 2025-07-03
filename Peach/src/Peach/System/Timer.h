#pragma once

#include "Peach/Core/Core.h"

#include <chrono>

namespace Peach
{
	class PEACH_API Timer
	{
	public:
		Timer();

		void reset();
		float elapsedTimeSec() const;
		float elapsedTimeMs() const;
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

	class PEACH_API ScopeTimer
	{
	public:
		ScopeTimer(const std::string_view name);
		~ScopeTimer();

	private:
		std::string m_Name;
		Timer m_Timer;
	};
}
