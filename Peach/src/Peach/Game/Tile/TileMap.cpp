#include "peachpch.h"
#include "TileMap.h"

namespace Peach
{
	TileMap::TileMap(const Vec2u& mapsize, const Vec2f& tilesize)
		: m_TileSize(tilesize), m_Size(0, 0)
	{
		setSize(mapsize);
	}

	Map& TileMap::getRawMap()
	{
		return m_TileMap;
	}

	const Vec2u& TileMap::getSize() const
	{
		return m_Size;
	}

	const Vec2f& TileMap::getTileSize() const
	{
		return m_TileSize;
	}

	TileRef TileMap::getTile(const MapKey& key)
	{
		return m_TileMap[key];
	}

	void TileMap::setTexture(const sf::Texture& texture)
	{
		for (auto& [position, tile] : m_TileMap)
		{
			tile->setTexture(texture);
		}
	}

	void TileMap::setSize(const Vec2u& newsize)
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

	void TileMap::setTileSize(const Vec2f& newsize)
	{
		m_TileSize = newsize;

		for (auto& [position, tile] : m_TileMap)
		{
			tile->setSize(m_TileSize);
			tile->setPosition({ position.x * m_TileSize.x, position.y * m_TileSize.y });
		}
	}

	void TileMap::convertImage(const sf::Image& image, const ConvertMap& convertMap, bool forcesize)
	{
		if (image.getSize().x == 0 || image.getSize().y == 0)
		{
			PEACH_CORE_ERROR("TileMap::convertImage(...), Impossibile convertire (immagine non valida)");

			return;
		}

		if (convertMap.empty())
		{
			PEACH_CORE_ERROR("TileMap::convertImage(...), Impossibile convertire (tavola di conversione non valida)");

			return;
		}

		if (forcesize)
		{
			setSize(image.getSize());
		}

		for (uint32_t x = 0; x < image.getSize().x; ++x)
		{
			for (uint32_t y = 0; y < image.getSize().y; ++y)
			{
				uint32_t pixel = image.getPixel(x, y).toInteger();
				TileRef tile = getTile(MapKey(x, y));

				tile->setType(convertMap.at(pixel).first);
				tile->setTextureRect(convertMap.at(pixel).second);
			}
		}
	}

	void TileMap::render(sf::RenderTarget* target, const IntRect& view, bool forceview, bool convertrect) const
	{
		int x = view.x;
		int y = view.y;
		int width = view.width;
		int height = view.height;

		if (convertrect)
		{
			x /= m_TileSize.x;
			y /= m_TileSize.y;
			width /= m_TileSize.x;
			height /= m_TileSize.y;
		}

		const bool& useview = forceview || ((width != 0 && height != 0) && (view != IntRect(0, 0, m_Size.x, m_Size.y)));

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
}
