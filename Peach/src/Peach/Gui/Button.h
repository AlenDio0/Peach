#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Button : public GuiObject
	{
	public:
		enum class State
		{
			IDLE = 0,
			HOVER,
			PRESSED
		};
	public:
		Button(const sf::Vector2f& size, const sf::String& label, const sf::Font& font);
		~Button();

		void setPosition(const sf::Vector2f& position);
		void setSize(const sf::Vector2f& size);
		void setLabel(const sf::String& label);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);
		void setLabelStyle(sf::Text::Style style);

		virtual void handleEvent(const sf::Event& event);
		void onMouseMovedEvent(const sf::Event::MouseMoveEvent& event);
		void onMousePressedEvent(const sf::Event::MouseButtonEvent& event);

		const sf::Vector2f& getSize() const;
		const sf::String& getLabel() const;

		GuiType getType() const;

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;

		State m_State;
	};
}
