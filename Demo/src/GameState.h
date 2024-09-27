#pragma once
#include <Peach\State.h>

#include <Peach\Game\Tile\MapManager.h>

class MapManager : public Peach::MapManager
{
public:
	enum TileType
	{
		NONE = 0,
		DEBUG,
		WOOD,

	};
public:
	MapManager(const sf::Vector2f& tilesize)
		: Peach::MapManager(tilesize)
	{
	}

	virtual void convertImageToMap(const sf::Image& image)
	{
		m_TileMap.setSize(image.getSize());

		for (uint32_t x = 0; x < image.getSize().x; ++x)
		{
			for (uint32_t y = 0; y < image.getSize().y; ++y)
			{
				sf::Color pixel = image.getPixel(x, y);

				if (pixel == sf::Color::White)
				{
					m_TileMap.getTile({ x,y })->type = DEBUG;
				}
				else if (pixel == sf::Color::Black)
				{
					m_TileMap.getTile({ x,y })->type = WOOD;
				}
			}
		}

		for (auto& [position, tile] : m_TileMap.getRawMap())
		{
			switch (tile->type)
			{
			case NONE:
				tile->setTextureRect(sf::IntRect(0, 0, 1, 1));
				break;
			case DEBUG:
				tile->setTextureRect(sf::IntRect(16, 0, 16, 16));
				break;
			case WOOD:
				tile->setTextureRect(sf::IntRect(0, 0, 16, 16));
				break;
			}
		}
	}
};

class GameState : public Peach::State
{
public:
	GameState(Peach::DataRef data);
	~GameState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	MapManager m_Map;

	// TODO: Add a player and boxes to collide
};

