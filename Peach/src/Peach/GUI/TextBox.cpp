#include "peachpch.h"
#include "TextBox.h"

namespace Peach
{
	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, bool selected)
		: TextBox(size, font, 16, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, size_t length, bool selected)
		: TextBox(size, "", font, length, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const std::string& placeholder, const sf::Font& font, size_t length, bool selected)
		: GuiObject(m_Container), m_Placeholder(placeholder), m_TextLabel("", font), m_Length(length), m_Space(true), m_Selected(selected)
	{
		setSize(size);

		setPosition({ 0, 0 });
	}

	void TextBox::setSelected(bool selected)
	{
		m_Selected = selected;

		m_TextLabel.setString(m_Buff.str());
		setPosition(getPosition());
	}

	void TextBox::setRestriction(const std::function<bool(char)> restriciton, bool space)
	{
		m_Restriction = restriciton;
		m_Space = space;
	}

	void TextBox::setSize(const sf::Vector2f& size)
	{
		m_Container.setSize(size);
		setCharSize((sf::Uint32)(size.y / 1.75f));

		setPosition(getPosition());
	}

	void TextBox::setPosition(const sf::Vector2f& position)
	{
		m_Container.setPosition(position);
		m_TextLabel.setPosition
		(
			floor(position.x + ((getSize().x / 2.f) - (m_TextLabel.getGlobalBounds().getSize().x / 2.f)) - 2.f),
			floor(position.y + ((getSize().y / 2.f) - (m_TextLabel.getCharacterSize() - 10.f)))
		);
	}

	void TextBox::setPlaceholder(const std::string& placeholder)
	{
		m_Placeholder = placeholder;
	}

	void TextBox::setCharSize(uint32_t size)
	{
		m_TextLabel.setCharacterSize(size);
	}

	void TextBox::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);
	}

	void TextBox::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			onMousePressedEvent(event.mouseButton);
			break;
		case sf::Event::TextEntered:
			onTextEnteredEvent(event.text);
			break;
		}
	}

	void TextBox::onMousePressedEvent(const sf::Event::MouseButtonEvent& event)
	{
		if (isCursorOn({ event.x, event.y }) && !m_Selected)
		{
			if (event.button != sf::Mouse::Button::Left)
			{
				return;
			}

			setSelected(true);

			callback();
		}
		else if (m_Selected)
		{
			setSelected(false);
		}
	}

	void TextBox::onTextEnteredEvent(sf::Event::TextEvent event)
	{
		uint32_t input = event.unicode;

		bool is_char = input < 128;
		bool is_delete = input == DELETE_KEY;

		if (!m_Selected || !is_char || (isOverLimit() && !is_delete))
		{
			return;
		}

		switch (input)
		{
		default:
			if (m_Restriction)
			{
				if (!(m_Restriction(input) || (input == ' ' && m_Space)))
				{
					return;
				}
			}

			m_Buff << (char)input;
			break;
		case ESCAPE_KEY:
		case ENTER_KEY:
			setSelected(false);
			return;
		case DELETE_KEY:
			if (m_Buff.str().empty())
			{
				return;
			}
			const size_t& size = m_Buff.str().size();
			std::string sub = m_Buff.str().substr(0, size - 1);

			m_Buff.str("");
			m_Buff << sub;
			break;
		}

		m_TextLabel.setString(m_Buff.str());
		setPosition(getPosition());

		m_BlinkTimer.restart();
	}

	std::string TextBox::getBuff() const
	{
		return m_Buff.str();
	}

	const sf::Vector2f& TextBox::getSize() const
	{
		return m_Container.getSize();
	}

	bool TextBox::isOverLimit() const
	{
		return m_Buff.str().size() >= m_Length;
	}

	GuiType TextBox::getType() const
	{
		return GuiType::TextBox;
	}

	void TextBox::update()
	{
		const auto [_, primary, secondary, background] = getAppearance();
		sf::Color placeholder_color = sf::Color(secondary.r, secondary.g, secondary.b, 140u);

		m_TextLabel.setFillColor(primary);
		m_Container.setOutlineColor(secondary);
		m_Container.setFillColor(background);

		if (!m_Buff.str().empty())
		{
			m_TextLabel.setStyle(sf::Text::Style::Regular);
			m_TextLabel.setFillColor(primary);
		}

		if (!m_Selected)
		{
			if (m_Buff.str().empty())
			{
				m_TextLabel.setStyle(sf::Text::Style::Italic);
				m_TextLabel.setFillColor(placeholder_color);
				m_TextLabel.setString(m_Placeholder);
				setPosition(getPosition());
			}

			return;
		}

		if (m_BlinkTimer.getElapsedTime().asMilliseconds() >= 500 && !isOverLimit())
		{
			static bool blink = false;
			blink = !blink;

			m_BlinkTimer.restart();

			if (blink)
			{
				m_TextLabel.setString(m_Buff.str() + '|');
			}
			else
			{
				m_TextLabel.setString(m_Buff.str());
			}
		}
	}

	void TextBox::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);
		target->draw(m_TextLabel);
	}
}
