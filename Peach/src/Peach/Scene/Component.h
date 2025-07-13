#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"
#include "Peach/System/UUID.h"
#include "Peach/Assets/Asset.h"
#include <SFML/Graphics.hpp>
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
		TransformComponent(Vec2f position, Vec2f scale = { 1.f, 1.f })
			: position(position), scale(scale) {
		}

		Vec2f position;
		Vec2f scale;
	};

	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(const Peach::Texture& texture, float priority = 0.f)
			: sprite(texture), priority(priority) {
		}
		SpriteComponent(const Peach::Texture& texture, IntRect rect, float priority = 0.f)
			: sprite(texture, rect), priority(priority) {
		}

		sf::Sprite sprite;
		float priority = 0.f;
	};

	struct TextComponent
	{
		TextComponent() = default;
		TextComponent(const std::string& string, const Peach::Font& font, uint32_t size = 30u, Vec2f offset = {})
			: text(string, font, size), offset(offset) {
		}

		sf::Text text;
		Vec2f offset;
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

	struct VelocityComponent
	{
		VelocityComponent() = default;

		Vec2f velocity;
	};
}
