#pragma once

#include "Peach/Core.h"

#include "Peach/System.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API GameObject
	{
	public:
		GameObject(Vec2f position = {}, FloatRect hitbox = {});
		virtual ~GameObject();

		void setPosition(const Vec2f& position);
		void setHitbox(const FloatRect& hitbox);
		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setTextureRect(const IntRect& rect);

		const Vec2f& getPosition() const;
		const FloatRect& getHitbox() const;

		virtual void update();
		virtual void render(sf::RenderTarget* target);
	protected:
		sf::RectangleShape m_Shape;
	private:
		Vec2f m_Position;
		FloatRect m_Hitbox;
	};
}
