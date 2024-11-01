#pragma once

#include "Transform.h"

#include "Peach/System/Rect.h"

namespace Peach
{
	class RigidBody
	{
	public:
		RigidBody() = default;
		RigidBody(const Transform& transform, const FloatRect& hitbox)
			: m_Transform(transform), m_Hitbox(hitbox)
		{
		}

		void setPosition(const Vec2f& position) { m_Transform.setPosition(position); }
		void setScale(const Vec2f& scale) { m_Transform.setScale(scale); }
		void setHitbox(const FloatRect& hitbox) { m_Hitbox = hitbox; }

		const Transform& getTransform() const { return m_Transform; }
		const FloatRect& getHitbox() const { return m_Hitbox; }
	private:
		Transform m_Transform;
		FloatRect m_Hitbox;
	};
}
