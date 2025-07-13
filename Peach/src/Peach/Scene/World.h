#pragma once

#include "Peach/Core/Core.h"

#include "Tile/TileMap.h"
#include "Scene.h"

namespace Peach
{
	class World
	{
	public:
		World(Scene* scene, std::filesystem::path mapFile, const Peach::Texture& mapTexture);
		virtual ~World() = default;

	private:
		TileMap m_TileMap;

		Scene* m_Scene;
	};
}
