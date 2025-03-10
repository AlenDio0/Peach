#include "peachpch.h"
#include "EntityManager.h"

namespace Peach
{
	EntityManager::EntityManager()
	{
		PEACH_CORE_TRACE("EntityManager costruito");
	}

	EntityManager::~EntityManager()
	{
		PEACH_CORE_TRACE("EntityManager distrutto");

		PEACH_CORE_TRACE("[EntityManager] {} Entity distrutti", m_Entities.size());
		m_Entities.clear();
	}

	UUID EntityManager::add(Ref<Entity> entity)
	{
		UUID uuid;

		PEACH_CORE_TRACE("EntityManager::addEntity(entity: {}), [uuid: {}]", entity, uuid);
		if (!entity)
		{
			PEACH_CORE_ERROR("EntityManager::addEntity(...), Impossibile aggiungere un Entity nullo");
			return 0;
		}

		m_Entities[uuid] = entity;

		return uuid;
	}

	UUID EntityManager::add(Entity* entity)
	{
		return add(Ref<Entity>(entity));
	}

	void EntityManager::remove(UUID uuid)
	{
		PEACH_CORE_TRACE("EntityManager::removeEntity(uuid: {})", uuid);
		m_Entities.erase(uuid);
	}

	void EntityManager::remove(Ref<Entity> entity)
	{
		PEACH_CORE_TRACE("EntityManager::removeEntity(entity: {})", entity);
		for (auto& [uuid, ent] : m_Entities)
		{
			if (ent == entity)
			{
				remove(uuid);
				break;
			}
		}
	}

	void EntityManager::remove(Entity* entity)
	{
		remove(Ref<Entity>(entity));
	}

	const EntityMap& EntityManager::getEntities() const
	{
		return m_Entities;
	}

	EntityMap& EntityManager::getEntities()
	{
		return m_Entities;
	}

	void EntityManager::update(const float deltaTime)
	{
		for (auto& [uuid, entity] : m_Entities)
		{
			entity->update(deltaTime);
		}
	}

	std::weak_ptr<Entity> EntityManager::getEntity(UUID uuid) const
	{
		try
		{
			return m_Entities.at(uuid);
		}
		catch (const std::exception& e)
		{
			PEACH_CORE_ERROR("EntityManager::getEntity(uuid: {}), Catturata eccezione: {}", uuid, e.what());
			return Ref<Entity>(nullptr);
		}
	}
}
