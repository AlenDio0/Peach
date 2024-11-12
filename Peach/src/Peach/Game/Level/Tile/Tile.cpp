#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const sf::Texture& texture, RigidBody body, std::function<void(Tile&)> changedid, bool debuglog)
		: GameObject(debuglog), m_ChangedID(changedid)
	{
		setTexture(texture);

		addComponent<RigidBody>(body);
		addComponent<ID>(0);
	}

	void Tile::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_Sprite.setTexture(texture);
	}

	void Tile::setTextureRect(IntRect rect)
	{
		m_Sprite.setTextureRect(rect);
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

	void Tile::update()
	{
		const auto& [position, scale] = has<RigidBody>().lock()->transform;

		m_Sprite.setPosition(position);
		m_Sprite.setScale(scale);
	}
	void Tile::render(sf::RenderTarget* target) const
	{
		target->draw(m_Sprite);
	}
}