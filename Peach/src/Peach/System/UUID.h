#pragma once

#include "Peach/Core/Core.h"

#include <spdlog/fmt/ostr.h>

namespace Peach
{
	class PEACH_API UUID
	{
	public:
		UUID();
		UUID(const size_t uuid);

		operator size_t() const { return m_UUID; }

		friend std::ostream& operator<<(std::ostream& os, const UUID& uuid)
		{
			return os << std::hex << (size_t)uuid;
		}
	private:
		size_t m_UUID;
	};
}

template<>
struct fmt::formatter<Peach::UUID> : fmt::ostream_formatter {};

namespace std
{
	template<typename T>
	struct hash;

	template<>
	struct hash<Peach::UUID>
	{
		size_t operator()(const Peach::UUID& uuid) const
		{
			return (size_t)uuid;
		}
	};
}
