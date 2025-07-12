#pragma once

#include "Scene.h"

#include <entt.hpp>

namespace Peach
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		Entity(entt::entity handle, Scene* scene);

		template<typename Component, typename... Args>
		Component& addComponent(Args&&... args)
		{
			PEACH_ASSERT(!hasComponent<Component>(), "Entity ha già il Component");
			return m_Scene->m_Registry.emplace<Component>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename Component, typename... Args>
		Component& replaceComponent(Args&&... args)
		{
			return m_Scene->m_Registry.emplace_or_replace<Component>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename Component>
		void removeComponent()
		{
			PEACH_ASSERT(hasComponent<Component>(), "Entity non ha il Component");
			m_Scene->m_Registry.remove<Component>(m_Handle);
		}

		template<typename Component>
		Component& getComponent()
		{
			PEACH_ASSERT(hasComponent<Component>(), "Entity non ha il Component");
			return m_Scene->m_Registry.get<Component>(m_Handle);
		}

		template<typename... Components>
		bool hasComponent()
		{
			return m_Scene->m_Registry.any_of<Components...>(m_Handle);
		}
	private:
		entt::entity m_Handle;
		Scene* m_Scene;
	};
}
