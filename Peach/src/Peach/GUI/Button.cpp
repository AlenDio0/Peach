#include "peachpch.h"
#include "Button.h"

namespace Peach
{
	Button::Button(const sf::Vector2f& size, const sf::String& label, const sf::Font& font)
		: GUIObject(m_Container), m_TextLabel(label, font), m_State(State::IDLE)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void Button::setState(State state)
	{
		m_State = state;
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

	void Button::onHover()
	{
		setState(State::HOVER);
	}

	void Button::onPressed()
	{
		setState(State::PRESSED);

		callback();
	}

	const sf::Vector2f& Button::getSize() const
	{
		return m_Container.getSize();
	}

	const sf::String& Button::getLabel() const
	{
		return m_TextLabel.getString();
	}

	GUIType Button::getStaticType()
	{
		return GUIType::Button;
	}

	GUIType Button::getType() const
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

			setState(State::HOVER);
			break;
		}
	}

	void Button::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);
		target->draw(m_TextLabel);
	}
}
