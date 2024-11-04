#pragma once

#include "Tile/TileMap.h"

#include <filesystem>
#include <fstream>

namespace Peach
{
	class PEACH_API Level
	{
	public:
		Level() = default;
		Level(const std::filesystem::path& filepath, const sf::Texture& texture);

		void convertFile(const std::filesystem::path& filepath);

		void setTileTexture(const sf::Texture& texture, bool resetrect = false);

		void render(sf::RenderTarget* target) const;
	private:
		TileMap m_TileMap;
	private:
		void fileToTileMap(std::fstream& file);
		void fileToMap(std::fstream& file);

		bool isEnd(const std::string& buff) const;

		bool find(const std::string& buff, const std::string& find) const;

		uint32_t nextUInt(const std::string& buff) const;

		Vec2u stringToVec2u(const std::string& str) const;
		Vec2f stringToVec2f(const std::string& str) const;
	};
}
