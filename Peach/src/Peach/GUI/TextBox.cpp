#include "peachpch.h"
#include "TextBox.h"

namespace Peach
{
	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, bool selected)
		: TextBox(size, font, 16, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, const size_t& length, bool selected)
		: TextBox(size, "", font, length, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const std::string& placeholder, const sf::Font& font, const size_t& length, bool selected)
		: GUIObject(m_Container), m_Placeholder(placeholder), m_TextLabel("", font), m_Length(length), m_Selected(selected)
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

	void TextBox::setRestriction(Restriction restriction)
	{
		m_Restriction = restriction;
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

	void TextBox::setCharSize(const sf::Uint32& size)
	{
		m_TextLabel.setCharacterSize(size);
	}

	void TextBox::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);
	}

	std::string TextBox::getBuff() const
	{
		return m_Buff.str();
	}

	const sf::Vector2f& TextBox::getSize() const
	{
		return m_Container.getSize();
	}

	GUIType TextBox::getStaticType()
	{
		return GUIType::TextBox;
	}

	GUIType TextBox::getType() const
	{
		return getStaticType();
	}

	void TextBox::onTextEntered(const uint32_t& input)
	{
		const bool& is_char = input < 128;
		const bool& over_limit = m_Buff.str().size() >= m_Length;
		const bool& is_delete = input == DELETE_KEY;

		if (!m_Selected || !is_char || (over_limit && !is_delete))
		{
			return;
		}

		switch (input)
		{
		case ESCAPE_KEY:
		case ENTER_KEY:
			setSelected(false);
			return;
		case DELETE_KEY:
		{
			if (m_Buff.str().empty())
			{
				return;
			}
			const size_t& size = m_Buff.str().size();
			std::string sub = m_Buff.str().substr(0, size - 1);

			m_Buff.str("");
			m_Buff << sub;
		}
		break;
		default:
			if (input != ' ')
			{
				switch (m_Restriction)
				{
				case Restriction::Regular:
					if (input < ' ')
					{
						return;
					}
					break;
				case Restriction::AlphaDigit:
					if (!isalnum(input))
					{
						return;
					}
					break;
				case Restriction::Alpha:
					if (!isalpha(input))
					{
						return;
					}
					break;
				case Restriction::Digit:
					if (!isdigit(input))
					{
						return;
					}
					break;
				}
			}
			m_Buff << (char)input;
			break;
		}

		m_TextLabel.setString(m_Buff.str());
		setPosition(getPosition());

		m_BlinkTimer.restart();
	}

	void TextBox::update()
	{
		m_Container.setOutlineColor(m_SecondaryColor);
		m_Container.setOutlineColor(m_PrimaryColor);
		m_TextLabel.setFillColor(m_SecondaryColor);

		if (!m_Selected)
		{
			if (m_Buff.str().empty())
			{
				m_TextLabel.setStyle(sf::Text::Style::Italic);
				m_TextLabel.setFillColor({ 128, 128, 128 });
				m_TextLabel.setString(m_Placeholder);
				setPosition(getPosition());
			}
			else
			{
				m_TextLabel.setStyle(sf::Text::Style::Regular);
				m_TextLabel.setFillColor(m_PrimaryColor);
			}

			return;
		}

		if (m_BlinkTimer.getElapsedTime().asMilliseconds() >= 500)
		{
			static bool blink = false;
			blink = !blink;

			m_BlinkTimer.restart();

			if (blink)
			{
				m_TextLabel.setString(m_Buff.str() + "|");
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
