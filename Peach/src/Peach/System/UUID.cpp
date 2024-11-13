#include "peachpch.h"
#include "UUID.h"

#include <random>

namespace Peach
{
	static std::random_device s_RandomDevice;
	static std::default_random_engine s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<size_t> s_UniformDistribution((size_t)pow(10, 19));

	UUID::UUID()
		: m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(size_t uuid)
		: m_UUID(uuid)
	{
	}
}
