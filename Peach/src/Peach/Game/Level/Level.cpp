#include "peachpch.h"
#include "Level.h"

namespace Peach
{
	Level::Level()
		: Level(std::move(TileMap())) {
	}

	Level::Level(TileMap&& tilemap)
		: m_TileMap(std::move(tilemap))
	{
		PEACH_CORE_TRACE("Level costruito");
	}

	Level::~Level()
	{
		PEACH_CORE_TRACE("Level distrutto");
	}

	const TileMap& Level::getTileMap() const
	{
		return m_TileMap;
	}

	TileMap& Level::getTileMap()
	{
		return m_TileMap;
	}

	const EntityManager& Level::getEntityManager() const
	{
		return m_EntityManager;
	}

	EntityManager& Level::getEntityManager()
	{
		return m_EntityManager;
	}

	void Level::update(const float deltaTime)
	{
		m_TileMap.update(deltaTime);
		m_EntityManager.update(deltaTime);
	}

	void Level::render(sf::RenderTarget& target) const
	{
		m_TileMap.render(target);

		for (const auto& [uuid, gameobj] : m_EntityManager.getEntities<GameObject>())
		{
			target.draw(*gameobj);
		}
	}
}
