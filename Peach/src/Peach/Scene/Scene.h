#pragma once

#include "Peach/Core/Core.h"

#include "Component.h"
#include <entt.hpp>

namespace Peach
{
	class Entity;
	class World;

	class PEACH_API Scene
	{
	public:
		Scene();
		Scene(std::filesystem::path mapFile, const Peach::Texture& mapTexture);
		virtual ~Scene();

		Entity createEntity(std::string_view tag = "");

		Entity getEntity(std::string_view tag);

		template<typename... Components>
		auto getEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		void update(const float deltaTime);
		void render(sf::RenderTarget& target);

		void renderHitbox(sf::RenderTarget& target, sf::Color color = sf::Color::Red, float thickness = -1.f);
	private:
		entt::registry m_Registry;

		Scope<World> m_World;

		friend class Entity;
	};
}
