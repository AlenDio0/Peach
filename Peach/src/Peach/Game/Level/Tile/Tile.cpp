#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const sf::Texture& texture, RigidBody body, std::function<void(Tile&)> changedid, bool debuglog)
		: GameObject(texture, body, false, debuglog), m_ID(0), m_ChangedID(changedid)
	{
	}

	void Tile::setID(TileID id)
	{
		if (m_ID == id)
		{
			return;
		}

		m_ID = id;

		if (m_ChangedID)
		{
			m_ChangedID(*this);
		}
	}

	TileID Tile::getID() const
	{
		return m_ID;
	}
}