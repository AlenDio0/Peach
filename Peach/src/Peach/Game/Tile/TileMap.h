#pragma once

#include "Peach/Core.h"

#include "Peach/System/Vec2.h"
#include "Peach/System/Rect.h"
#include "Tile.h"

namespace Peach
{
	using TileRef = std::shared_ptr<Tile>;
	using MapKey = Vec2u;
	using Map = std::map<MapKey, TileRef>;

	class PEACH_API TileMap
	{
	public:
		TileMap(const sf::Vector2u& mapsize, const sf::Vector2f& tilesize);
		~TileMap() = default;

		Map& getRawMap();
		const sf::Vector2u& getSize() const;
		const sf::Vector2f& getTileSize() const;
		TileRef getTile(const MapKey& key);

		void setSize(const sf::Vector2u& newsize);
		void setTileSize(const sf::Vector2f& newsize);

		void render(sf::RenderTarget* target, const IntRect& view = {}) const;
	private:
		Map m_TileMap;

		sf::Vector2u m_Size;
		sf::Vector2f m_TileSize;
	};
}
