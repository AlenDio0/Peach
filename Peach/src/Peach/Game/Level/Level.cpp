#include "peachpch.h"
#include "Level.h"

namespace Peach
{
	Level::Level(const std::filesystem::path& filepath, const sf::Texture& texture)
		: m_TileMap(texture)
	{
		convertFile(filepath);
	}

	void Level::convertFile(const std::filesystem::path& filepath)
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

	void Level::setTileTexture(const sf::Texture& texture, bool resetrect)
	{
		m_TileMap.setTexture(texture, resetrect);
	}

	void Level::render(sf::RenderTarget* target) const
	{
		m_TileMap.render(target);
	}

	void Level::fileToTileMap(std::fstream& file)
	{
		static const char token_mapsize[] = "MapSize";
		static const char token_tilesize[] = "TileSize";
		static const char token_spritesize[] = "SpriteSize";

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
				m_TileMap.setSize(stringToVec2u(str_mapsize));
			}
			else if (find(buff, token_tilesize))
			{
				const std::string str_tilesize = buff.substr(strlen(token_tilesize));
				m_TileMap.setTileSize(stringToVec2f(str_tilesize));
			}
			else if (find(buff, token_spritesize))
			{
				const std::string str_spritesize = buff.substr(strlen(token_spritesize));
				m_TileMap.setSpriteSize(stringToVec2u(str_spritesize));
			}
		}
	}

	void Level::fileToMap(std::fstream& file)
	{
		static const char token_pos[] = "Pos";
		static const char token_id[] = "ID";

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
				if (auto tile = m_TileMap.getTile(tile_pos).lock())
				{
					tile->setID(id);
				}
				else
				{
					PEACH_CORE_WARN("Level::convertFile(...), La posizione del Tile {} va oltre la grandezza di TileMap {}", tile_pos, m_TileMap.getSize());
					continue;
				}
			}

			if (found == npos)
			{
				std::getline(file, buff);
			}
		}
	}

	bool Level::isEnd(const std::string& buff) const
	{
		return buff == "END";
	}

	bool Level::find(const std::string& buff, const std::string& find) const
	{
		return buff.find(find + ' ') != std::string::npos;
	}

	uint32_t Level::nextUInt(const std::string& buff) const
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

	Vec2u Level::stringToVec2u(const std::string& str) const
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

	Vec2f Level::stringToVec2f(const std::string& str) const
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