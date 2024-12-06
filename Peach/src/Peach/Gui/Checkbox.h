#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Checkbox : public GuiObject
	{
	public:
		Checkbox(Vec2f size, const sf::Texture& texture, bool active = false);
		~Checkbox();

		virtual void setSize(Vec2f size) override;
		virtual void setPosition(Vec2f position) override;
		void setCheckTexture(const sf::Texture& texture);

		const sf::Vector2f& getSize() const;
		bool isActive() const;

		virtual void handleSpecEvent(sf::Event event) override;
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Sprite m_Check;

		bool m_Active;
	};
}
