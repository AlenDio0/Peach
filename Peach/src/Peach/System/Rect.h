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
		Rect(const T& x, const T& y, const T& width, const T& height)
			: x(x), y(y), width(width), height(height)
		{
		}
		template<typename U = T>
		Rect(const Rect<U>& rect)
			: x((T)rect.x), y((T)rect.y), width((T)rect.width), height((T)rect.height)
		{
		}
		template<typename U = T>
		Rect(const Vec2<U>& position, const Vec2<U>& size)
			: x((T)position.x), y((T)position.y), width((T)size.x), height((T)size.y)
		{
		}
		template<typename U = T>
		Rect(const sf::Rect<U>& rect)
			: x((T)rect.left), y((T)rect.top), width((T)rect.width), height((T)rect.height)
		{
		}

		template<typename U = T>
		operator sf::Rect<U>() const { return sf::Rect<U>(x, y, width, height); }

		// FUNCTIONS

		const T& operator[](size_t index) const
		{
			switch (index)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return width;
			case 3:
				return height;
			}
		}
		T& operator[](size_t index)
		{
			switch (index)
			{
			default:
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return width;
			case 3:
				return height;
			}
		}

		Vec2<T> getPosition() const { return Vec2<T>(x, y); }
		Vec2<T> getSize() const { return Vec2<T>(width, height); }
		Vec2<T> max() const { return getPosition() + getSize(); }
		T area() const { return getSize().area(); }
		Vec2<T> center() const { return max().center(); }

		bool contains(Vec2<T> point) const { return (point.x >= x && point.x < max().x) && (point.y >= y && point.y < max().y); }

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
