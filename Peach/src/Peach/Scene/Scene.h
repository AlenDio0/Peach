#pragma once

#include "Peach/Core/Core.h"

#include "Component.h"
#include <entt.hpp>

namespace Peach
{
	class Entity;

	class PEACH_API Scene
	{
	public:
		Entity createEntity(std::string_view tag = {});

		Entity getEntity(std::string_view tag);

		void update(const float deltaTime);
		void render(sf::RenderTarget& target);

		void renderHitbox(sf::RenderTarget& target, sf::Color color = sf::Color::Red, float thickness = -1.f);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}
