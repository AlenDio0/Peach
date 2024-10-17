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
		enum Token
		{
			TileMap,
			Map
		};

		auto getVec2u = [](const std::string& str) -> Vec2u
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
			};
		auto getVec2f = [](const std::string& str) -> Vec2f
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

					if (isdigit(c) || c == '.')
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
			};

		const auto& npos = std::string::npos;

		std::fstream file(filepath, std::ios::in);
		while (!file.eof())
		{
			std::string buff;
			std::getline(file, buff);

			if (buff.find("START") == npos)
			{
				continue;
			}

			std::string token_str = buff.substr(6);

			if (token_str == "TileMap")
			{
				while (!file.eof())
				{
					std::getline(file, buff);
					if (buff == "END")
					{
						break;
					}

					if (buff.find("MapSize") != npos)
					{
						m_TileMap.setSize(getVec2u(buff.substr(strlen("MapSize"))));
					}
					else if (buff.find("TileSize") != npos)
					{
						m_TileMap.setTileSize(getVec2f(buff.substr(strlen("TileSize"))));
					}
					else if (buff.find("SpriteSize") != npos)
					{
						m_TileMap.setSpriteSize(getVec2u(buff.substr(strlen("SpriteSize"))));
					}
				}
			}
			else if (token_str == "Map")
			{
				Vec2u tile_pos;

				while (!file.eof())
				{
					if (buff == "END")
					{
						break;
					}

					size_t found;
					if (found = buff.find("Pos") != npos)
					{
						std::string pos = buff;
						for (size_t i = 0; i < pos.size(); ++i)
						{
							if (pos[i] == ']')
							{
								buff = pos.substr(i + 1);
								break;
							}
						}

						tile_pos = getVec2u(pos);
					}
					if (found = buff.find("ID") != npos)
					{
						buff = buff.substr(found + 2);

						bool in = false;
						std::string id;
						for (const auto& c : buff)
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

						auto& tile = m_TileMap.getTile(tile_pos);
						if (!tile)
						{
							PEACH_CORE_WARN("Level::convertFile(...), La posizione del Tile {} va oltre la grandezza di TileMap {}", tile_pos, m_TileMap.getSize());
							continue;
						}

						tile->setID(stoi(id));
					}

					if (found == npos || found == 0)
					{
						std::getline(file, buff);
					}
				}
			}
		}

		m_TileMap.update();
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