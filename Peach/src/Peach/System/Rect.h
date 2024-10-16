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
		Rect(const Vec2<T>& position, const Vec2<T> size)
			: x(position.x), y(position.y), width(size.x), height(size.y)
		{

		}
		template<typename U>
		Rect(const Rect<U>& rect)
			: x(rect.x), y(rect.y), width(rect.width), height(rect.height)
		{
		}
		template<typename U>
		Rect(const sf::Rect<U>& rect)
			: x(rect.x), y(rect.y), width(rect.width), height(rect.width)
		{
		}

		const Rect& operator+(const Rect& r) const
		{
			return Rect(x + r.x, y + r.y, width + r.width, height + r.height);
		}
		const Rect& operator+(const T& r) const
		{
			return Rect(x + r, y + r, width + r, height + r);
		}

		const Rect& operator-(const Rect& r) const
		{
			return Rect(x - r.x, y - r.y, width - r.width, height - r.height);
		}
		const Rect& operator-(const T& r) const
		{
			return Rect(x - r, y - r, width - r, height - r);
		}

		const Rect& operator*(const Rect& r) const
		{
			return Rect(x * r.x, y * r.y, width * r.width, height * r.height);
		}
		const Rect& operator*(const T& r) const
		{
			return Rect(x * r, y * r, width * r, height * r);
		}

		const Rect& operator/(const Rect& r) const
		{
			return Rect(x / r.x, y / r.y, width / r.width, height / r.height);
		}
		const Rect& operator/(const T& r) const
		{
			return Rect(x / r, y / r, width / r, height / r);
		}

		bool operator==(const Rect& r) const
		{
			return x == r.x && y == r.y && width == r.width && height == r.height;
		}
		bool operator!=(const Rect& r) const
		{
			return !(*this == r);
		}

		Rect& operator=(const sf::Rect<T>& r)
		{
			x = r.x;
			y = r.y;
			width = r.width;
			height = r.height;

			return *this;
		}

		operator sf::Rect<T>() const
		{
			return sf::Rect<T>(x, y, width, height);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Rect<T>& r)
	{
		return os << "[" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << "]";
	}

	template<typename T>
	struct fmt::formatter<Rect<T>> : fmt::ostream_formatter {};

	using IntRect = Rect<int>;
	using FloatRect = Rect<float>;
}
