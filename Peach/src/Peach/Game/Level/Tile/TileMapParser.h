#pragma once

#include "Peach/System/Parser.h"

#include "TileMap.h"

namespace Peach
{
	class PEACH_API TileMapParser : public Parser
	{
	public:
		TileMapParser() = delete;
		~TileMapParser() = delete;

		static TileMap&& parse(const std::filesystem::path& filepath, const sf::Texture& texture);
	private:
		static void fileToMap(TileMap& tilemap);
		static void fileToTileMap(TileMap& tilemap);
	};
}
