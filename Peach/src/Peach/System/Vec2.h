#pragma once

#include <SFML/System/Vector2.hpp>
#include <spdlog/fmt/ostr.h>

namespace Peach
{
	template<typename T>
	struct Vec2
	{
		T x, y;

		Vec2()
			: Vec2(0, 0)
		{
		}
		Vec2(const T& x, const T& y)
			: x(x), y(y)
		{
		}
		Vec2(const sf::Vector2<T>& vec)
			: x(vec.x), y(vec.y)
		{
		}

		const Vec2& operator+(const Vec2& r) const
		{
			return Vec2(x + r.x, y + r.y);
		}
		const Vec2& operator+(const T& r) const
		{
			return Vec2(x + r, y + r);
		}

		const Vec2& operator-(const Vec2& r) const
		{
			return Vec2(x - r.x, y - r.y);
		}
		const Vec2& operator-(const T& r) const
		{
			return Vec2(x - r, y - r);
		}

		const Vec2& operator*(const Vec2& r) const
		{
			return Vec2(x * r.x, y * r.y);
		}
		const Vec2& operator*(const T& r) const
		{
			return Vec2(x * r, y * r);
		}

		const Vec2& operator/(const Vec2& r) const
		{
			return Vec2(x / r.x, y / r.y);
		}
		const Vec2& operator/(const T& r) const
		{
			return Vec2(x / r, y / r);
		}

		bool operator==(const Vec2& r) const
		{
			return x == r.x && y == r.y;
		}
		bool operator!=(const Vec2& r) const
		{
			return !(*this == r);
		}

		bool operator>(const Vec2& r) const
		{
			return x == r.x ? y > r.y : x > r.x;
		}
		bool operator<(const Vec2& r) const
		{
			return x == r.x ? y < r.y : x < r.x;
		}

		Vec2<T>& operator=(const sf::Vector2<T>& r)
		{
			x = r.x;
			y = r.y;

			return *this;
		}

		operator sf::Vector2<T>() const
		{
			return sf::Vector2<T>(x, y);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
	{
		return os << "[" << v.x << ", " << v.y << "]";
	}

	template<typename T>
	struct fmt::formatter<Vec2<T>> : fmt::ostream_formatter {};

	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2f = Vec2<float>;
}
