#pragma once

#include "Peach/Core.h"

#include "Tile.h"

namespace Peach
{
	using MapKey = Vec2u;
	using Map = std::map<MapKey, Ref<Tile>>;
	using ConvertMap = std::map<uint32_t, std::pair<TileType, IntRect>>;

	class PEACH_API TileMap
	{
	public:
		TileMap(const Vec2u& mapsize, const Vec2f& tilesize);
		~TileMap() = default;

		Map& getRawMap();
		const Vec2u& getSize() const;
		const Vec2f& getTileSize() const;
		Ref<Tile> getTile(const MapKey& key);

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setSize(const Vec2u& newsize);
		void setTileSize(const Vec2f& newsize);

		void convertImage(const sf::Image& image, const ConvertMap& convertMap, bool forcesize = true);

		void render(sf::RenderTarget* target, const IntRect& view = {}, bool forceview = false, bool convertrect = false) const;
	private:
		Map m_TileMap;

		Vec2u m_Size;
		Vec2f m_TileSize;
	};
}
