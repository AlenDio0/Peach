#pragma once

#include "Peach/Core.h"

#include "Tile.h"

namespace Peach
{
	using TileRef = std::shared_ptr<Tile>;
	using MapKey = Vec2u;
	using Map = std::map<MapKey, TileRef>;
	using ConvertMap = std::map<uint32_t, std::pair<TileType, IntRect>>;

	class PEACH_API TileMap
	{
	public:
		TileMap(const Vec2u& mapsize, const Vec2f& tilesize);
		~TileMap() = default;

		Map& getRawMap();
		const Vec2u& getSize() const;
		const Vec2f& getTileSize() const;
		TileRef getTile(const MapKey& key);

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setSize(const Vec2u& newsize);
		void setTileSize(const Vec2f& newsize);

		void convertImage(const sf::Image& image, const ConvertMap& convertMap, bool forcesize = true);

		void render(sf::RenderTarget* target, const IntRect& view, bool convertrect = false) const;
		void render(sf::RenderTarget* target) const;
	private:
		Map m_TileMap;

		Vec2u m_Size;
		Vec2f m_TileSize;
	private:
		void resizeX(const uint32_t& sizex);
		void resizeY(const uint32_t& sizey);
	};
}
