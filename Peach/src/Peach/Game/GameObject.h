#pragma once

#include "Entity.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API GameObject : public Entity, public sf::Drawable
	{
	public:
		GameObject();
		GameObject(const sf::Texture& texture);

		virtual void setTexture(const sf::Texture& texture, bool resetrect = false);
		virtual void setTextureRect(IntRect rect);

		virtual void setPosition(Vec2f position);
		virtual void setScale(Vec2f scale);

		Transform& getTransform();
		Transform getTransform() const;

		virtual void update() override = 0;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Sprite m_Sprite;
	};
}
