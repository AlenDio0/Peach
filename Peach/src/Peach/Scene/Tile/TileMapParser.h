#pragma once

#include "Peach/System/Parser.h"

#include "TileMap.h"

namespace Peach
{
	class TileMapParser : public Parser
	{
	public:
		TileMapParser() = delete;
		~TileMapParser() = delete;

		static TileMap parse(const std::filesystem::path& filePath, Scene* scene, const Peach::Texture& texture);
	private:
		struct MapInfo
		{
			Vec2u mapSize;
			Vec2f tileSize;
			Vec2u spriteSize;
			std::vector<uint32_t> collideIDs;
		};
	private:
		static MapInfo convertMap();
		static std::map<Vec2u, uint32_t> convertTileMap(MapInfo mapInfo);
	};
}
