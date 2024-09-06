#include "peachpch.h"
#include "Button.h"

namespace Peach
{
	Button::Button(const sf::Vector2f& size, const sf::String& label, const sf::Font* font)
		: GUIObject(m_Container), m_TextLabel(label, *font)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void Button::setSecondaryColor(const sf::Color& color)
	{
		m_Container.setOutlineColor(color);
		m_TextLabel.setFillColor(color);
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		m_Container.setPosition(position);
		m_TextLabel.setPosition
		(
			floor(position.x + (getSize().x - m_TextLabel.getGlobalBounds().getSize().x) / 2.f - 2.f),
			floor(position.y + ((getSize().y / 2.f) - (m_TextLabel.getGlobalBounds().getSize().y)))
		);
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		m_Container.setSize(size);
		setCharSize((sf::Uint32)((size.x * size.y) / (size.x * 1.75f)));

		setPosition(getPosition());
	}

	void Button::setLabel(const sf::String& label)
	{
		m_TextLabel.setString(label);
	}

	void Button::setCharSize(const sf::Uint32& size)
	{
		m_TextLabel.setCharacterSize(size);

		setPosition(getPosition());
	}

	void Button::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);

		setPosition(getPosition());
	}

	void Button::setLabelStyle(const sf::Text::Style& style)
	{
		m_TextLabel.setStyle(style);

		setPosition(getPosition());
	}

	const sf::Vector2f& Button::getSize() const
	{
		return m_Container.getSize();
	}

	const sf::String& Button::getLabel() const
	{
		return m_TextLabel.getString();
	}

	void Button::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);
		target->draw(m_TextLabel);
	}
}
