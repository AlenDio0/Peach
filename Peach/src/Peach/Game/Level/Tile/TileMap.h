#pragma once

#include "Tile.h"

namespace Peach
{
	using MapKey = Vec2u;
	using Map = std::map<MapKey, Ref<Tile>>;

	class PEACH_API TileMap
	{
	public:
		TileMap();
		TileMap(const sf::Texture& texture);
		TileMap(const Vec2u& mapsize, const Vec2f& tilesize, const sf::Texture& texture, const Vec2u& spritesize);
		~TileMap();

		const Vec2u& getSize() const;
		const Vec2f& getTileSize() const;
		Ref<Tile> getTile(const MapKey& key);
		std::vector<Ref<Tile>> getTiles(const UIntRect& rect = {});

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setSize(const Vec2u& newsize);
		void setTileSize(const Vec2f& newsize);
		void setSpriteSize(const Vec2u& newsize);

		void update();

		void render(sf::RenderTarget* target, const IntRect& view, bool convertrect = false) const;
		void render(sf::RenderTarget* target) const;
	private:
		Map m_TileMap;

		Vec2u m_Size;
		Vec2f m_TileSize;
		SpriteSheet m_SpriteSheet;
	private:
		void resizeX(uint32_t sizex);
		void resizeY(uint32_t sizey);
	};
}
