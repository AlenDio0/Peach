#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"

namespace Peach
{
	struct Transform
	{
		Transform() = default;
		Transform(Vec2f position, Vec2f scale)
			: position(position), scale(scale)
		{
		}

		Vec2f position;
		Vec2f scale;
	};

	struct RigidBody
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
