#include "peachpch.h"
#include "Checkbox.h"

namespace Peach
{
	Checkbox::Checkbox(const sf::Vector2f& size, bool active)
		: GuiObject(m_Container), m_Active(active)
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

	const sf::Vector2f& Checkbox::getSize() const
	{
		return m_Container.getSize();
	}

	bool Checkbox::isActive() const
	{
		return m_Active;
	}

	void Checkbox::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			onMousePressedEvent(event.mouseButton);
			break;
		}
	}

	void Checkbox::onMousePressedEvent(const sf::Event::MouseButtonEvent& event)
	{
		if (event.button != sf::Mouse::Button::Left)
		{
			return;
		}

		if (isCursorOn({ event.x, event.y }))
		{
			m_Active = !m_Active;

			callback();
		}
	}

	GuiType Checkbox::getStaticType()
	{
		return GuiType::Checkbox;
	}

	GuiType Checkbox::getType() const
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
