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
		Entity createEntity(UUID uuid, std::string_view tag = "");

		void destroyEntity(Entity entity);

		Entity getEntity(std::string_view tag);
		Entity getEntity(UUID uuid);

		template<typename... Components>
		auto getEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		inline World& getWorld() { return *m_World; }

		void update(const float deltaTime);
		void render(sf::RenderTarget& target);

		void renderHitbox(sf::RenderTarget& target, sf::Color color = sf::Color::Red, float thickness = -1.f);
	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_Entities;

		Scope<World> m_World;

		friend class Entity;
	};
}
