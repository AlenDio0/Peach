#pragma once

#include "Entity.h"

#include "Peach/System/UUID.h"

namespace Peach
{
	using EntityMap = std::unordered_map<UUID, Ref<Entity>>;

	class PEACH_API EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		UUID add(Ref<Entity> entity);
		UUID add(Entity* entity);

		void remove(UUID uuid);
		void remove(Ref<Entity> entity);
		void remove(Entity* entity);

		const EntityMap& getEntities() const;
		EntityMap& getEntities();

		template<typename T>
		std::unordered_map<UUID, Ref<T>> getEntities() const
		{
			std::unordered_map<UUID, Ref<T>> entities;

			for (const auto& [uuid, ent] : m_Entities)
			{
				if (const auto& entity = std::dynamic_pointer_cast<T>(ent))
				{
					entities[uuid] = entity;
				}
			}

			return entities;
		}

		std::weak_ptr<Entity> getEntity(UUID uuid) const;
		template<typename T>
		std::weak_ptr<T> getEntity(UUID uuid) const
		{
			return std::dynamic_pointer_cast<T>(getEntity(uuid));
		}

		void update(float deltaTime);
	private:
		EntityMap m_Entities;
	};
}
