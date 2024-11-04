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

		virtual void setPosition(const sf::Vector2f& position) override;
		virtual void setSize(const sf::Vector2f& size) override;
		void setLabel(const sf::String& label);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);
		void setLabelStyle(sf::Text::Style style);

		virtual void handleEvent(const sf::Event& event) override;
		void onMouseMovedEvent(const sf::Event::MouseMoveEvent& event);
		void onMousePressedEvent(const sf::Event::MouseButtonEvent& event);

		const sf::Vector2f& getSize() const;
		const sf::String& getLabel() const;

		virtual GuiType getType() const override;

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;

		State m_State;
	};
}
