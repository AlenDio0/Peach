#include "peachpch.h"
#include "Checkbox.h"

namespace Peach
{
	Checkbox::Checkbox(const sf::Vector2f& size)
		: GUIObject(m_Container), m_Active(false)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void Checkbox::setActive(const bool& active)
	{
		m_Active = active;
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

	const bool& Checkbox::getActive() const
	{
		return m_Active;
	}

	const sf::Vector2f& Checkbox::getSize() const
	{
		return m_Container.getSize();
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
		if (m_Container.getFillColor() != m_PrimaryColor)
		{
			m_Container.setFillColor(m_PrimaryColor);
		}

		if (m_Container.getOutlineColor() != m_SecondaryColor)
		{
			m_Container.setOutlineColor(m_SecondaryColor);
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
