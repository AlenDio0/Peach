#include "peachpch.h"
#include "TextBox.h"

namespace Peach
{
	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, bool selected)
		: TextBox(size, font, 0, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, size_t length, bool selected)
		: TextBox(size, font, "", length, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, const std::string& placeholder, bool selected)
		: TextBox(size, font, placeholder, 0, selected)
	{
	}

	TextBox::TextBox(const sf::Vector2f& size, const sf::Font& font, const std::string& placeholder, size_t length, bool selected)
		: GuiObject(m_Container, false), m_TextLabel("", font), m_Placeholder(placeholder), m_Length(length), m_Space(true), m_Selected(selected), m_Blink(false)
	{
		PEACH_CORE_TRACE("Textbox costruito");

		m_Indicator.setOutlineThickness(1.f);
		m_Indicator.setFillColor(sf::Color::White);
		m_Indicator.setOutlineColor(sf::Color::Black);

		setSize(size);

		setPosition({ 0, 0 });
		setIndex(0);

		if (m_Length == 0)
		{
			m_Length = calcMaxLength();
		}
	}

	TextBox::~TextBox()
	{
		PEACH_CORE_TRACE("Textbox distrutto");
	}

	void TextBox::setIndex(size_t index)
	{
		if (index >= 0 && index <= getBuffSize() && m_Index != index)
		{
			m_Index = index;

			setPosition(getPosition());

			m_Blink = true;
			m_BlinkTimer.restart();
		}
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
			floor(position.x + ((getSize().x / 2.f) - (m_TextLabel.getGlobalBounds().getSize().x / 2.f)) - 1.f),
			floor(position.y + ((getSize().y / 2.f) - (m_TextLabel.getCharacterSize() / 1.75f)))
		);

		const auto [x, y] = m_TextLabel.findCharacterPos(m_Index);
		m_Indicator.setPosition(x, y + ((getSize().y / 2.f) - (m_Indicator.getSize().y / 1.25f)));
	}

	void TextBox::setPlaceholder(const std::string& placeholder)
	{
		m_Placeholder = placeholder;
	}

	void TextBox::setCharSize(uint32_t size)
	{
		m_TextLabel.setCharacterSize(size);

		m_Indicator.setSize({ 1.5f, (float)size - 2.f });
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
		case sf::Event::KeyPressed:
			onKeyPressedEvent(event.key);
			break;
		}
	}

	void TextBox::onMousePressedEvent(const sf::Event::MouseButtonEvent& event)
	{
		const auto& [button, x, y] = event;
		if (!isCursorOn({ x, y }) || button != sf::Mouse::Button::Left)
		{
			setSelected(false);
			return;
		}

		if (!getBuff().empty())
		{
			for (size_t i = 0; i <= getBuffSize(); ++i)
			{
				int char_x = (int)m_TextLabel.findCharacterPos(i).x + (int)m_TextLabel.getGlobalBounds().width / getBuffSize() / 2;
				if (x <= char_x)
				{
					setIndex(i);
					break;
				}
			}
		}

		if (!m_Selected)
		{
			setSelected(true);

			callback();
		}
	}

	void TextBox::onTextEnteredEvent(sf::Event::TextEvent event)
	{
		uint32_t input = event.unicode;

		bool is_ascii = input < 128;
		bool is_delete = input == DELETE_KEY;

		if (!m_Selected || !is_ascii || (isOverLimit() && !is_delete))
		{
			return;
		}

		switch (input)
		{
		default:
		{
			if (m_Restriction)
			{
				if (!(m_Restriction(input) || (input == ' ' && m_Space)))
				{
					return;
				}
			}

			if (m_Index == getBuffSize())
			{
				m_Buff << (char)input;
				setIndex(m_Index + 1);
				break;
			}

			std::string first_half = getBuff().substr(0, m_Index);
			first_half += (char)input;
			std::string second_half = getBuff().substr(m_Index);

			m_Buff.str("");
			m_Buff << first_half << second_half;

			setIndex(m_Index + 1);
			break;
		}
		case DELETE_KEY:
		{
			if (getBuff().empty() || m_Index == 0)
			{
				return;
			}

			std::string first_half = getBuff().substr(0, m_Index - 1);
			std::string second_half = getBuff().substr(m_Index);

			m_Buff.str("");
			m_Buff << first_half << second_half;

			setIndex(m_Index - 1);
		}
		break;
		case ESCAPE_KEY:
		case ENTER_KEY:
			setSelected(false);
			return;
		}

		m_TextLabel.setString(getBuff());
		setPosition(getPosition());

		m_BlinkTimer.restart();
	}

	void TextBox::onKeyPressedEvent(sf::Event::KeyEvent event)
	{
		if (!m_Selected)
		{
			return;
		}

		sf::Keyboard::Key input = event.code;

		switch (input)
		{
		case sf::Keyboard::Key::Right:
			setIndex(m_Index + 1);
			break;
		case sf::Keyboard::Key::Left:
			setIndex(m_Index - 1);
			break;
		case sf::Keyboard::Key::Up:
			setIndex(0);
			break;
		case sf::Keyboard::Key::Down:
			setIndex(getBuffSize());
			break;
		}
	}

	std::string TextBox::getBuff() const
	{
		return m_Buff.str();
	}

	size_t TextBox::getBuffSize() const
	{
		return getBuff().size();
	}

	const sf::Vector2f& TextBox::getSize() const
	{
		return m_Container.getSize();
	}

	size_t TextBox::calcMaxLength() const
	{
		return m_Container.getSize().x / (m_TextLabel.getCharacterSize() / 1.75f);
	}

	bool TextBox::isOverLimit() const
	{
		return getBuffSize() >= m_Length;
	}

	GuiType TextBox::getType() const
	{
		return GuiType::TextBox;
	}

	void TextBox::update()
	{
		const auto [_, primary, secondary, background] = getAppearance();
		sf::Color placeholder_color = sf::Color(primary.r, primary.g, primary.b, 140u);

		m_TextLabel.setFillColor(primary);
		m_Container.setOutlineColor(secondary);
		m_Container.setFillColor(background);

		if (!getBuff().empty())
		{
			m_TextLabel.setStyle(sf::Text::Style::Regular);
			m_TextLabel.setFillColor(primary);
		}

		if (!m_Selected)
		{
			if (getBuff().empty())
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
			m_Blink = !m_Blink;

			m_BlinkTimer.restart();
		}
	}

	void TextBox::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);
		target->draw(m_TextLabel);

		if (m_Blink && m_Selected)
		{
			target->draw(m_Indicator);
		}
	}
}
