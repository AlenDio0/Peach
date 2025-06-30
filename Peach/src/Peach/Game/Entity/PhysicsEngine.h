#pragma once

#include "Peach/Game/Level/Level.h"

namespace Peach
{
	class PEACH_API PhysicsEngine
	{
	public:
		PhysicsEngine();
		PhysicsEngine(TileMap& tilemap);
		PhysicsEngine(EntityManager& entitymanager);
		PhysicsEngine(Level& level);
		PhysicsEngine(TileMap& tilemap, EntityManager& entitymanager);
		~PhysicsEngine() = default;


		void setMapCollision(bool collide);
		void setEntitiesCollision(bool collide);
		void setGravity(float gravity);
		void setDrag(float drag);

		bool isMapCollision() const;
		bool isEntitiesCollision() const;
		float getDrag() const;
		float getGravity() const;

		void update(const float deltaTime);
		void renderBoxes(sf::RenderTarget& target) const;
	private:
		struct Box
		{
			Box(Vec2f& position, const FloatRect& hitbox)
				: position(position), hitbox(hitbox) {
			}

			bool isColliding(const Box& r) const
			{
				return position.x + hitbox.x < r.position.x + r.hitbox.max().x &&	// LEFT-RIGHT
					position.x + hitbox.max().x > r.position.x + r.hitbox.x &&		// RIGHT-LEFT
					position.y + hitbox.y < r.position.y + r.hitbox.max().y &&		// TOP-BOTTOM
					position.y + hitbox.max().y > r.position.y + r.hitbox.y;		// BOTTOM-TOP
			}

			void operator=(const Box& r) {}

			Vec2f& position;
			FloatRect hitbox;
		};
		struct PhysicsBox
		{
			PhysicsBox(Box& box, Ref<Movement> movement)
				: box(box), movement(movement) {
			}

			PhysicsBox& operator=(const PhysicsBox& r)
			{
				box = r.box;
				movement = r.movement;
				return *this;
			}

			Box box;
			Ref<Movement> movement;
		};
	private:
		void updateLinearMovement(LinearMovement& movement) const;
		void updateAccelerationMovement(AccelerationMovement& movement) const;

		void addNearTiles(const PhysicsBox& prime, std::vector<Box>& boxes) const;
		void addNearBoxes(const PhysicsBox& prime, const std::vector<PhysicsBox>& physicsboxes, std::vector<Box>& boxes) const;

		void updateCollisions(PhysicsBox& prime, const std::vector<Box>& boxes);
	private:
		TileMap* m_TileMap;
		EntityManager* m_EntityManager;

		float m_Gravity;
		float m_Drag;

		bool m_MapCollision;
		bool m_EntitiesCollision;

		std::vector<PhysicsBox> m_PhysicsBoxes;
		std::vector<Box> m_Boxes;
	};

}