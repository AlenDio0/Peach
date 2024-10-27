#include "peachpch.h"
#include "Checkbox.h"

namespace Peach
{
	Checkbox::Checkbox(const sf::Vector2f& size, const bool& active)
		: GUIObject(m_Container), m_Active(active)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void Checkbox::setSize(const sf::Vector2f& size)
	{
		m_Container.setSize(size);
		m_Check.setScale(size.x / m_Check.getTextureRect().width, size.y / m_Check.getTextureRect().height);
	}

	void Checkbox::setPosition(const sf::Vector2f& position)
	{
		m_Container.setPosition(position);
		m_Check.setPosition(position);
	}

	void Checkbox::setCheckTexture(const sf::Texture& texture)
	{
		m_Check.setTexture(texture);
		setSize(getSize());
	}

	void Checkbox::setActive(const bool& active)
	{
		m_Active = active;
	}

	const sf::Vector2f& Checkbox::getSize() const
	{
		return m_Container.getSize();
	}

	const bool& Checkbox::isActive() const
	{
		return m_Active;
	}

	void Checkbox::onPressed()
	{
		setActive(!m_Active);

		callback();
	}

	GUIType Checkbox::getStaticType()
	{
		return GUIType::Checkbox;
	}

	GUIType Checkbox::getType() const
	{
		return getStaticType();
	}

	void Checkbox::update()
	{
		if (m_Container.getFillColor() != getPrimaryColor())
		{
			m_Container.setFillColor(getPrimaryColor());
		}

		if (m_Container.getOutlineColor() != getSecondaryColor())
		{
			m_Container.setOutlineColor(getSecondaryColor());
		}
	}

	void Checkbox::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);

		if (m_Active)
		{
			target->draw(m_Check);
		}
	}
}
