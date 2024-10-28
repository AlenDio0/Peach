#pragma once

#include "Button.h"

#include "GUIObject.h"

namespace Peach
{
	class PEACH_API Checkbox : public GUIObject
	{
	public:
		Checkbox(const sf::Vector2f& size, bool active = false);
		~Checkbox() = default;

		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setCheckTexture(const sf::Texture& texture);

		const sf::Vector2f& getSize() const;
		bool isActive() const;

		virtual void handleEvent(const sf::Event& event);
		void onMousePressedEvent(const sf::Event::MouseButtonEvent& event);

		static GUIType getStaticType();
		GUIType getType() const;

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		sf::RectangleShape m_Container;
		sf::Sprite m_Check;

		bool m_Active;
	};
}
