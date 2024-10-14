#include "peachpch.h"
#include "Level.h"

namespace Peach
{
	Level::Level(const std::filesystem::path& filepath)
		: m_TileMap({}, {})
	{
		convertFile(filepath);
	}

	void Level::convertFile(const std::filesystem::path& filepath)
	{
		enum Token
		{
			UNKNOWN = -1,
			START,
			LEVEL,
			TILEMAP,
			MAP
		};
		Token token = UNKNOWN;

		static Vec2i sprite_size;
		std::ifstream file(filepath, std::ios::app);
		while (!file.eof())
		{
			std::string buff;
			file >> buff;

			token = buff != "START" ? (buff == "END" ? Token(token - 1) : token) : START;
			if (buff == "START")
			{
				file >> buff;
			}

			switch (token)
			{
			case START:
				if (buff == "LEVEL")
				{
					token = LEVEL;
				}
				else if (buff == "TILEMAP")
				{
					token = TILEMAP;
				}
				else if (buff == "MAP")
				{
					token = MAP;
				}
				break;
			case LEVEL:
				break;
			case TILEMAP:
				if (buff == "MAP_SIZE")
				{
					Vec2u map_size;
					file >> map_size.x >> map_size.y;
					m_TileMap.setSize(map_size);
				}
				else if (buff == "SPRITE_SIZE")
				{
					file >> sprite_size.x >> sprite_size.y;
				}
				else if (buff == "TILE_SIZE")
				{
					Vec2f tile_size;
					file >> tile_size.x >> tile_size.y;
					m_TileMap.setTileSize(tile_size);
				}
				break;
			case MAP:
			{
				static MapKey tile_pos;
				if (buff == "X")
				{
					file >> tile_pos.x;
				}
				else if (buff == "Y")
				{
					file >> tile_pos.y;
				}
				else if (buff == "ID")
				{
					Ref<Tile> tile = m_TileMap.getTile(tile_pos);
					TileID id;
					file >> id;

					tile->setID(id);
					tile->setTextureRect({ {sprite_size.x * (int)id, 0}, sprite_size });
				}
			}
			break;
			}
		}
	}

	void Level::setTileTexture(const sf::Texture& texture, bool resetrect)
	{
		m_TileMap.setTexture(texture, resetrect);
	}

	void Level::render(sf::RenderTarget* target) const
	{
		m_TileMap.render(target);
	}
}