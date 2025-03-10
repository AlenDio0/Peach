#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Checkbox : public GuiObject
	{
	public:
		Checkbox(const Vec2f size, const sf::Texture& texture, bool active = false);
		virtual ~Checkbox() override;

		virtual void setSize(const Vec2f size) override;
		virtual void setPosition(const Vec2f position) override;
		void setCheckTexture(const sf::Texture& texture);

		bool isActive() const;

		virtual void handleSpecEvent(const sf::Event& event) override;
		void onMousePressedEvent(const sf::Event::MouseButtonEvent event);

		virtual void update(const float deltaTime) override;
		virtual void render(sf::RenderTarget& target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Sprite m_Check;

		bool m_Active;
	};
}
