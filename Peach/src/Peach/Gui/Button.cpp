#include "peachpch.h"
#include "Button.h"

namespace Peach
{
	Button::Button(const sf::Vector2f& size, const sf::String& label, const sf::Font& font)
		: GuiObject(m_Container, false), m_TextLabel(label, font), m_State(State::IDLE)
	{
		PEACH_CORE_TRACE("Button costruito");

		setSize(size);

		setPosition({ 0, 0 });
	}

	Button::~Button()
	{
		PEACH_CORE_TRACE("Button distrutto");
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

	GuiType Button::getType() const
	{
		return GuiType::Button;
	}

	void Button::update()
	{
		const auto [_, primary, secondary, background] = getAppearance();
		sf::Color inverted_background = sf::Color(primary.r, primary.g, primary.b, 200u);

		switch (m_State)
		{
		case State::IDLE:
			m_TextLabel.setFillColor(primary);
			m_Container.setOutlineColor(secondary);
			m_Container.setFillColor(background);
			break;
		case State::HOVER:
			m_TextLabel.setFillColor(background);
			m_Container.setOutlineColor(secondary);
			m_Container.setFillColor(inverted_background);
			break;
		case State::PRESSED:
			m_TextLabel.setFillColor(background);
			m_Container.setOutlineColor(secondary);
			m_Container.setFillColor(inverted_background);

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
