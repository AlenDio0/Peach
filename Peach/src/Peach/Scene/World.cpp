#include "peachpch.h"
#include "World.h"

#include "Tile/TileMapParser.h"

namespace Peach
{
	World::World(Scene* scene, std::filesystem::path mapFile, const Peach::Texture& mapTexture)
		: m_TileMap(TileMapParser::parse(mapFile, scene, mapTexture)), m_Scene(scene)
	{
	}
}
