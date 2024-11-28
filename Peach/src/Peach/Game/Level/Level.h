#pragma once

#include "Tile/TileMap.h"

#include "Peach/Game/Entity.h"
#include "Peach/System/UUID.h"

#include <unordered_map>

namespace Peach
{
    class PEACH_API Level
    {
    public:
        Level();
        Level(TileMap&& tilemap);
        
        UUID addEntity(Ref<Entity> entity);
        void removeEntity(Ref<Entity> entity);
        void removeEntity(UUID uuid);

        const TileMap& getTileMap() const;
        TileMap& getTileMap();


        void update();
        void render(sf::RenderTarget* target) const;
    private:
        TileMap m_TileMap;
        std::unordered_map<UUID, Ref<Entity>> m_Entities;
    }
}
