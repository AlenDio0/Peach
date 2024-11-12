#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class Entity : public GameObject, public sf::Drawable
	{
	public:
		Entity();
		Entity(const sf::Texture& texture);

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
