#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Button : public GuiObject
	{
	public:
		Button(const Vec2f size, const sf::String& label, const sf::Font& font);
		virtual ~Button() override;

		virtual void setPosition(const Vec2f position) override;
		virtual void setSize(const Vec2f size) override;
		void setLabel(const sf::String& label);
		void setCharSize(const uint32_t size);
		void setFont(const sf::Font& font);
		void setLabelStyle(const sf::Text::Style style);

		const sf::String& getLabel() const;

		virtual void handleSpecEvent(const sf::Event& event) override;
		void onMouseMovedEvent(const sf::Event::MouseMoveEvent event);
		void onMousePressedEvent(const sf::Event::MouseButtonEvent event);

		virtual void update(const float deltaTime) override;
		virtual void render(sf::RenderTarget& target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;

		bool m_Hover;
	};
}
