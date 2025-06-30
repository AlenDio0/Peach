#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const sf::Texture& texture, const std::function<void(Tile&)>& changedId)
		: GameObject(texture), m_ChangedID(changedId)
	{
		setTexture(texture);

		addComponent<IDComp>(0);
		addComponent<RigidBodyComp>(FloatRect(), false);
	}

	void Tile::setID(size_t id)
	{
		has<IDComp>().lock()->id = id;

		if (m_ChangedID)
		{
			m_ChangedID(*this);
		}
	}

	size_t Tile::getID() const
	{
		return has<IDComp>().lock()->id;
	}

	RigidBodyComp Tile::getRigidBody() const
	{
		return *has<RigidBodyComp>().lock();
	}

	RigidBodyComp& Tile::getRigidBody()
	{
		return *has<RigidBodyComp>().lock();
	}
}