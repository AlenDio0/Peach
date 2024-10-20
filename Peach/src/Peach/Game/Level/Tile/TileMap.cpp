#include "peachpch.h"
#include "TileMap.h"

namespace Peach
{
	TileMap::TileMap()
		: m_SpriteSheet({}, { 1, 1 })
	{
	}

	TileMap::TileMap(const sf::Texture& texture)
		: TileMap()
	{
		setTexture(texture);
	}

	TileMap::TileMap(const Vec2u& mapsize, const Vec2f& tilesize, const sf::Texture& texture, const Vec2u& spritesize)
		: m_TileSize(tilesize), m_SpriteSheet(texture, spritesize)
	{
		setSize(mapsize);
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
			for (uint32_t x = 0; x < newsize.x; ++x)
			{
				for (uint32_t y = 0; y < newsize.y; ++y)
				{
					m_TileMap[MapKey(x, y)] = MakeRef<Tile>(m_TileSize, Vec2f(x * m_TileSize.x, y * m_TileSize.y));
				}
			}

			m_Size = newsize;
			return;
		}

		resizeX(newsize.x);
		resizeY(newsize.y);
	}

	void TileMap::setTileSize(const Vec2f& newsize)
	{
		m_TileSize = newsize;

		for (auto& [position, tile] : m_TileMap)
		{
			tile->setSize(m_TileSize);
			tile->setHitbox({ {}, m_TileSize });
			tile->setPosition({ position.x * m_TileSize.x, position.y * m_TileSize.y });
			tile->update();
		}
	}

	void TileMap::setSpriteSize(const Vec2u& newsize)
	{
		m_SpriteSheet.setSpriteSize(newsize);
	}

	void TileMap::update()
	{
		for (auto& [position, tile] : m_TileMap)
		{
			tile->setTexture(m_SpriteSheet.getTexture());
			tile->setTextureRect(m_SpriteSheet.getRect(tile->getID()));
		}
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

	void TileMap::resizeX(const uint32_t& sizex)
	{
		if (m_Size.x < sizex)
		{
			for (uint32_t x = m_Size.x; x < sizex; ++x)
			{
				for (uint32_t y = 0; y < m_Size.y; ++y)
				{
					m_TileMap[MapKey(x, y)] = MakeRef<Tile>(m_TileSize, Vec2f(x * m_TileSize.x, y * m_TileSize.y));
				}
			}
		}
		else
		{
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

	void TileMap::resizeY(const uint32_t& sizey)
	{
		if (m_Size.y < sizey)
		{
			for (uint32_t x = 0; x < m_Size.x; ++x)
			{
				for (uint32_t y = m_Size.y; y < sizey; ++y)
				{
					m_TileMap[MapKey(x, y)] = MakeRef<Tile>(m_TileSize, Vec2f(x * m_TileSize.x, y * m_TileSize.y));
				}
			}
		}
		else
		{
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
}
