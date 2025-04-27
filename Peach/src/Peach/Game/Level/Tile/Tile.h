#pragma once

#include "Peach/Game/GameObject.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const sf::Texture& texture, const std::function<void(Tile&)>& changedId = nullptr);
		virtual ~Tile() = default;

		void setID(size_t id);

		size_t getID() const;

		RigidBody getRigidBody() const;
		RigidBody& getRigidBody();

		virtual void update(const float deltaTime) override {}
	private:
		std::function<void(Tile&)> m_ChangedID;
	};
}
