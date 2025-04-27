#include "peachpch.h"
#include "Timer.h"

namespace Peach
{
	Timer::Timer()
	{
		reset();
	}

	void Timer::reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Timer::elapsedTime() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f;
	}

	float Timer::elapsedTimeMs() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f;
	}

	ScopeTimer::ScopeTimer(const std::string_view name)
		: m_Name(name)
	{
	}

	ScopeTimer::~ScopeTimer()
	{
		PEACH_TRACE("{} - {}ms", m_Name, m_Timer.elapsedTimeMs());
	}
}