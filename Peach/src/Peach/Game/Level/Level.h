#pragma once

#include "Tile/TileMap.h"

#include "Peach/Game/Entity/EntityManager.h"
#include "Peach/System/UUID.h"

#include <unordered_map>

namespace Peach
{
	class PEACH_API Level
	{
	public:
		Level();
		Level(TileMap&& tilemap);
		virtual ~Level();

		const TileMap& getTileMap() const;
		TileMap& getTileMap();
		const EntityManager& getEntityManager() const;
		EntityManager& getEntityManager();

		virtual void update();
		virtual void render(sf::RenderTarget* target) const;
	private:
		TileMap m_TileMap;
		EntityManager m_EntityManager;
	};
}
