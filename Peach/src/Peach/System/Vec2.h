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
		template<typename U = T>
		Vec2(const Vec2<U>& vec)
			: x((T)vec.x), y((T)vec.y)
		{
		}
		template<typename U = T>
		Vec2(const sf::Vector2<U>& vec)
			: x((T)vec.x), y((T)vec.y)
		{
		}

		template<typename U = T>
		operator sf::Vector2<U>() const { return sf::Vector2<U>(x, y); }

		// FUNCTIONS

		T square() { return x * y; }

		// OPERATIONS

		// vec1 + vec2
		Vec2 operator+(const Vec2& r) const { return Vec2(x + r.x, y + r.y); }
		Vec2 operator+=(const Vec2& r)
		{
			*this = *this + r;
			return *this;
		}

		// vec1 - vec2
		Vec2 operator-(const Vec2& r) const { return Vec2(x - r.x, y - r.y); }
		Vec2 operator-=(const Vec2& r)
		{
			*this = *this - r;
			return *this;
		}

		// vec1 * vec2
		Vec2 operator*(const Vec2& r) const { return Vec2(x * r.x, y * r.y); }
		Vec2 operator*=(const Vec2& r)
		{
			*this = *this * r;
			return *this;
		}

		// vec1 / vec2
		Vec2 operator/(const Vec2& r) const { return Vec2(x / r.x, y / r.y); }
		Vec2 operator/=(const Vec2& r)
		{
			*this = *this / r;
			return *this;
		}

		// vec + k
		Vec2 operator+(const T& r) const { return Vec2(x + r, y + r); }
		Vec2 operator+=(const T& r)
		{
			*this = *this + r;
			return *this;
		}

		// vec - k
		Vec2 operator-(const T& r) const { return Vec2(x - r, y - r); }
		Vec2 operator-=(const T& r)
		{
			*this = *this - r;
			return *this;
		}

		// vec * k
		Vec2 operator*(const T& r) const { return Vec2(x * r, y * r); }
		Vec2 operator*=(const T& r)
		{
			*this = *this * r;
			return *this;
		}

		// vec / k
		Vec2 operator/(const T& r) const { return Vec2(x / r, y / r); }
		Vec2 operator/=(const T& r)
		{
			*this = *this / r;
			return *this;
		}

		// COMPARATIONS

		// vec1 == vec2
		bool operator==(const Vec2& r) const { return x == r.x && y == r.y; }
		// vec1 != vec2
		bool operator!=(const Vec2& r) const { return !(*this == r); }

		// vec1 > vec2
		bool operator>(const Vec2& r) const { return x == r.x ? y > r.y : x > r.x; }
		// vec1 >= vec2
		bool operator>=(const Vec2& r) const { return *this > r && *this == r; }

		// vec1 < vec2
		bool operator<(const Vec2& r) const { return x == r.x ? y < r.y : x < r.x; }
		// vec1 <= vec2
		bool operator<=(const Vec2& r) const { return *this < r && *this == r; }
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
