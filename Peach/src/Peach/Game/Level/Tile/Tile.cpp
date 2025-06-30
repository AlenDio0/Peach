#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const sf::Texture& texture, const std::function<void(Tile&)>& changedId)
		: GameObject(texture), m_ChangedID(changedId)
	{
		setTexture(texture);

		addComponent<ID>(0);
		addComponent<RigidBody>(FloatRect(), false);
	}

	void Tile::setID(size_t id)
	{
		has<ID>().lock()->id = id;

		if (m_ChangedID)
		{
			m_ChangedID(*this);
		}
	}

	size_t Tile::getID() const
	{
		return has<ID>().lock()->id;
	}

	RigidBody Tile::getRigidBody() const
	{
		return *has<RigidBody>().lock();
	}

	RigidBody& Tile::getRigidBody()
	{
		return *has<RigidBody>().lock();
	}
}