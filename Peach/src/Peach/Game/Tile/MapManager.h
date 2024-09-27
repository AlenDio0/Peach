#pragma once

#include "Peach/Core.h"

#include "TileMap.h"

namespace Peach
{
	//To be defined in CLIENT
	class PEACH_API MapManager
	{
	public:
		enum TileType {};
	public:
		MapManager(const sf::Vector2f& tilesize);
		virtual ~MapManager() = default;

		TileMap& getMap();

		void setTexture(sf::Texture* texture);

		virtual void convertImageToMap(const sf::Image& image) = 0;

		virtual void render(sf::RenderTarget* target) const;
	protected:
		TileMap m_TileMap;

		sf::Image m_Image;
	};
}
