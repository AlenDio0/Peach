#include "peachpch.h"
#include "GameObject.h"

namespace Peach
{
	GameObject::GameObject(Vec2f position, FloatRect hitbox)
	{
		PEACH_CORE_TRACE("GameObject costruito");

		setPosition(position);
		setHitbox(hitbox);
	}

	GameObject::~GameObject()
	{
		PEACH_CORE_TRACE("GameObject distrutto");
	}

	void GameObject::setPosition(const Vec2f& position)
	{
		m_Position = position;
	}

	void GameObject::setHitbox(const FloatRect& hitbox)
	{
		m_Hitbox = hitbox;
	}

	void GameObject::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_Shape.setTexture(&texture, resetrect);
	}

	void GameObject::setTextureRect(const IntRect& rect)
	{
		m_Shape.setTextureRect(rect);
	}

	const Vec2f& GameObject::getPosition() const
	{
		return m_Position;
	}

	const FloatRect& GameObject::getHitbox() const
	{
		return m_Hitbox;
	}

	void GameObject::update()
	{
		m_Shape.setPosition(m_Position);
	}

	void GameObject::render(sf::RenderTarget* target)
	{
		target->draw(m_Shape);
	}
}