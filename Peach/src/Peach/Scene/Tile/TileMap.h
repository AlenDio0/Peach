#pragma once

#include "Peach/Core/Core.h"

#include "Peach/Scene/Scene.h"
#include "Peach/System/SpriteSheet.h"
#include <vector>

namespace Peach
{
	class PEACH_API TileMap
	{
	public:
		TileMap(TileMap&) = default;
		TileMap(Scene* scene, const Peach::Texture& texture, Vec2u spriteSize, Vec2u mapSize, Vec2f tileSize);
		virtual ~TileMap() = default;

		Entity createTile(Vec2u position, uint32_t id = 0);

		void destroyTile(Vec2u position);

		bool hasTile(Vec2u position);
		Entity getTile(Vec2u position);
	private:
		void setTileID(Entity tile, uint32_t id);
	private:
		std::vector<entt::entity> m_Tiles;

		Vec2u m_MapSize;
		Vec2f m_TileSize;
		SpriteSheet m_Sprites;

		Scene* m_Scene;

		friend class TileComponent;
	};

	class TileComponent
	{
	public:
		TileComponent(Vec2u position, TileMap* tileMap)
			: position(position), m_TileMap(tileMap) {
		}

		uint32_t getID() const { return m_ID; }
		void setID(Entity tile, uint32_t id);

		Vec2u position;
	private:
		uint32_t m_ID = 0u;

		TileMap* m_TileMap;
	};

	/*using MapKey = Vec2i;

	class PEACH_API TileMap
	{
	public:
		TileMap();
		TileMap(const sf::Texture& texture);
		TileMap(const sf::Texture& texture, const Vec2u mapsize, const Vec2f tilesize, const Vec2u spritesize);
		TileMap(const TileMap&) = default;
		TileMap(TileMap&&) = default;
		~TileMap();

		void setCollideIDs(const std::vector<size_t>& collideid);

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setSize(const Vec2u newsize);
		void setTileSize(const Vec2f newsize);
		void setSpriteSize(const Vec2u newsize);

		const Vec2u& getSize() const;
		const Vec2f& getTileSize() const;
		std::weak_ptr<Tile> getTile(const MapKey key) const;
		const std::map<MapKey, std::weak_ptr<Tile>>& getTiles(IntRect rect = {}) const;

		void update(const float deltaTime);

		void render(sf::RenderTarget& target, const IntRect view, bool convertrect = false) const;
		void render(sf::RenderTarget& target) const;
	private:
		void resizeX(const uint32_t sizex);
		void resizeY(const uint32_t sizey);

		Ref<Tile> createTile() const;
		void adjustTiles();
	private:
		std::map<MapKey, Ref<Tile>> m_Map;
		std::vector<size_t> m_CollideIDs;

		Vec2u m_Size;
		Vec2f m_TileSize;
		SpriteSheet m_SpriteSheet;

		mutable struct
		{
			IntRect rect;
			std::map<MapKey, std::weak_ptr<Tile>> tiles;
		} m_CachedRectTiles;
	};*/
}
