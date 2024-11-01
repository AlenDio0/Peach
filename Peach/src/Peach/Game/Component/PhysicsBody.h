#pragma once

#include "RigidBody.h"

namespace Peach
{
	class PhysicsBody
	{
	public:
		PhysicsBody() = default;
		PhysicsBody(const RigidBody& body, const Vec2f& velocity = {}, const Vec2f& maxvelocity = {}, float acceleration = 1.f, float drag = 0.f)
			: m_Body(body), m_Velocity(velocity), m_MaxVelocity(maxvelocity), m_Acceleration(acceleration), m_Drag(drag)
		{
		}

		void setPosition(const Vec2f& position) { m_Body.setPosition(position); }
		void setScale(const Vec2f& scale) { m_Body.setScale(scale); }
		void setHitbox(const FloatRect& hitbox) { m_Body.setHitbox(hitbox); }
		void setVelocity(const Vec2f& velocity) { m_Velocity = velocity; }
		void setMaxVelocity(const Vec2f& maxvelocity) { m_MaxVelocity = maxvelocity; }
		void setAcceleration(float acceleration) { m_Acceleration = acceleration; }
		void setDrag(float drag) { m_Drag = drag; }

		const RigidBody& getBody() const { return m_Body; }
		const Vec2f& getVelocity() const { return m_Velocity; }
		const Vec2f& getMaxVelocity() const { return m_MaxVelocity; }
		float getAcceleration() const { return m_Acceleration; }
		float getDrag() const { return m_Drag; }
	private:
		RigidBody m_Body;

		Vec2f m_Velocity;
		Vec2f m_MaxVelocity;
		float m_Acceleration;
		float m_Drag;
	};
}
