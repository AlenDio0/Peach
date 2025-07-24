#include "peachpch.h"
#include "TileMap.h"

#include "Peach/Scene/Entity.h"
#include <string>

namespace Peach
{
	TileMap::TileMap(Scene* scene, const Peach::Texture& texture, Vec2u spriteSize, Vec2u mapSize, Vec2f tileSize)
		: m_Scene(scene), m_Sprites(texture, spriteSize), m_MapSize(mapSize), m_TileSize(tileSize)
	{
		m_Tiles.reserve(m_MapSize.area());
		for (uint32_t y = 0; y < m_MapSize.y; y++)
		{
			for (uint32_t x = 0; x < m_MapSize.x; x++)
			{
				createTile({ x, y });
			}
		}
	}

	Entity TileMap::createTile(Vec2u position, uint32_t id)
	{
		PEACH_CORE_ASSERT(position.x < m_MapSize.x && position.y < m_MapSize.y);

		Entity tile = m_Scene->createEntity();

		tile.addComponent<TileComponent>(position, this);
		tile.addComponent<TransformComponent>(position * m_TileSize, m_TileSize / m_Sprites.getSpriteSize());
		tile.addComponent<SpriteComponent>(m_Sprites.getTexture(), m_Sprites.getRect(id));

		m_Tiles.push_back(tile);
		return tile;
	}

	void TileMap::destroyTile(Vec2u position)
	{
		if (!hasTile(position))
		{
			return;
		}

		Entity tile = getTile(position);

		m_Tiles.erase(std::remove(m_Tiles.begin(), m_Tiles.end(), tile), m_Tiles.end());
		m_Scene->destroyEntity(tile);
	}

	bool TileMap::hasTile(Vec2u position)
	{
		auto view = m_Scene->getEntitiesWith<TileComponent>();
		for (auto& [entity, tile] : view.each())
		{
			if (tile.position != position)
			{
				continue;
			}

			if (std::find(m_Tiles.begin(), m_Tiles.end(), entity) != m_Tiles.end())
			{
				return true;
			}
		}

		return false;
	}

	Entity TileMap::getTile(Vec2u position)
	{
		PEACH_CORE_ASSERT(hasTile(position));

		auto view = m_Scene->getEntitiesWith<TileComponent>();
		for (auto& [entity, tile] : view.each())
		{
			if (tile.position != position)
			{
				continue;
			}

			if (std::find(m_Tiles.begin(), m_Tiles.end(), entity) != m_Tiles.end())
			{
				return Entity(entity, m_Scene);
			}
		}

		PEACH_CORE_ERROR("TileMap::getTile(position: {}), Ritornato valore nullo", position);
		return {};
	}

	void TileMap::setTileID(Entity tile, uint32_t id)
	{
		sf::Sprite& sprite = tile.getComponent<SpriteComponent>().sprite;
		sprite.setTexture(m_Sprites.getTexture());
		sprite.setTextureRect(m_Sprites.getRect(id));
	}

	void TileComponent::setID(Entity tile, uint32_t id)
	{
		m_TileMap->setTileID(tile, id);
	}

	/*TileMap::TileMap()
		: TileMap(sf::Texture()) {
	}

	TileMap::TileMap(const sf::Texture& texture)
		: TileMap(texture, {}, {}, { 1, 1 }) {
	}

	TileMap::TileMap(const sf::Texture& texture, const Vec2u mapsize, const Vec2f tilesize, const Vec2u spritesize)
		: m_TileSize(tilesize), m_SpriteSheet(texture, spritesize)
	{
		setSize(mapsize);
	}

	TileMap::~TileMap()
	{
		PEACH_CORE_TRACE("TileMap distrutto");

		PEACH_CORE_TRACE("[TileMap] {} Tile distrutti", m_Map.size());
		m_Map.clear();
	}

	void TileMap::setCollideIDs(const std::vector<size_t>& collideid)
	{
		m_CollideIDs = collideid;
		adjustTiles();
	}

	void TileMap::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_SpriteSheet.setTexture(texture);
		for (auto& [position, tile] : m_Map)
		{
			tile->setTexture(texture, resetrect);
		}
	}

	void TileMap::setSize(const Vec2u newsize)
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
					m_Map[MapKey(x, y)] = createTile();
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

	void TileMap::setTileSize(const Vec2f newsize)
	{
		m_TileSize = newsize;
		adjustTiles();
	}

	void TileMap::setSpriteSize(const Vec2u newsize)
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

	std::weak_ptr<Tile> TileMap::getTile(const MapKey key) const
	{
		try
		{
			return m_Map.at(key);
		}
		catch (const std::exception& e)
		{
			PEACH_CORE_ERROR("TileMap::getTile(key: {}), Catturata eccezione: {}", key, e.what());
			return Ref<Tile>(nullptr);
		}
	}

	const std::map<MapKey, std::weak_ptr<Tile>>& TileMap::getTiles(IntRect rect) const
	{
		if (rect == IntRect())
		{
			rect = IntRect(Vec2i(), (Vec2i)m_Size);
		}

		if (rect.x < 0)
		{
			rect.width -= rect.x;
			rect.x = 0;
		}
		if (rect.y < 0)
		{
			rect.height -= rect.y;
			rect.y = 0;
		}
		while (m_Size.x < rect.x + rect.width && rect.width > 0)
		{
			rect.width--;
		}
		while (m_Size.y < rect.y + rect.height && rect.height > 0)
		{
			rect.height--;
		}

		auto& [cachedRect, cachedTiles] = m_CachedRectTiles;
		if (!cachedTiles.empty() && cachedRect == rect)
		{
			return cachedTiles;
		}
		cachedTiles.clear();
		cachedRect = rect;

		for (uint32_t x = rect.x; x < rect.width + rect.x; ++x)
		{
			for (uint32_t y = rect.y; y < rect.height + rect.y; ++y)
			{
				MapKey key(x, y);
				cachedTiles[key] = getTile(key);
			}
		}

		return cachedTiles;
	}

	void TileMap::update(const float deltaTime)
	{
		for (auto& [position, tile] : m_Map)
		{
			tile->update(deltaTime);
		}
	}

	void TileMap::render(sf::RenderTarget& target, const IntRect view, bool convertrect) const
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

		for (const auto& [position, tile] : m_Map)
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

			target.draw(*tile);
		}
	}
	void TileMap::render(sf::RenderTarget& target) const
	{
		for (const auto& [position, tile] : m_Map)
		{
			target.draw(*tile);
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
					m_Map[MapKey(x, y)] = createTile();
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
					m_Map.erase(MapKey(x, y));
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
					m_Map[MapKey(x, y)] = createTile();
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
					m_Map.erase(MapKey(x, y));
				}
			}
		}
		m_Size.y = sizey;
	}

	Ref<Tile> TileMap::createTile() const
	{
		auto changed_id = [&](Tile& tile)
			{
				tile.setTextureRect(m_SpriteSheet.getRect(tile.getID()));

				tile.getRigidBody().collide = false;
				for (const auto& id : m_CollideIDs)
				{
					if (tile.getID() == id)
					{
						tile.getRigidBody().collide = true;
						break;
					}
				}
			};

		return MakeRef<Tile>(m_SpriteSheet.getTexture(), changed_id);
	}

	void TileMap::adjustTiles()
	{
		setTexture(m_SpriteSheet.getTexture());
		for (auto& [pos, tile] : m_Map)
		{
			auto& [position, scale] = tile->getTransform();
			position = m_TileSize * pos;
			scale = m_TileSize / m_SpriteSheet.getSpriteSize();

			tile->setID(tile->getID());

			if (auto& body = tile->has<RigidBodyComp>().lock())
			{
				body->hitbox.position = Vec2f();
				body->hitbox.size = m_TileSize;
			}
		}
	}*/
}
