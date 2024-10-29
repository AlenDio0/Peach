#include "peachpch.h"
#include "Button.h"

namespace Peach
{
	Button::Button(const sf::Vector2f& size, const sf::String& label, const sf::Font& font)
		: GuiObject(m_Container), m_TextLabel(label, font), m_State(State::IDLE)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		m_Container.setPosition(position);
		m_TextLabel.setPosition
		(
			floor(position.x + ((getSize().x - m_TextLabel.getGlobalBounds().getSize().x) / 2.f) - 2.f),
			floor(position.y + ((getSize().y / 2.f) - m_TextLabel.getGlobalBounds().getSize().y))
		);
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		m_Container.setSize(size);
		setCharSize((sf::Uint32)(size.y / 1.75f));

		setPosition(getPosition());
	}

	void Button::setLabel(const sf::String& label)
	{
		m_TextLabel.setString(label);
	}

	void Button::setCharSize(uint32_t size)
	{
		m_TextLabel.setCharacterSize(size);

		setPosition(getPosition());
	}

	void Button::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);

		setPosition(getPosition());
	}

	void Button::setLabelStyle(sf::Text::Style style)
	{
		m_TextLabel.setStyle(style);

		setPosition(getPosition());
	}

	void Button::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseMoved:
			onMouseMovedEvent(event.mouseMove);
			break;
		case sf::Event::MouseButtonPressed:
			onMousePressedEvent(event.mouseButton);
			break;
		}
	}

	void Button::onMouseMovedEvent(const sf::Event::MouseMoveEvent& event)
	{
		if (isCursorOn({ event.x, event.y }))
		{
			m_State = State::HOVER;
		}
		else
		{
			m_State = State::IDLE;
		}
	}

	void Button::onMousePressedEvent(const sf::Event::MouseButtonEvent& event)
	{
		if (event.button != sf::Mouse::Button::Left)
		{
			return;
		}

		if (isCursorOn({ event.x, event.y }))
		{
			m_State = State::PRESSED;

			callback();
		}
	}

	const sf::Vector2f& Button::getSize() const
	{
		return m_Container.getSize();
	}

	const sf::String& Button::getLabel() const
	{
		return m_TextLabel.getString();
	}

	GuiType Button::getStaticType()
	{
		return GuiType::Button;
	}

	GuiType Button::getType() const
	{
		return getStaticType();
	}

	void Button::update()
	{
		switch (m_State)
		{
		case State::IDLE:
			if (m_Container.getOutlineColor() == getSecondaryColor())
			{
				break;
			}

			m_Container.setFillColor(getPrimaryColor());
			m_Container.setOutlineColor(getSecondaryColor());
			m_TextLabel.setFillColor(getSecondaryColor());
			break;
		case State::HOVER:
			if (m_TextLabel.getFillColor() == getPrimaryColor())
			{
				break;
			}

			m_Container.setFillColor(getSecondaryColor());
			m_Container.setOutlineColor(getPrimaryColor());
			m_TextLabel.setFillColor(getPrimaryColor());
			break;
		case State::PRESSED:
			m_Container.setFillColor(getSecondaryColor());
			m_Container.setOutlineColor(getPrimaryColor());
			m_TextLabel.setFillColor(getPrimaryColor());

			m_State = State::HOVER;
			break;
		}
	}

	void Button::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);
		target->draw(m_TextLabel);
	}
}
