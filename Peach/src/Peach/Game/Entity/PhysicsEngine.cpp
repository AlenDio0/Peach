#include "peachpch.h"
#include "PhysicsEngine.h"

namespace Peach
{
	PhysicsEngine::PhysicsEngine()
		: PhysicsEngine(TileMap(), EntityManager())
	{
	}

	PhysicsEngine::PhysicsEngine(TileMap& tilemap)
		: PhysicsEngine(tilemap, EntityManager())
	{
	}

	PhysicsEngine::PhysicsEngine(EntityManager& entitymanager)
		: PhysicsEngine(TileMap(), entitymanager)
	{
	}

	PhysicsEngine::PhysicsEngine(TileMap& tilemap, EntityManager& entitymanager)
		: m_TileMap(&tilemap), m_EntityManager(&entitymanager),
		m_Gravity(0.4f), m_Drag(0.89f), m_MapCollision(true), m_EntitiesCollision(true)
	{
	}

	void PhysicsEngine::setMapCollision(bool collide)
	{
		m_MapCollision = collide;
	}

	void PhysicsEngine::setEntitiesCollision(bool collide)
	{
		m_EntitiesCollision = collide;
	}

	void PhysicsEngine::setGravity(float gravity)
	{
		m_Gravity = gravity;
	}

	void PhysicsEngine::setDrag(float drag)
	{
		m_Drag = drag;
	}

	bool PhysicsEngine::getMapCollisions() const
	{
		return m_MapCollision;
	}

	bool PhysicsEngine::getEntitiesCollisions() const
	{
		return m_EntitiesCollision;
	}

	float PhysicsEngine::getDrag() const
	{
		return m_Drag;
	}

	float PhysicsEngine::getGravity() const
	{
		return m_Gravity;
	}

	void PhysicsEngine::update()
	{
		if (!m_EntityManager)
		{
			return;
		}

		std::vector<PhysicsBox> physics_boxes;
		for (auto& [uuid, entity] : m_EntityManager->getEntities())
		{
			auto entity_transform = entity->has<Transform>().lock();
			auto entity_body = entity->has<RigidBody>().lock();
			auto entity_physics = entity->has<Movement>().lock();
			if (!entity_body || !entity_transform || !entity_physics)
			{
				continue;
			}

			if (!entity_body->collide)
			{
				continue;
			}

			physics_boxes.emplace_back(Box(entity_transform->position, entity_body->hitbox), *entity_physics);
		}

		m_PhysicsBoxes.clear();
		m_PhysicsBoxes = physics_boxes;

		for (auto& [box, movement] : physics_boxes)
		{
			updateMovement(movement);
		}

		m_Boxes.clear();
		std::vector<Box> collisions_boxes;
		for (auto& physics_box : physics_boxes)
		{
			collisions_boxes.clear();

			// Add collisions with near Tiles in TileMap
			addNearTiles(physics_box, collisions_boxes);

			// Add collisions with near entities
			addNearBoxes(physics_box, physics_boxes, collisions_boxes);

			updateCollisions(physics_box, collisions_boxes);
		}
		m_Boxes = collisions_boxes;
	}

	void PhysicsEngine::renderBoxes(sf::RenderTarget* target) const
	{
		for (const auto& [box, movement] : m_PhysicsBoxes)
		{
			sf::RectangleShape box_shape(box.hitbox.size);
			box_shape.setPosition(box.position + box.hitbox.position);
			box_shape.setFillColor(sf::Color::Transparent);
			box_shape.setOutlineThickness(2.f);
			box_shape.setOutlineColor(sf::Color::Blue);

			target->draw(box_shape);
		}
		for (const auto& box : m_Boxes)
		{
			sf::RectangleShape box_shape(box.hitbox.size);
			box_shape.setPosition(box.position + box.hitbox.x);
			box_shape.setFillColor(sf::Color::Transparent);
			box_shape.setOutlineThickness(2.f);
			box_shape.setOutlineColor(sf::Color::Red);

			target->draw(box_shape);
		}
	}

	void PhysicsEngine::updateMovement(Movement& movement) const
	{
		auto& [velocity, minvelocity, maxvelocity, acceleration] = movement;

		// Add gravity
		velocity.y += m_Gravity;

		// Add drag
		velocity *= m_Drag;

		if (std::abs(velocity.x) > maxvelocity.x)
		{
			velocity.x = (velocity.x < 0.f ? -1.f : 1.f) * maxvelocity.x;
		}
		if (std::abs(velocity.y) > maxvelocity.y)
		{
			velocity.y = (velocity.y < 0.f ? -1.f : 1.f) * maxvelocity.y;
		}

		if (std::abs(velocity.x) < minvelocity.x)
		{
			velocity.x = 0.f;
		}
		if (std::abs(velocity.y) < minvelocity.y)
		{
			velocity.y = 0.f;
		}
	}

	void PhysicsEngine::addNearTiles(const PhysicsBox& prime, std::vector<Box>& boxes) const
	{
		if (m_TileMap)
		{
			const Vec2f& tile_size = m_TileMap->getTileSize();

			Vec2i relative_position = ((prime.box.position + prime.box.hitbox.position) / tile_size) - 2;
			Vec2i relative_boxsize = ((prime.box.position + prime.box.hitbox.position + prime.box.hitbox.size) / tile_size) + 2;

			auto tiles_grid = m_TileMap->getTiles(IntRect(relative_position, relative_boxsize));
			for (auto& [pos, t] : tiles_grid)
			{
				auto tile = t.lock();
				if (!tile)
				{
					continue;
				}
				auto tile_transform = tile->has<Transform>().lock();
				auto tile_body = tile->has<RigidBody>().lock();
				if (!tile_transform || !tile_body)
				{
					continue;
				}

				if (!tile_body->collide)
				{
					continue;
				}

				boxes.emplace_back(tile_transform->position, tile_body->hitbox);
			}
		}
	}

	void PhysicsEngine::addNearBoxes(const PhysicsBox& prime, const std::vector<PhysicsBox>& physicsboxes, std::vector<Box>& boxes) const
	{
		for (auto& [box, movement] : physicsboxes)
		{
			if (&prime.box == &box)
			{
				continue;
			}

			auto [x1, y1] = prime.box.position;
			auto [x2, y2] = box.position;
			Vec2f distance(std::abs(x2 - x1), std::abs(y2 - y1));

			if (distance > prime.box.hitbox.size || distance > box.hitbox.size)
			{
				continue;
			}

			boxes.emplace_back(box.position, box.hitbox);
		}
	}

	void PhysicsEngine::updateCollisions(PhysicsBox& prime, const std::vector<Box>& boxes)
	{
		prime.box.position.x += prime.movement.velocity.x;
		for (const auto& box : boxes)
		{
			if (!prime.box.isColliding(box))
			{
				continue;
			}

			auto& [velocity, _, __, ___] = prime.movement;
			if (velocity.x > 0.f)
			{
				prime.box.position.x = box.position.x - prime.box.hitbox.width - prime.box.hitbox.x;
				velocity.x = 0.f;
			}
			else if (velocity.x < 0.f)
			{
				prime.box.position.x = box.position.x + box.hitbox.width - prime.box.hitbox.x;
				velocity.x = 0.f;
			}
		}

		prime.box.position.y += prime.movement.velocity.y;
		for (const auto& box : boxes)
		{
			if (!prime.box.isColliding(box))
			{
				continue;
			}

			auto& [velocity, _, __, ___] = prime.movement;
			if (velocity.y > 0.f)
			{
				prime.box.position.y = box.position.y - prime.box.hitbox.height - prime.box.hitbox.y;
				velocity.y = 0.f;
			}
			else if (velocity.y < 0.f)
			{
				prime.box.position.y = box.position.y + box.hitbox.height - prime.box.hitbox.y;
				velocity.y = 0.f;
			}
		}
	}
}
