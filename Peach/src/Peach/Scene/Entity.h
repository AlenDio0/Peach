#pragma once

#include "Scene.h"

namespace Peach
{
	class Entity
	{
	public:
		Entity(EntityHandle handle, Scene* scene);

		template<typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			PEACH_ASSERT(!hasComponent<T>(), "Entity already has component");
			T& component = m_Scene->m_Registry.add(m_Handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		void removeComponent()
		{
			m_Scene->m_Registry.remove<T>(m_Handle);
		}

		template<typename T>
		T& getComponent()
		{
			PEACH_ASSERT(hasComponent<T>(), "Entity does not have component");
			return m_Scene->m_Registry.get<T>(m_Handle)
		}

		template<typename T>
		bool hasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_Handle);
		}
	private:
		EntityHandle m_Handle;
		Scene* m_Scene;
	};
}
