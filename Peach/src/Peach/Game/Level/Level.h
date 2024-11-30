#pragma once

#include "Tile/TileMap.h"

#include "Peach/Game/Entity.h"
#include "Peach/System/UUID.h"

#include <unordered_map>

namespace Peach
{
    using EntityMap = std::unordered_map<UUID, Ref<Entity>>;
    class PEACH_API Level
    {
    public:
        Level();
        Level(TileMap&& tilemap);
        virtual ~Level();

        UUID addEntity(Ref<Entity> entity);
        UUID addEntity(Entity* entity);

        void removeEntity(UUID uuid);
        void removeEntity(Ref<Entity> entity);
        void removeEntity(Entity* entity);

        const TileMap& getTileMap() const;
        TileMap& getTileMap();
        const EntityMap& getEntities() const;
        EntityMap& getEntities();
        std::weak_ptr<Entity> getEntity(UUID uuid) const;

        virtual void update();
        virtual void render(sf::RenderTarget* target) const;
    private:
        TileMap m_TileMap;
        EntityMap m_Entities;
    }
}
