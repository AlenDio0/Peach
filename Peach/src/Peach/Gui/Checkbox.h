#pragma once

#include "GuiObject.h"

namespace Peach
{
	class PEACH_API Checkbox : public GuiObject
	{
	public:
		Checkbox(const sf::Vector2f& size, bool active = false);
		~Checkbox();

		virtual void setSize(const sf::Vector2f& size) override;
		virtual void setPosition(const sf::Vector2f& position) override;
		void setCheckTexture(const sf::Texture& texture);

		const sf::Vector2f& getSize() const;
		bool isActive() const;

		virtual void handleEvent(const sf::Event& event) override;
		void onMousePressedEvent(const sf::Event::MouseButtonEvent& event);

		virtual GuiType getType() const override;

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::RectangleShape m_Container;
		sf::Sprite m_Check;

		bool m_Active;
	};
}
