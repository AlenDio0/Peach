#pragma once

#include "Button.h"

#include "GUIObject.h"

namespace Peach
{
	class PEACH_API Checkbox : public GUIObject
	{
	public:
		Checkbox(const sf::Vector2f& size);
		~Checkbox() = default;

		void setActive(const bool& active);
		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setCheckTexture(const sf::Texture& texture);

		const bool& getActive() const;
		const sf::Vector2f& getSize() const;

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
