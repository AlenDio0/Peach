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
						// m_TileMap.setSpriteSize(getVec2u(buff.substr(strlen("SpriteSize"))));
					}
				}
			}
			else if (token_str == "Map")
			{
				Vec2u tile_pos;

				while (!file.eof())
				{
					file >> buff;
					if (buff == "END")
					{
						break;
					}

					if (size_t found = buff.find("Pos") != npos)
					{
						std::string pos;
						std::getline(file, pos);

						pos = pos.substr(found);
						for (size_t i = 0; i < pos.size(); ++i)
						{
							if (pos[i] == ']')
							{
								pos = pos.substr(0, i + 1);
								break;
							}
						}

						tile_pos = getVec2u(pos);
					}
					else if (buff.find("ID") != npos)
					{
						TileID id;
						file >> id;

						m_TileMap.getTile(tile_pos)->setID(id);
					}
				}
			}
		}

		/*
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
		*/
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