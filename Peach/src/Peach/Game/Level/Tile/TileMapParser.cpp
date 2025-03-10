#include "peachpch.h"
#include "TileMapParser.h"

namespace Peach
{
	TileMap&& TileMapParser::parse(const std::filesystem::path& filepath, const sf::Texture& texture)
	{
		TileMap* tilemap = new TileMap(texture);

		open(filepath);
		while (!isEOF())
		{
			std::string buff = consumeLine();

			if (!find(buff, "START"))
			{
				continue;
			}

			std::string_view token_str(buff.c_str() + 6);

			if (token_str == "TileMap")
			{
				fileToTileMap(*tilemap);
			}
			else if (token_str == "Map")
			{
				fileToMap(*tilemap);
			}
		}

		return std::move(*tilemap);
	}

	void TileMapParser::fileToTileMap(TileMap& tilemap)
	{
		constexpr char* token_mapsize = "MapSize";
		constexpr char* token_tilesize = "TileSize";
		constexpr char* token_spritesize = "SpriteSize";
		constexpr char* token_collideids = "CollideIDs";

		while (!isEOF())
		{
			std::string buff = consumeLine();

			if (isEnd(buff))
			{
				break;
			}

			if (find(buff, token_mapsize))
			{
				std::string_view str_mapsize(buff.c_str() + strlen(token_mapsize));
				tilemap.setSize(stringToVec2u(str_mapsize));
			}
			else if (find(buff, token_tilesize))
			{
				std::string_view str_tilesize(buff.c_str() + strlen(token_tilesize));
				tilemap.setTileSize(stringToVec2f(str_tilesize));
			}
			else if (find(buff, token_spritesize))
			{
				std::string_view str_spritesize(buff.c_str() + strlen(token_spritesize));
				tilemap.setSpriteSize(stringToVec2u(str_spritesize));
			}
			else if (find(buff, token_collideids))
			{
				std::string_view str_collideids(buff.c_str() + strlen(token_spritesize));
				tilemap.setCollideIDs(stringToVectorU(str_collideids));
			}
		}
	}

	void TileMapParser::fileToMap(TileMap& tilemap)
	{
		constexpr char* token_pos = "Pos";
		constexpr char* token_id = "ID";

		constexpr size_t npos = std::string::npos;

		Vec2u tile_pos;
		std::string buff;
		while (!isEOF())
		{
			if (isEnd(buff))
			{
				break;
			}

			size_t found = npos;
			if (find(buff, token_pos))
			{
				found = buff.find(token_pos);
				buff = buff.substr(found + strlen(token_pos));

				tile_pos = stringToVec2u(buff);
			}
			if (find(buff, token_id))
			{
				found = buff.find(token_id);
				buff = buff.substr(found + strlen(token_id));

				uint32_t id = nextUInt(buff);
				if (auto tile = tilemap.getTile(tile_pos).lock())
				{
					tile->setID(id);
				}
				else
				{
					PEACH_CORE_WARN("Level::convertFile(...), La posizione del Tile {} va oltre la grandezza di TileMap {}", tile_pos, tilemap.getSize());
					continue;
				}
			}

			if (found == npos)
			{
				buff = consumeLine();
			}
		}
	}
}