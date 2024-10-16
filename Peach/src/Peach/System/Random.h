#pragma once

#include "Peach/Core.h"

#include <random>

namespace Peach
{
	class PEACH_API Random
	{
	public:
		static uint32_t getUInt()
		{
			return s_Distribution(s_Engine);
		}

		static uint32_t getUInt(uint32_t min, uint32_t max)
		{
			return min + (getUInt() % (max - min + 1));
		}

		static float getFloat()
		{
			return (float)s_Distribution(s_Engine) / (float)std::numeric_limits<uint32_t>::max();
		}
	private:
		static inline std::default_random_engine s_Engine;
		static inline std::uniform_int_distribution<uint32_t> s_Distribution;
	};
}

#define PEACH_RANDOM_UINT(...)		Peach::Random::getUInt(__VA_ARGS__);
#define PEACH_RANDOM_FLOAT()		Peach::Random::getFloat();
