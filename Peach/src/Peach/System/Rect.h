#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <spdlog/fmt/ostr.h>

namespace Peach
{
	template<typename T>
	struct Rect
	{
		T x, y, width, height;

		Rect()
			: Rect(0, 0, 0, 0)
		{
		}
		template<typename U = T>
		Rect(const Rect<U>& rect)
			: Rect((T)rect.x, (T)rect.y, (T)rect.width, (T)rect.height)
		{
		}
		template<typename U = T>
		Rect(const Vec2<U>& position, const Vec2<U>& size)
			: Rect((T)position.x, (T)position.y, (T)size.x, (T)size.y)
		{
		}
		template<typename U = T>
		Rect(const sf::Rect<U>& rect)
			: Rect((T)rect.left, (T)rect.top, (T)rect.width, (T)rect.height)
		{
		}
		Rect(const T& x, const T& y, const T& width, const T& height)
			: x(x), y(y), width(width), height(height)
		{
		}

		template<typename U = T>
		operator sf::Rect<U>() const { return sf::Rect<U>(x, y, width, height); }

		// FUNCTIONS

		Vec2<T> getPosition() const { return Vec2<T>(x, y); }
		Vec2<T> getSize() const { return Vec2<T>(width, height); }

		// OPERATIONS

		// rect + k
		Rect operator+(const T& r) const { return Rect(x + r, y + r, width + r, height + r); }
		Rect operator+=(const T& r)
		{
			*this = *this + r;
			return *this;
		}

		// rect - k
		Rect operator-(const T& r) const { return Rect(x - r, y - r, width - r, height - r); }
		Rect operator-=(const T& r)
		{
			*this = *this - r;
			return *this;
		}

		// rect * k
		Rect operator*(const T& r) const { return Rect(x * r, y * r, width * r, height * r); }
		Rect operator*=(const T& r)
		{
			*this = *this * r;
			return *this * r;
		}

		// rect / k
		Rect operator/(const T& r) const { return Rect(x / r, y / r, width / r, height / r); }
		Rect operator/=(const T& r)
		{
			*this = *this / r;
			return *this;
		}

		// COMPARATIONS

		// rect == rect2
		bool operator==(const Rect& r) const { return x == r.x && y == r.y && width == r.width && height == r.height; }
		// rect1 != rect2
		bool operator!=(const Rect& r) const { return !(*this == r); }
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Rect<T>& r)
	{
		return os << "[" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << "]";
	}

	template<typename T>
	struct fmt::formatter<Rect<T>> : fmt::ostream_formatter {};

	using IntRect = Rect<int>;
	using UIntRect = Rect<unsigned int>;
	using FloatRect = Rect<float>;
}
