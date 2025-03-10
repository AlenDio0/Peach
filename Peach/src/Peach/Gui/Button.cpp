#include "peachpch.h"
#include "Button.h"

namespace Peach
{
	Button::Button(const Vec2f size, const sf::String& label, const sf::Font& font)
		: GuiObject(m_Container, false), m_TextLabel(label, font), m_Hover(false)
	{
		PEACH_CORE_TRACE("Button costruito");

		setSize(size);

		setPosition({ 0, 0 });
	}

	Button::~Button()
	{
		PEACH_CORE_TRACE("Button distrutto");
	}

	void Button::setPosition(const Vec2f position)
	{
		m_Container.setPosition(position);
		m_TextLabel.setPosition
		(
			floor(position.x + ((getSize().x - m_TextLabel.getGlobalBounds().getSize().x) / 2.f) - 2.f),
			floor(position.y + ((getSize().y / 2.f) - m_TextLabel.getGlobalBounds().getSize().y))
		);
	}

	void Button::setSize(const Vec2f size)
	{
		m_Container.setSize(size);
		setCharSize((sf::Uint32)(size.y / 1.75f));

		setPosition(getPosition());
	}

	void Button::setLabel(const sf::String& label)
	{
		m_TextLabel.setString(label);
	}

	void Button::setCharSize(const uint32_t size)
	{
		m_TextLabel.setCharacterSize(size);

		setPosition(getPosition());
	}

	void Button::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);

		setPosition(getPosition());
	}

	void Button::setLabelStyle(const sf::Text::Style style)
	{
		m_TextLabel.setStyle(style);

		setPosition(getPosition());
	}

	const sf::String& Button::getLabel() const
	{
		return m_TextLabel.getString();
	}

	void Button::handleSpecEvent(const sf::Event& event)
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

	void Button::onMouseMovedEvent(const sf::Event::MouseMoveEvent event)
	{
		if (isCursorOn(event))
		{
			m_Hover = true;
		}
		else
		{
			m_Hover = false;
		}
	}

	void Button::onMousePressedEvent(const sf::Event::MouseButtonEvent event)
	{
		if (isCursorOn(event))
		{
			m_Hover = false;
		}
	}

	void Button::update(const float deltaTime)
	{
		const auto [_, primary, secondary, background] = getAppearance();
		sf::Color inverted_background = sf::Color(primary.r, primary.g, primary.b, 200u);

		m_Container.setOutlineColor(secondary);

		if (m_Hover)
		{
			m_TextLabel.setFillColor(background);
			m_Container.setFillColor(inverted_background);

			return;
		}

		m_TextLabel.setFillColor(primary);
		m_Container.setFillColor(background);
	}

	void Button::render(sf::RenderTarget& target) const
	{
		target.draw(m_Container);
		target.draw(m_TextLabel);
	}
}
