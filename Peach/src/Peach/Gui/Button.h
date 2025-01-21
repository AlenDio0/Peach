#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Button : public GuiObject
	{
	public:
		Button(Vec2f size, const sf::String& label, const sf::Font& font);
		virtual ~Button() override;

		virtual void setPosition(Vec2f position) override;
		virtual void setSize(Vec2f size) override;
		void setLabel(const sf::String& label);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);
		void setLabelStyle(sf::Text::Style style);

		const sf::String& getLabel() const;

		virtual void handleSpecEvent(sf::Event event) override;
		void onMouseMovedEvent(sf::Event::MouseMoveEvent event);
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;

		bool m_Hover;
	};
}
