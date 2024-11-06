#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API TextBox : public GuiObject
	{
	public:
		TextBox(Vec2f size, const sf::Font& font, bool selected);
		TextBox(Vec2f size, const sf::Font& font, size_t length, bool selected);
		TextBox(Vec2f size, const sf::Font& font, const std::string& placeholder, bool selected);
		TextBox(Vec2f size, const sf::Font& font, const std::string& placeholder, size_t length, bool selected);
		~TextBox();

		void setIndex(size_t index);
		void setSelected(bool selected);
		void setRestriction(const std::function<bool(char)> restriciton, bool space = true);
		virtual void setSize(Vec2f size) override;
		virtual void setPosition(Vec2f position) override;
		void setPlaceholder(const std::string& placeholder);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);

		std::string getBuff() const;
		size_t getBuffSize() const;
		bool isOverLimit() const;
		size_t calcMaxLength() const;

		virtual void handleEvent(sf::Event event) override;
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);
		void onTextEnteredEvent(sf::Event::TextEvent event);
		void onKeyPressedEvent(sf::Event::KeyEvent event);

		virtual GuiType getType() const override;

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;
		sf::RectangleShape m_Indicator;

		std::string m_Placeholder;
		std::ostringstream m_Buff;
		size_t m_Length;

		std::function<bool(char)> m_Restriction;
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
