#include "peachpch.h"
#include "TileMap.h"

namespace Peach
{
	TileMap::TileMap(const sf::Vector2u& mapsize, const sf::Vector2f& tilesize)
		: m_TileSize(tilesize)
	{
		setSize(mapsize);
	}

	Map& TileMap::getRawMap()
	{
		return m_TileMap;
	}

	const sf::Vector2u& TileMap::getSize() const
	{
		return m_Size;
	}

	const sf::Vector2f& TileMap::getTileSize() const
	{
		return m_TileSize;
	}

	TileRef TileMap::getTile(const MapKey& key)
	{
		return m_TileMap[key];
	}

	void TileMap::setSize(const sf::Vector2u& size)
	{
		m_Size = size;
		m_TileMap.clear();

		for (uint32_t x = 0; x < m_Size.x; ++x)
		{
			for (uint32_t y = 0; y < m_Size.y; ++y)
			{
				m_TileMap[MapKey(x, y)] = TileRef(new Tile(m_TileSize, { x * m_TileSize.x, y * m_TileSize.y }));
			}
		}
	}

	void TileMap::setTileSize(const sf::Vector2f& size)
	{
		m_TileSize = size;

		for (auto& [position, tile] : m_TileMap)
		{
			tile->setSize(m_TileSize);
		}
	}

	void TileMap::render(sf::RenderTarget* target) const
	{
		for (auto& [position, tile] : m_TileMap)
		{
			tile->render(target);
		}
	}
}
