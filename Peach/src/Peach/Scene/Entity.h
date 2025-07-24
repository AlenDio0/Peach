#pragma once

#include "Scene.h"

#include <entt.hpp>

namespace Peach
{
	class PEACH_API Entity
	{
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		Entity(entt::entity handle, Scene* scene);
		virtual ~Entity() = default;

		template<typename Component, typename... Args>
		Component& addComponent(Args&&... args)
		{
			PEACH_CORE_ASSERT(!hasComponent<Component>());
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
			PEACH_CORE_ASSERT(hasComponent<Component>());
			m_Scene->m_Registry.remove<Component>(m_Handle);
		}

		template<typename Component>
		Component& getComponent()
		{
			PEACH_CORE_ASSERT(hasComponent<Component>());
			return m_Scene->m_Registry.get<Component>(m_Handle);
		}

		template<typename... Components>
		bool hasComponent()
		{
			return m_Scene->m_Registry.all_of<Components...>(m_Handle);
		}

		const UUID& getUUID();
		const std::string& getTag();

		operator uint32_t() const;
		operator entt::entity() const;
	private:
		entt::entity m_Handle;
		Scene* m_Scene;
	};
}
