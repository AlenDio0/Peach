#include "peachpch.h"
#include "TileMap.h"

namespace Peach
{
	TileMap::TileMap()
		: TileMap(sf::Texture())
	{
	}

	TileMap::TileMap(const sf::Texture& texture)
		: TileMap(texture, {}, {}, { 1, 1 })
	{
	}

	TileMap::TileMap(const sf::Texture& texture, const Vec2u& mapsize, const Vec2f& tilesize, const Vec2u& spritesize)
		: m_TileSize(tilesize), m_SpriteSheet(texture, spritesize)
	{
		setSize(mapsize);
	}

	TileMap::~TileMap()
	{
		PEACH_CORE_TRACE("TileMap distrutto");

		PEACH_CORE_TRACE("{} Tile distrutti", m_Size.x * m_Size.y);
		m_TileMap.clear();
	}

	void TileMap::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_SpriteSheet.setTexture(texture);
		for (auto& [position, tile] : m_TileMap)
		{
			tile->setTexture(texture, resetrect);
		}
	}

	void TileMap::setSize(const Vec2u& newsize)
	{
		if (m_Size == newsize)
		{
			return;
		}

		if (m_Size == Vec2u(0, 0))
		{
			PEACH_CORE_TRACE("TileMap::setSize(newsize: {}), Creati {} Tile", newsize, newsize.x * newsize.y);

			for (uint32_t x = 0; x < newsize.x; ++x)
			{
				for (uint32_t y = 0; y < newsize.y; ++y)
				{
					m_TileMap[MapKey(x, y)] = createTile();
				}
			}

			m_Size = newsize;
		}
		else
		{
			resizeX(newsize.x);
			resizeY(newsize.y);
		}

		adjustTiles();
	}

	void TileMap::setTileSize(const Vec2f& newsize)
	{
		m_TileSize = newsize;
		adjustTiles();
	}

	void TileMap::setSpriteSize(const Vec2u& newsize)
	{
		m_SpriteSheet.setSpriteSize(newsize);
		adjustTiles();
	}

	const Vec2u& TileMap::getSize() const
	{
		return m_Size;
	}

	const Vec2f& TileMap::getTileSize() const
	{
		return m_TileSize;
	}

	Ref<Tile> TileMap::getTile(const MapKey& key)
	{
		try
		{
			return m_TileMap.at(key);
		}
		catch (const std::exception& e)
		{
			PEACH_CORE_ERROR("TileMap::getTile(key: {}), Catturata eccezione: {}", key, e.what());
			return NULL;
		}
	}

	std::vector<Ref<Tile>> TileMap::getTiles(const UIntRect& rect)
	{
		size_t map_area = (size_t)(m_Size.x * m_Size.y);
		size_t rect_areapos = (size_t)((rect.x + rect.width) * (rect.y + rect.height));

		if (rect_areapos == 0)
		{
			return getTiles({ {}, m_Size });
		}
		else if (map_area < rect_areapos)
		{
			PEACH_CORE_ERROR("TileMap::getTiles(rect: {}), Il Rect supera la grandezza del TileMap [size: {}]", rect, m_Size);
			return {};
		}

		size_t rect_area = (size_t)(rect.width * rect.height);
		std::vector<Ref<Tile>> tiles;
		tiles.reserve(rect_area);

		for (uint32_t x = rect.x; x < rect.width + rect.x; ++x)
		{
			for (uint32_t y = rect.y; y < rect.height + rect.y; ++y)
			{
				tiles.push_back(m_TileMap[MapKey(x, y)]);
			}
		}

		return tiles;
	}

	void TileMap::render(sf::RenderTarget* target, const IntRect& view, bool convertrect) const
	{
		int x = view.x;
		int y = view.y;
		int width = view.width;
		int height = view.height;

		if (convertrect)
		{
			x /= (int)m_TileSize.x;
			y /= (int)m_TileSize.y;
			width /= (int)m_TileSize.x;
			height /= (int)m_TileSize.y;
		}

		const bool& useview = view != IntRect(0, 0, m_Size.x, m_Size.y);

		for (const auto& [position, tile] : m_TileMap)
		{
			if (useview)
			{
				const bool& inboundX = (int)position.x >= x && (int)position.x < width;
				const bool& inboundY = (int)position.y >= y && (int)position.y < height;

				if (!(inboundX && inboundY))
				{
					continue;
				}
			}

			tile->render(target);
		}
	}
	void TileMap::render(sf::RenderTarget* target) const
	{
		for (const auto& [position, tile] : m_TileMap)
		{
			tile->render(target);
		}
	}

	void TileMap::adjustTiles()
	{
		setTexture(m_SpriteSheet.getTexture());
		for (auto& [position, tile] : m_TileMap)
		{
			tile->setScale(m_TileSize / m_SpriteSheet.getSpriteSize());
			tile->setPosition(m_TileSize * position);
		}
	}

	void TileMap::resizeX(uint32_t sizex)
	{
		if (m_Size.x < sizex)
		{
			PEACH_CORE_TRACE("TileMap::resizeX(sizex: {}), {} Tile costruiti", sizex, (sizex - m_Size.x) * m_Size.y);
			for (uint32_t x = m_Size.x; x < sizex; ++x)
			{
				for (uint32_t y = 0; y < m_Size.y; ++y)
				{
					m_TileMap[MapKey(x, y)] = createTile();
				}
			}
		}
		else if (m_Size.x > sizex)
		{
			PEACH_CORE_TRACE("TileMap::resizeX(sizex: {}), {} Tile distrutti", sizex, (m_Size.x - sizex) * m_Size.y);
			for (uint32_t x = sizex; x < m_Size.x; ++x)
			{
				for (uint32_t y = 0; y < m_Size.y; ++y)
				{
					m_TileMap.erase(MapKey(x, y));
				}
			}
		}
		m_Size.x = sizex;
	}

	void TileMap::resizeY(uint32_t sizey)
	{
		if (m_Size.y < sizey)
		{
			PEACH_CORE_TRACE("TileMap::resizeY(sizey: {}), {} Tile costruiti", sizey, (sizey - m_Size.y) * m_Size.x);
			for (uint32_t x = 0; x < m_Size.x; ++x)
			{
				for (uint32_t y = m_Size.y; y < sizey; ++y)
				{
					m_TileMap[MapKey(x, y)] = createTile();
				}
			}
		}
		else if (m_Size.y > sizey)
		{
			PEACH_CORE_TRACE("TileMap::resizeY(sizey: {}), {} Tile distrutti", sizey, (m_Size.y - sizey) * m_Size.x);
			for (uint32_t x = 0; x < m_Size.x; ++x)
			{
				for (uint32_t y = sizey; y < m_Size.y; ++y)
				{
					m_TileMap.erase(MapKey(x, y));
				}
			}
		}
		m_Size.y = sizey;
	}

	Ref<Tile> TileMap::createTile() const
	{
		static auto changed_id = [&](Tile& tile)
			{
				tile.setTextureRect(m_SpriteSheet.getRect(tile.getID()));
			};

		return MakeRef<Tile>(m_SpriteSheet.getTexture(), RigidBody(), changed_id, false);
	}
}
