#pragma once

#include "Tile.h"

#include "Peach/System.h"

namespace Peach
{
	using MapKey = Vec2u;
	using Map = std::map<MapKey, Ref<Tile>>;

	class PEACH_API TileMap
	{
	public:
		TileMap();
		TileMap(const sf::Texture& texture);
		TileMap(const sf::Texture& texture, const Vec2u& mapsize, const Vec2f& tilesize, const Vec2u& spritesize);
		~TileMap();

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setSize(const Vec2u& newsize);
		void setTileSize(const Vec2f& newsize);
		void setSpriteSize(const Vec2u& newsize);

		const Vec2u& getSize() const;
		const Vec2f& getTileSize() const;
		std::weak_ptr<Tile> getTile(const MapKey& key);
		std::vector<std::weak_ptr<Tile>> getTiles(const UIntRect& rect = {});

		void render(sf::RenderTarget* target, const IntRect& view, bool convertrect = false) const;
		void render(sf::RenderTarget* target) const;
	private:
		Map m_TileMap;

		Vec2u m_Size;
		Vec2f m_TileSize;
		SpriteSheet m_SpriteSheet;
	private:
		void adjustTiles();

		void resizeX(uint32_t sizex);
		void resizeY(uint32_t sizey);

		Ref<Tile> createTile() const;
	};
}
