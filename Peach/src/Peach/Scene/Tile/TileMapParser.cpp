#include "peachpch.h"
#include "TileMapParser.h"

#include "Peach/Scene/Entity.h"

namespace Peach
{
	TileMap TileMapParser::parse(const std::filesystem::path& filePath, Scene* scene, const Peach::Texture& texture)
	{
		open(filePath);

		MapInfo mapInfo;
		std::map<Vec2u, uint32_t> map;

		while (!isEOF())
		{
			std::string buff = consumeLine();

			if (!find(buff, "START"))
			{
				continue;
			}

			std::string_view token_str(buff.c_str() + 6);

			if (token_str == "Map")
			{
				mapInfo = convertMap();
			}
			else if (token_str == "TileMap")
			{
				map = convertTileMap(mapInfo);
			}
		}

		TileMap tileMap(scene, texture, mapInfo.spriteSize, mapInfo.mapSize, mapInfo.tileSize);

		for (uint32_t y = 0; y < mapInfo.mapSize.y; y++)
		{
			for (uint32_t x = 0; x < mapInfo.mapSize.x; x++)
			{
				Vec2u position = { x, y };
				try
				{
					uint32_t tileID = map.at(position);
					Entity tile = tileMap.getTile(position);
					tile.getComponent<TileComponent>().setID(tile, tileID);

					for (uint32_t id : mapInfo.collideIDs)
					{
						if (id == tileID)
						{
							tile.addComponent<HitboxComponent>(FloatRect({}, mapInfo.tileSize));
							tile.getComponent<SpriteComponent>().priority = 10.f;
							break;
						}
					}
				}
				catch (std::exception& e)
				{
					PEACH_CORE_WARN("TileMapParser::parse(filePath: {}, ...), Tile non trovato nel file nella posizione {}", filePath.string(), position);
					continue;
				}
			}
		}

		return tileMap;
	}

	TileMapParser::MapInfo TileMapParser::convertMap()
	{
		constexpr char* token_mapsize = "MapSize";
		constexpr char* token_tilesize = "TileSize";
		constexpr char* token_spritesize = "SpriteSize";
		constexpr char* token_collideids = "CollideIDs";

		MapInfo info;

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
				info.mapSize = stringToVec2u(str_mapsize);
			}
			else if (find(buff, token_tilesize))
			{
				std::string_view str_tilesize(buff.c_str() + strlen(token_tilesize));
				info.tileSize = stringToVec2f(str_tilesize);
			}
			else if (find(buff, token_spritesize))
			{
				std::string_view str_spritesize(buff.c_str() + strlen(token_spritesize));
				info.spriteSize = stringToVec2u(str_spritesize);
			}
			else if (find(buff, token_collideids))
			{
				std::string_view str_collideids(buff.c_str() + strlen(token_spritesize));
				info.collideIDs = stringToVectorU(str_collideids);
			}
		}

		return info;
	}

	std::map<Vec2u, uint32_t> TileMapParser::convertTileMap(MapInfo mapInfo)
	{
		constexpr char* token_pos = "Pos";
		constexpr char* token_id = "ID";

		constexpr size_t npos = std::string::npos;

		std::map<Vec2u, uint32_t> map;

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
				if (tile_pos.x <= mapInfo.mapSize.x && tile_pos.y <= mapInfo.mapSize.y)
				{
					map[tile_pos] = id;
				}
				else
				{
					PEACH_CORE_WARN("Level::convertFile(...), La posizione del Tile {} va oltre la grandezza di TileMap {}", tile_pos, mapInfo.mapSize);
					continue;
				}
			}

			if (found == npos)
			{
				buff = consumeLine();
			}
		}

		return map;
	}
}