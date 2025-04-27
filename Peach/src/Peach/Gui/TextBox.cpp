#include "peachpch.h"
#include "TextBox.h"

namespace Peach
{
	TextBox::TextBox(const Vec2f size, const sf::Font& font, bool selected)
		: TextBox(size, font, 0, selected) {
	}

	TextBox::TextBox(const Vec2f size, const sf::Font& font, const size_t length, bool selected)
		: TextBox(size, font, "", length, selected) {
	}

	TextBox::TextBox(const Vec2f size, const sf::Font& font, const std::string_view placeholder, bool selected)
		: TextBox(size, font, placeholder, 0, selected) {
	}

	TextBox::TextBox(const Vec2f size, const sf::Font& font, const std::string_view placeholder, const size_t length, bool selected)
		: GuiObject(m_Container, false), m_TextLabel("", font), m_Placeholder(placeholder), m_Length(length), m_Space(true), m_Selected(selected), m_Blink(false)
	{
		PEACH_CORE_TRACE("TextBox costruito");

		m_Indicator.setOutlineThickness(1.f);
		m_Indicator.setFillColor(sf::Color::White);
		m_Indicator.setOutlineColor(sf::Color::Black);

		setSize(size);

		setPosition({});
		setIndex(0);

		if (m_Length == 0)
		{
			setLength(calcMaxLength(), true);
		}
		else
		{
			setCharSize(calcMaxCharSize(), true);
		}
	}

	TextBox::~TextBox()
	{
		PEACH_CORE_TRACE("TextBox distrutto");
	}

	void TextBox::setBuff(const std::string& buff)
	{
		if (getBuff() != buff)
		{
			m_Buff.str("");
			m_Buff << buff;
		}

		m_TextLabel.setString(getBuff());
		setPosition(getPosition());
	}

	void TextBox::setIndex(const size_t index)
	{
		if (!(index >= 0 && index <= getBuffLength()))
		{
			return;
		}
		if (m_Index == index)
		{
			return;
		}

		m_Index = index;

		setPosition(getPosition());

		m_Blink = true;
		m_BlinkTimer.restart();
	}

	void TextBox::setSelected(bool selected)
	{
		m_Selected = selected;

		setBuff(getBuff());
	}

	void TextBox::setRestriction(const std::function<bool(int)>& restriciton, bool space)
	{
		m_Restriction = restriciton;
		m_Space = space;
	}

	void TextBox::setSize(const Vec2f size)
	{
		m_Container.setSize(size);
		setCharSize(size.y / 1.75f, true);

		setPosition(getPosition());
	}

	void TextBox::setPosition(const Vec2f position)
	{
		m_Container.setPosition(position);
		m_TextLabel.setPosition
		(
			floor(position.x + ((getSize().x / 2.f) - (m_TextLabel.getGlobalBounds().getSize().x / 2.f)) - 1.f),
			floor(position.y + ((getSize().y / 2.f) - (m_TextLabel.getCharacterSize() / 1.75f)))
		);

		const auto [x, y] = m_TextLabel.findCharacterPos(m_Index);
		m_Indicator.setPosition(x, y + 5.f);
	}

	void TextBox::setPlaceholder(const std::string_view placeholder)
	{
		m_Placeholder = placeholder;
	}

	void TextBox::setCharSize(const uint32_t size, bool force, bool adjustLength)
	{
		if (force)
		{
			m_TextLabel.setCharacterSize(size);
		}
		else
		{
			uint32_t max = calcMaxCharSize();
			m_TextLabel.setCharacterSize(size > max ? max : size);
		}

		m_Indicator.setSize({ 1.5f, (float)size - 2.f });

		if (adjustLength)
		{
			setLength(calcMaxLength());
		}
	}

	void TextBox::setLength(const size_t length, bool truncate, bool force, bool adjustCharSize)
	{
		size_t lastLength = m_Length;
		if (force)
		{
			m_Length = length;
		}
		else
		{
			size_t max = calcMaxLength();
			m_Length = length > max ? max : length;
		}

		if (m_Index > m_Length)
		{
			setIndex(m_Length);
		}

		if (truncate && lastLength > m_Length)
		{
			setBuff(m_Buff.str().substr(0, m_Length));
		}

		if (adjustCharSize)
		{
			setCharSize(calcMaxCharSize());
		}
	}

	void TextBox::setFont(const sf::Font& font)
	{
		m_TextLabel.setFont(font);
	}

	void TextBox::handleSpecEvent(const sf::Event& event)
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

	void TextBox::onMousePressedEvent(const sf::Event::MouseButtonEvent event)
	{
		const auto& [button, x, y] = event;
		if (!isCursorOn(event) || button != sf::Mouse::Button::Left)
		{
			setSelected(false);
			return;
		}

		if (!getBuff().empty())
		{
			for (size_t i = 0; i <= getBuffLength(); ++i)
			{
				const bool isFirst = i == 0;
				const bool isLast = i == getBuffLength();
				bool isOnMouse = false;

				if (!isLast)
				{
					const float relative_mouse_x = x + (m_TextLabel.getGlobalBounds().width / (float)(getBuffLength() * 2));
					const float char_x = m_TextLabel.findCharacterPos(i).x;
					const float next_char_x = m_TextLabel.findCharacterPos(i + 1).x;

					const bool isInbounds = relative_mouse_x >= char_x && relative_mouse_x <= next_char_x;
					const bool isBefore = relative_mouse_x <= char_x && isFirst;

					isOnMouse = isInbounds || isBefore;
				}

				if (isOnMouse || isLast)
				{
					setIndex(i);
					break;
				}
			}
		}

		if (!m_Selected)
		{
			setSelected(true);
		}
	}

	void TextBox::onTextEnteredEvent(const sf::Event::TextEvent event)
	{
		uint32_t input = event.unicode;

		bool isDelete = input == DELETE_KEY;

		if (!m_Selected)
		{
			return;
		}
		if ((isOverLimit() && !isDelete))
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
					m_Blink = true;
					return;
				}
			}

			if (m_Index == getBuffLength())
			{
				m_Buff << (char)input;
				setIndex(m_Index + 1);
				break;
			}

			std::string firstHalf = getBuff().substr(0, m_Index);
			firstHalf += (char)input;
			std::string secondHalf = getBuff().substr(m_Index);

			setBuff(firstHalf.append(secondHalf));
			setIndex(m_Index + 1);
			break;
		}
		case DELETE_KEY:
		{
			if (getBuff().empty() || m_Index == 0)
			{
				return;
			}

			std::string firstHalf = getBuff().substr(0, m_Index - 1);
			std::string secondHalf = getBuff().substr(m_Index);

			setBuff(firstHalf.append(secondHalf));
			setIndex(m_Index - 1);
		}
		break;
		case ESCAPE_KEY:
		case ENTER_KEY:
			setSelected(false);
			return;
		}

		setBuff(getBuff());

		m_BlinkTimer.restart();
	}

	void TextBox::onKeyPressedEvent(const sf::Event::KeyEvent event)
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
			setIndex(getBuffLength());
			break;
		case sf::Keyboard::Key::BackSpace:
			if (event.control)
			{
				if (getBuff().empty() || m_Index == 0)
				{
					break;
				}

				setBuff(getBuff().substr(m_Index));
				setIndex(0);
			}
			break;
		}
	}

	std::string TextBox::getBuff() const
	{
		return m_Buff.str();
	}

	size_t TextBox::getBuffLength() const
	{
		return getBuff().length();
	}

	size_t TextBox::getIndex() const
	{
		return m_Index;
	}

	bool TextBox::isSelected() const
	{
		return m_Selected;
	}

	const std::string& TextBox::getPlaceholder() const
	{
		return m_Placeholder;
	}

	size_t TextBox::calcMaxLength() const
	{
		return (size_t)floor(m_Container.getSize().x / (m_TextLabel.getCharacterSize() / 1.75f));
	}

	uint32_t TextBox::calcMaxCharSize() const
	{
		return (uint32_t)floor(m_Container.getSize().x / (m_Length / 1.75f));
	}

	bool TextBox::isOverLimit() const
	{
		return getBuffLength() >= m_Length;
	}

	void TextBox::update(const float deltaTime)
	{
		const auto [_, primary, secondary, background] = getAppearance();
		sf::Color placeholderColor = sf::Color(primary.r, primary.g, primary.b, 140u);

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
				m_TextLabel.setFillColor(placeholderColor);
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

	void TextBox::render(sf::RenderTarget& target) const
	{
		target.draw(m_Container);
		target.draw(m_TextLabel);

		if (m_Blink && m_Selected)
		{
			target.draw(m_Indicator);
		}
	}
}
