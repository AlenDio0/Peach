#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include <SFML/Graphics/Sprite.hpp>

namespace Peach
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(const Vec2f& position, const Vec2f& scale = {})
			: m_Position(position), m_Scale(scale)
		{
		}

		void setPosition(const Vec2f& position) { m_Position = position; }
		void setScale(const Vec2f& scale) { m_Scale = scale; }

		const Vec2f& getPosition() const { return m_Position; }
		const Vec2f& getScale() const { return m_Scale; }
	private:
		Vec2f m_Position;
		Vec2f m_Scale;
	};
}
