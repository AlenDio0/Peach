#pragma once

#include "Peach/Core/Core.h"

#include <vector>
#include <unordered_map>

namespace Peach
{
	using EntityHandle = uint32_t;

	class IComponentPool
	{
		IComponentPool() = default;
		virtual ~IComponentPool() = default;
	};

	template<typename T>
	class ComponentPool : public IComponentPool
	{
	public:
		void add(EntityHandle entity, T& component)
		{
			PEACH_ASSERT(m_EntityToComponent.find(entity) == m_EntityToComponent.end(), "heal");

			m_EntityToComponent[entity] = m_Components.size();

			m_Entities.push_back(entity);
			m_Components.push_back(component);
		}

		void remove(EntityHandle entity)
		{
			if (EntityToComponent.find(entity) == m_EntityToComponent.end())
			{
				return;
			}

			size_t index = EntityToComponent[entity]->second;
			size_t last = m_Components.size() - 1;

			m_Components[index] = m_Components[last];
			m_Entities[index] = m_Entities[last];

			EntityToComponent[m_Entities[index]] = index;

			m_Components.pop_back();
			m_Entities.pop_back();
			EntityToComponent.erase(entity);
		}

		T& get(EntityHandle entity)
		{
			return m_Components[m_EntityToComponent[entity]];
		}

		bool has(EntityHandle entity)
		{
			return m_EntityToComponent.count(entity) > 0;
		}
	private:
		std::vector<T> m_Components;
		std::vector<EntityHandle> m_Entities;
		std::unordered_map<EntityHandle, size_t> m_EntityToComponent;
	};
}

