#include "peachpch.h"
#include "GameObject.h"

namespace Peach
{
	GameObject::GameObject()
		: GameObject(sf::Texture())
	{
	}

	GameObject::GameObject(const sf::Texture& texture)
		: Entity(false)
	{
		setTexture(texture, true);

		addComponent<Transform>();
	}

	void GameObject::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_Sprite.setTexture(texture, resetrect);
	}

	void GameObject::setTextureRect(IntRect rect)
	{
		m_Sprite.setTextureRect(rect);
	}

	Transform GameObject::getTransform() const
	{
		return *has<Transform>().lock();
	}

	Transform& GameObject::getTransform()
	{
		return *has<Transform>().lock();
	}

	void GameObject::setPosition(Vec2f position)
	{
		getTransform().position = position;
	}

	void GameObject::setScale(Vec2f scale)
	{
		getTransform().scale = scale;
	}

	void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const auto& [position, scale] = getTransform();

		states.transform.translate(position);
		states.transform.scale(scale);

		target.draw(m_Sprite, states);
	}
}
