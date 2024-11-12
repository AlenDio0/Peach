#include "peachpch.h"
#include "Entity.h"

namespace Peach
{
	Entity::Entity()
		: Entity(sf::Texture())
	{
	}

	Entity::Entity(const sf::Texture& texture)
		: GameObject(false)
	{
		setTexture(texture, true);

		addComponent<Transform>();
	}

	void Entity::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_Sprite.setTexture(texture, resetrect);
	}

	void Entity::setTextureRect(IntRect rect)
	{
		m_Sprite.setTextureRect(rect);
	}

	Transform Entity::getTransform() const
	{
		return *has<Transform>().lock();
	}

	Transform& Entity::getTransform()
	{
		return *has<Transform>().lock();
	}

	void Entity::setPosition(Vec2f position)
	{
		getTransform().position = position;
	}

	void Entity::setScale(Vec2f scale)
	{
		getTransform().scale = scale;
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const auto& [position, scale] = getTransform();

		states.transform.translate(position);
		states.transform.scale(scale);

		target.draw(m_Sprite, states);
	}
}
