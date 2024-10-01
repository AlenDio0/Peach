#include "peachpch.h"
#include "TileMap.h"

namespace Peach
{
	TileMap::TileMap(const sf::Vector2u& mapsize, const sf::Vector2f& tilesize)
		: m_TileSize(tilesize), m_Size(0, 0)
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

	void TileMap::setSize(const sf::Vector2u& newsize)
	{
		if (m_Size == newsize)
		{
			return;
		}

		if (m_Size.x == 0 && m_Size.y == 0)
		{
			for (uint32_t x = 0; x < newsize.x; x++)
			{
				for (uint32_t y = 0; y < newsize.y; y++)
				{
					m_TileMap[MapKey(x, y)] = TileRef(new Tile(m_TileSize, { x * m_TileSize.x, y * m_TileSize.y }));
				}
			}

			m_Size = newsize;
			return;
		}

		if (m_Size.x < newsize.x)
		{
			for (uint32_t x = m_Size.x; x < newsize.x; x++)
			{
				for (uint32_t y = 0; y < m_Size.y; y++)
				{
					m_TileMap[MapKey(x, y)] = TileRef(new Tile(m_TileSize, { x * m_TileSize.x, y * m_TileSize.y }));
				}
			}
		}
		else
		{
			for (uint32_t x = newsize.x; x < m_Size.x; x++)
			{
				for (uint32_t y = 0; y < m_Size.y; y++)
				{
					m_TileMap.erase(MapKey(x, y));
				}
			}
		}
		m_Size.x = newsize.x;

		if (m_Size.y < newsize.y)
		{
			for (uint32_t x = 0; x < m_Size.x; x++)
			{
				for (uint32_t y = m_Size.y; y < newsize.y; y++)
				{
					m_TileMap[MapKey(x, y)] = TileRef(new Tile(m_TileSize, { x * m_TileSize.x, y * m_TileSize.y }));
				}
			}
		}
		else
		{
			for (uint32_t x = 0; x < m_Size.x; x++)
			{
				for (uint32_t y = newsize.y; y < m_Size.y; y++)
				{
					m_TileMap.erase(MapKey(x, y));
				}
			}
		}

		m_Size.y = newsize.y;
	}

	void TileMap::setTileSize(const sf::Vector2f& size)
	{
		m_TileSize = size;

		for (auto& [position, tile] : m_TileMap)
		{
			tile->setSize(m_TileSize);
			tile->setPosition({ position.x * m_TileSize.x, position.y * m_TileSize.y });
		}
	}

	void TileMap::render(sf::RenderTarget* target, const IntRect& view) const
	{
		const bool& ignoreview = view.width == 0 && view.height == 0;

		const int& x = view.x - 1;
		const int& y = view.y - 1;
		const int& width = view.width + 1;
		const int& height = view.height + 1;

		for (const auto& [position, tile] : m_TileMap)
		{
			if (!ignoreview)
			{
				const bool& inboundX = (int)position.x >= x && (int)position.x <= width;
				const bool& inboundY = (int)position.y >= y && (int)position.y <= height;

				if (!(inboundX && inboundY))
				{
					continue;
				}
			}

			tile->render(target);
		}
	}
}
