#pragma once

#include "GuiObject.h"

#include <sstream>

namespace Peach
{
	class PEACH_API TextBox : public GuiObject
	{
	public:
		TextBox(const Vec2f size, const sf::Font& font, bool selected);
		TextBox(const Vec2f size, const sf::Font& font, const size_t length, bool selected);
		TextBox(const Vec2f size, const sf::Font& font, const std::string_view placeholder, bool selected);
		TextBox(const Vec2f size, const sf::Font& font, const std::string_view placeholder, const size_t length, bool selected);
		virtual ~TextBox() override;

		void setIndex(const size_t index);
		void setSelected(bool selected);
		void setRestriction(const std::function<bool(int)>& restriciton, bool space = true);
		virtual void setSize(const Vec2f size) override;
		virtual void setPosition(const Vec2f position) override;
		void setPlaceholder(const std::string_view placeHolder);
		void setCharSize(const uint32_t size);
		void setFont(const sf::Font& font);

		std::string getBuff() const;
		size_t getBuffSize() const;
		bool isOverLimit() const;
		size_t calcMaxLength() const;

		virtual void handleSpecEvent(const sf::Event& event) override;
		void onMousePressedEvent(const sf::Event::MouseButtonEvent event);
		void onTextEnteredEvent(const sf::Event::TextEvent event);
		void onKeyPressedEvent(const sf::Event::KeyEvent event);

		virtual void update(const float deltaTime) override;
		virtual void render(sf::RenderTarget& target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;
		sf::RectangleShape m_Indicator;

		std::string m_Placeholder;
		std::ostringstream m_Buff;
		size_t m_Length;

		std::function<bool(int)> m_Restriction;
		bool m_Space;

		size_t m_Index;
		bool m_Selected;
		bool m_Blink;
		sf::Clock m_BlinkTimer;
	private:
		enum
		{
			DELETE_KEY = 8,
			ENTER_KEY = 13,
			ESCAPE_KEY = 27,
		};
	};
}
