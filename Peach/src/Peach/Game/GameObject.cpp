#include "peachpch.h"
#include "GameObject.h"

namespace Peach
{
	GameObject::GameObject()
		: GameObject(sf::Texture()) {
	}

	GameObject::GameObject(const sf::Texture& texture)
		: Entity(false)
	{
		m_Sprite.setTexture(texture, true);

		addComponent<TransformComp>(Vec2f(), Vec2f(1.f, 1.f));
	}

	void GameObject::setTexture(const sf::Texture& texture, bool resetRect)
	{
		m_Sprite.setTexture(texture, resetRect);
	}

	void GameObject::setTextureRect(const IntRect rect)
	{
		m_Sprite.setTextureRect(rect);
	}

	Vec2f GameObject::getLocalSize() const
	{
		return m_Sprite.getLocalBounds().getSize();
	}

	Vec2f GameObject::getGlobalSize() const
	{
		return getLocalSize() * getTransform().scale;
	}

	TransformComp GameObject::getTransform() const
	{
		return *has<TransformComp>().lock();
	}

	TransformComp& GameObject::getTransform()
	{
		return *has<TransformComp>().lock();
	}

	void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		const auto& [position, scale] = getTransform();

		states.transform.translate(position);
		states.transform.scale(scale);

		target.draw(m_Sprite, states);
	}
}
