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
	};
}
