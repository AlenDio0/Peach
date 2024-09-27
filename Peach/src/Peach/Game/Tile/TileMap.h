#pragma once

#include "Peach/Core.h"

#include "Tile.h"

namespace Peach
{
	struct TilePos
	{
		TilePos(const uint32_t& x, const uint32_t& y)
			: x(x), y(y)
		{
		}

		uint32_t x, y;

		bool operator<(const TilePos& right) const
		{
			return x == right.x ? y < right.y : x < right.x;
		}
	};

	using TileRef = std::shared_ptr<Tile>;
	using MapKey = TilePos;
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

		void setSize(const sf::Vector2u& size);
		void setTileSize(const sf::Vector2f& size);

		void render(sf::RenderTarget* target) const;
	private:
		Map m_TileMap;

		sf::Vector2u m_Size;
		sf::Vector2f m_TileSize;
	};
}
