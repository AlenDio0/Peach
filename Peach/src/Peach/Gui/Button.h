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
		Button(Vec2f size, const sf::String& label, const sf::Font& font);
		~Button();

		virtual void setPosition(Vec2f position) override;
		virtual void setSize(Vec2f size) override;
		void setLabel(const sf::String& label);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);
		void setLabelStyle(sf::Text::Style style);

		const sf::String& getLabel() const;

		virtual void handleEvent(sf::Event event) override;
		void onMouseMovedEvent(sf::Event::MouseMoveEvent event);
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);

		virtual GuiType getType() const override;

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;

		State m_State;
	};
}
