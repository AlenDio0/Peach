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
			: id(id)
		{
		}

		operator size_t() const { return id; }
		operator size_t& () { return id; }

		size_t id;
	};

	struct Tag : public Component
	{
		Tag() = default;
		Tag(const std::string& tag)
			: tag(tag)
		{
		}

		operator const std::string& () const { return tag; }
		operator std::string& () { return tag; }

		std::string tag;
	};

	struct Transform : public Component
	{
		Transform() = default;
		Transform(Vec2f position, Vec2f scale)
			: position(position), scale(scale)
		{
		}

		Vec2f position;
		Vec2f scale;
	};

	struct RigidBody : public Component
	{
		RigidBody() = default;
		RigidBody(Transform transform, FloatRect hitbox)
			: transform(transform), hitbox(hitbox)
		{
		}

		Transform transform;
		FloatRect hitbox;
	};
}
