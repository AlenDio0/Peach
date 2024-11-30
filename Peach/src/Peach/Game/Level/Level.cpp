#include "peachpch.h"
#include "Level.h"

namespace Peach
{
    Level::Level()
        : Level(std::move(TileMap()))
    {
    }

    Level::Level(TileMap&& tilemap)
        : m_TileMap(tilemap)
    {
		PEACH_CORE_TRACE("Level costruito");
    }

    Level::~Level()
    {
		PEACH_CORE_TRACE("Level distrutto");

		PEACH_CORE_TRACE("[Level] {} Entity distrutti", m_Entities.size());
		m_Entities.clear();
    }

    UUID Level::addEntity(Ref<Entity> entity)
    {
        UUID uuid;
        
		PEACH_CORE_TRACE("Level::addEntity(entity: {}), [uuid: {}]", entity, uuid);
		if (!entity)
		{
			PEACH_CORE_ERROR("Level::addEntity(...), Impossibile aggiungere un Entity nullo");
			return 0;
		}

        m_Entities[uuid] = entity;

        return uuid;
    }

    UUID Level::addEntity(Entity* entity)
    {
        return addEntity(Ref<Entity>(entity));
    }

    void Level::removeEntity(UUID uuid)
    {
		PEACH_CORE_TRACE("Level::removeEntity(uuid: {})", uuid);
		m_Entities.erase(uuid);
    }

    void Level::removeEntity(Ref<Entity> entity)
    {
		PEACH_CORE_TRACE("Level::removeEntity(entity: {})", entity);
		for (auto& [uuid, ent] : m_Entities)
		{
			if (ent == entity)
			{
				removeEntity(uuid);
				break;
			}
		}
    }

    void Level::removeEntity(Entity* entity)
    {
        removeEntity(Ref<Entity>(entity));
    }

    const TileMap& Level::getTileMap() const
    {
        return m_TileMap;
    }

    TileMap& Level::getTileMap()
    {
        return m_TileMap;
    }

    const EntityMap& Level::getEntities() const
    {
        return m_Entities;
    }

    EntityMap& Level::getEntities()
    {
        return m_Entities;
    }

    std::weak_ptr<Entity> Level::getEntity(UUID uuid) const
    {
		try
		{
			return m_Entities.at(uuid);
		}
		catch (const std::exception& e)
		{
			PEACH_CORE_ERROR("Level::getEntity(uuid: {}), Catturata eccezione: {}", uuid, e.what());
			return Ref<Entity>(nullptr);
		}
    }

    void Level::update()
    {
        m_TileMap.update();

        for (auto& [uuid, entity] : m_Entities)
        {
            entity->update();
        }
    }

    void Level::render(sf::RenderTarget* target) const
    {
        m_TileMap.render(target);

        for (auto& [uuid, entity] : m_Entities)
        {
            if (auto gameobj = std::dynamic_pointer_cast<GameObject>(entity))
            {
                target->draw(gameobj);
            }
        }
    }
}
