#include "peachpch.h"
#include "GameObject.h"

namespace Peach
{
	GameObject::GameObject()
		: GameObject({}, {})
	{
	}

	GameObject::GameObject(const sf::Texture& texture, RigidBody body, bool dynamic, bool debuglog)
		: m_Sprite(texture), m_Body(body), m_Dynamic(dynamic), m_DebugLog(debuglog)
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GameObject costruito");
		}
	}

	GameObject::~GameObject()
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GameObject distrutto");
		}
	}

	void GameObject::setTexture(const sf::Texture& texture, bool resetrect)
	{
		m_Sprite.setTexture(texture, resetrect);
	}

	void GameObject::setTextureRect(IntRect rect)
	{
		m_Sprite.setTextureRect(rect);
	}

	void GameObject::setPosition(Vec2f position)
	{
		m_Body.transform.position = position;

		if (!m_Dynamic)
		{
			m_Sprite.setPosition(position);
		}
	}

	void GameObject::setScale(Vec2f scale)
	{
		m_Body.transform.scale = scale;

		if (!m_Dynamic)
		{
			m_Sprite.setScale(scale);
		}
	}

	void GameObject::setHitBox(FloatRect hitbox)
	{
		m_Body.hitbox = hitbox;
	}

	void GameObject::render(sf::RenderTarget* target) const
	{
		renderSprite(target);
	}

	void GameObject::renderSprite(sf::RenderTarget* target) const
	{
		target->draw(m_Sprite);
	}
}