#pragma once

namespace Peach
{
	template<typename T>
	struct Vec2
	{
		T x, y;

		Vec2() = default;
		Vec2(const T& x, const T& y)
			: x(x), y(y)
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
	};

	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2f = Vec2<float>;
}
