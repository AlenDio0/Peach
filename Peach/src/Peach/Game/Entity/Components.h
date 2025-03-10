#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"

namespace Peach
{
	struct Component
	{
		Component() = default;
		virtual ~Component() = default;
	};

	struct ID : public Component
	{
		ID() = default;
		ID(size_t id)
			: id(id) {
		}

		operator size_t() const { return id; }
		operator size_t& () { return id; }

		size_t id = 0;
	};

	struct Tag : public Component
	{
		Tag() = default;
		Tag(std::string_view tag)
			: tag(tag) {
		}

		operator std::string_view() const { return tag; }
		operator std::string& () { return tag; }

		std::string tag;
	};

	struct Transform : public Component
	{
		Transform() = default;
		Transform(Vec2f position, Vec2f scale)
			: position(position), scale(scale) {
		}

		Vec2f position;
		Vec2f scale;
	};

	struct RigidBody : public Component
	{
		RigidBody() = default;
		RigidBody(FloatRect hitbox, bool collide)
			: hitbox(hitbox), collide(collide) {
		}

		FloatRect hitbox;
		bool collide = false;
	};

	struct Movement : public Component
	{
		Movement() = default;
		virtual ~Movement() = default;

		Vec2f velocity;
	};

	struct LinearMovement : public Movement
	{
		LinearMovement() = default;
		LinearMovement(Vec2f speed)
			: speed(speed) {
		}
		LinearMovement(float x, float y)
			: speed(x, y) {
		}

		Vec2f speed;
	};

	struct AccelerationMovement : public Movement
	{
		AccelerationMovement() = default;
		AccelerationMovement(Vec2f minVelocity, Vec2f maxVelocity, float acceleration)
			: minVelocity(minVelocity), maxVelocity(maxVelocity), acceleration(acceleration) {
		}

		Vec2f minVelocity;
		Vec2f maxVelocity;
		float acceleration = 0.f;
	};
}
