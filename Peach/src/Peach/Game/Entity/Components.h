#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"
#include "Peach/System/UUID.h"

namespace Peach
{
	struct Component
	{
		Component() = default;
		virtual ~Component() = default;
	};

	struct IDComp : public Component
	{
		IDComp() = default;
		IDComp(size_t id)
			: id(id) {
		}

		operator size_t() const { return id; }
		operator size_t& () { return id; }

		size_t id = 0;
	};

	struct UUIDComp : public Component
	{
		UUIDComp() = default;
		UUIDComp(UUID uuid)
			: uuid(uuid) {
		}

		operator UUID() const { return uuid; }
		operator UUID& () { return uuid; }

		UUID uuid;
	};

	struct TagComp : public Component
	{
		TagComp() = default;
		TagComp(std::string_view tag)
			: tag(tag) {
		}

		operator std::string_view() const { return tag; }
		operator std::string& () { return tag; }

		std::string tag;
	};

	struct TransformComp : public Component
	{
		TransformComp() = default;
		TransformComp(Vec2f position, Vec2f scale)
			: position(position), scale(scale) {
		}

		Vec2f position;
		Vec2f scale;
	};

	struct RigidBodyComp : public Component
	{
		RigidBodyComp() = default;
		RigidBodyComp(FloatRect hitbox, bool collide)
			: hitbox(hitbox), collide(collide) {
		}

		FloatRect hitbox;
		bool collide = false;
	};

	struct MovementComp : public Component
	{
		MovementComp() = default;
		virtual ~MovementComp() = default;

		Vec2f velocity;
	};

	struct LinearMovementComp : public MovementComp
	{
		LinearMovementComp() = default;
		LinearMovementComp(Vec2f speed)
			: speed(speed) {
		}
		LinearMovementComp(float x, float y)
			: speed(x, y) {
		}

		Vec2f speed;
	};

	struct AccelerationMovementComp : public MovementComp
	{
		AccelerationMovementComp() = default;
		AccelerationMovementComp(Vec2f minVelocity, Vec2f maxVelocity, float acceleration)
			: minVelocity(minVelocity), maxVelocity(maxVelocity), acceleration(acceleration) {
		}

		Vec2f minVelocity;
		Vec2f maxVelocity;
		float acceleration = 0.f;
	};
}
