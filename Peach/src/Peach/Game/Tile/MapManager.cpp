#include "peachpch.h"
#include "MapManager.h"

namespace Peach
{
	MapManager::MapManager(const sf::Vector2f& tilesize)
		: m_TileMap({ 0, 0 }, tilesize)
	{
	}

	TileMap& MapManager::getMap()
	{
		return m_TileMap;
	}

	void MapManager::setTexture(sf::Texture* texture)
	{
		for (auto& [position, tile] : m_TileMap.getRawMap())
		{
			tile->setTexture(texture);
		}
	}

	void MapManager::render(sf::RenderTarget* target) const
	{
		m_TileMap.render(target);
	}
}
