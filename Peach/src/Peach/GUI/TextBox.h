#pragma once

#include "Peach/Core.h"

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API TextBox : public GuiObject
	{
	public:
		TextBox(const sf::Vector2f& size, const sf::Font& font, bool selected);
		TextBox(const sf::Vector2f& size, const sf::Font& font, size_t length, bool selected);
		TextBox(const sf::Vector2f& size, const sf::Font& font, const std::string& placeholder, bool selected);
		TextBox(const sf::Vector2f& size, const sf::Font& font, const std::string& placeholder, size_t length, bool selected);
		~TextBox() = default;

		void setIndex(size_t index);
		void setSelected(bool selected);
		void setRestriction(const std::function<bool(char)> restriciton, bool space = true);
		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setPlaceholder(const std::string& placeholder);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);

		virtual void handleEvent(const sf::Event& event);
		void onMousePressedEvent(const sf::Event::MouseButtonEvent& event);
		void onTextEnteredEvent(sf::Event::TextEvent event);
		void onKeyPressedEvent(sf::Event::KeyEvent event);

		std::string getBuff() const;
		size_t getBuffSize() const;
		const sf::Vector2f& getSize() const;

		size_t calcMaxLength() const;

		bool isOverLimit() const;

		GuiType getType() const;

		void update();
		void render(sf::RenderTarget* target) const;
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
