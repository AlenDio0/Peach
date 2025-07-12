#pragma once

#include "Peach/Core/Core.h"

#include "ComponentPool.h"

#include <typeindex>

namespace Peach
{
	class Registry
	{
	public:
		EntityHandle create()
		{
			return m_EntityCount++;
		}

		template<typename T, typename... Args>
		T& add(EntityHandle entity, Args... args)
		{
			T component = T(std::forward<Args>(args)...);
			getPool<T>()->add(entity, component);

			return component;
		}

		template<typename T>
		T& get(EntityHandle entity) {
			return getPool<T>()->get(entity);
		}

		template<typename T>
		bool has(EntityHandle entity) {
			return getPool<T>()->has(entity);
		}

		template<typename T>
		void remove(EntityHandle entity) {
			getPool<T>()->remove(entity);
		}
	private:
		EntityHandle m_EntityCount = 0;
		std::unordered_map<std::type_index, Scope<IComponentPool>> m_Pools;

		template<typename T>
		const Scope<ComponentPool<T>>& getPool()
		{
			std::type_index compType = typeid(T);
			if (m_Pools.find(compType) == m_Pools.end())
			{
				m_Pools[type] = MakeScope<ComponentPool<T>>();
			}

			return m_Pools[type];
		}
	};
}

