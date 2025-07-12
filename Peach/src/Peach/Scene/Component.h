#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"
#include "Peach/System/UUID.h"
#include <functional>

namespace Peach
{
	class Entity;

	struct UUIDComponent
	{
		UUIDComponent() = default;
		UUIDComponent(UUID uuid)
			: uuid(uuid) {
		}

		operator const UUID& () const { return uuid; }
		operator UUID& () { return uuid; }

		UUID uuid;
	};

	struct TagComponent
	{
		TagComponent() = default;
		TagComponent(std::string_view tag)
			: tag(tag) {
		}

		operator std::string_view() const { return tag; }
		operator std::string& () { return tag; }

		std::string tag;
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(Vec2f position, Vec2f scale)
			: position(position), scale(scale) {
		}

		Vec2f position;
		Vec2f scale;
	};

	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(const sf::Texture& texture)
			: sprite(texture) {
		}
		SpriteComponent(const sf::Texture& texture, IntRect rect)
			: sprite(texture, rect) {
		}

		sf::Sprite sprite;
	};

	struct HitboxComponent
	{
		HitboxComponent() = default;
		HitboxComponent(FloatRect box)
			: box(box) {
		}

		FloatRect box;
	};

	struct UpdateComponent
	{
		UpdateComponent() = default;
		UpdateComponent(std::function<void(Entity, const float)> update)
			: update(update) {
		}

		std::function<void(Entity, const float)> update;
	};
}
