#pragma once

namespace Peach
{
	class UUID
	{
	public:
		UUID();
		UUID(size_t uuid);

		operator size_t() const { return m_UUID; }
	private:
		size_t m_UUID;
	};
}

namespace std 
{
	template <typename T> struct hash;

	template<>
	struct hash<Peach::UUID>
	{
		size_t operator()(const Peach::UUID& uuid) const
		{
			return (size_t)uuid;
		}
	};

}
