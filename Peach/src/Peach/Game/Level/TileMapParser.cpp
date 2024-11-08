#include "peachpch.h"
#include "TileMapParser.h"

namespace Peach
{
	TileMapParser::TileMapParser(const std::filesystem::path& filepath, const sf::Texture& texture)
		: TileMap(texture)
	{
		convertFile(filepath);
	}

	void TileMapParser::convertFile(const std::filesystem::path& filepath)
	{
		std::fstream file(filepath, std::ios::in);
		while (!file.eof())
		{
			std::string buff;
			std::getline(file, buff);

			if (!find(buff, "START"))
			{
				continue;
			}

			std::string token_str = buff.substr(6);

			if (token_str == "TileMap")
			{
				fileToTileMap(file);
			}
			else if (token_str == "Map")
			{
				fileToMap(file);
			}
		}
	}

	void TileMapParser::fileToTileMap(std::fstream& file)
	{
		const char* token_mapsize = "MapSize";
		const char* token_tilesize = "TileSize";
		const char* token_spritesize = "SpriteSize";

		while (!file.eof())
		{
			std::string buff;
			std::getline(file, buff);
			if (isEnd(buff))
			{
				break;
			}

			if (find(buff, token_mapsize))
			{
				const std::string str_mapsize = buff.substr(strlen(token_mapsize));
				setSize(stringToVec2u(str_mapsize));
			}
			else if (find(buff, token_tilesize))
			{
				const std::string str_tilesize = buff.substr(strlen(token_tilesize));
				setTileSize(stringToVec2f(str_tilesize));
			}
			else if (find(buff, token_spritesize))
			{
				const std::string str_spritesize = buff.substr(strlen(token_spritesize));
				setSpriteSize(stringToVec2u(str_spritesize));
			}
		}
	}

	void TileMapParser::fileToMap(std::fstream& file)
	{
		const char* token_pos = "Pos";
		const char* token_id = "ID";

		const size_t& npos = std::string::npos;

		Vec2u tile_pos;
		std::string buff;
		while (!file.eof())
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
				if (auto tile = getTile(tile_pos).lock())
				{
					tile->setID(id);
				}
				else
				{
					PEACH_CORE_WARN("Level::convertFile(...), La posizione del Tile {} va oltre la grandezza di TileMap {}", tile_pos, getSize());
					continue;
				}
			}

			if (found == npos)
			{
				std::getline(file, buff);
			}
		}
	}

	bool TileMapParser::isEnd(const std::string& buff) const
	{
		return buff == "END";
	}

	bool TileMapParser::find(const std::string& buff, const std::string& find) const
	{
		return buff.find(find + ' ') != std::string::npos;
	}

	uint32_t TileMapParser::nextUInt(const std::string& buff) const
	{
		bool in = false;
		std::string id;

		for (const char& c : buff)
		{
			if (isdigit(c))
			{
				in = true;
				id += c;
			}
			else if (in)
			{
				break;
			}
		}

		return stoi(id);
	}

	Vec2u TileMapParser::stringToVec2u(const std::string& str) const
	{
		bool in_x = false, in_y = false;
		std::string x, y;

		for (const char& c : str)
		{
			if (c == '[')
			{
				if (in_x || in_y)
				{
					break;
				}

				in_x = true;
				continue;
			}
			else if (c == ']')
			{
				break;
			}

			if (!in_x && !in_y)
			{
				continue;
			}

			if (isdigit(c))
			{
				std::string& append = in_x ? x : y;

				append += c;
			}
			else if (c == ',')
			{
				in_x = false;
				in_y = true;
			}
		}

		Vec2u out;
		out.x = x.empty() ? 0 : stoi(x);
		out.y = y.empty() ? 0 : stoi(y);

		return out;
	}

	Vec2f TileMapParser::stringToVec2f(const std::string& str) const
	{
		bool in_x = false, in_y = false;
		std::string x, y;

		for (const char& c : str)
		{
			if (c == '[')
			{
				if (in_x || in_y)
				{
					break;
				}

				in_x = true;
				continue;
			}
			else if (c == ']')
			{
				break;
			}

			if (!in_x && !in_y)
			{
				continue;
			}

			if (isdigit(c) || c == '.' || c == '-')
			{
				std::string& append = in_x ? x : y;

				append += c;
			}
			else if (c == ',')
			{
				in_x = false;
				in_y = true;
			}
		}

		Vec2f out;
		out.x = x.empty() ? 0 : stof(x);
		out.y = y.empty() ? 0 : stof(y);

		return out;
	}
}