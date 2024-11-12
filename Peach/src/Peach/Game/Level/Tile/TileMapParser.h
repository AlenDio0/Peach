#pragma once

#include "TileMap.h"

#include <filesystem>
#include <fstream>

namespace Peach
{
	class PEACH_API TileMapParser
	{
	public:
		TileMapParser() = delete;
		~TileMapParser() = delete;

		static TileMap&& parse(const std::filesystem::path& filepath, const sf::Texture& texture);
	private:
		static void fileToMap(std::fstream& file, TileMap& tilemap);
		static void fileToTileMap(std::fstream& file, TileMap& tilemap);

		static bool isEnd(const std::string& buff);

		static bool find(const std::string& buff, const std::string& find);

		static uint32_t nextUInt(const std::string& buff);

		static Vec2u stringToVec2u(const std::string& str);
		static Vec2f stringToVec2f(const std::string& str);
	};
}
