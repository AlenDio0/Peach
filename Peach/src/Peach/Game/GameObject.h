#pragma once

#include "Entity/Entity.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API GameObject : public Entity, public sf::Drawable
	{
	public:
		GameObject();
		GameObject(const sf::Texture& texture);

		virtual void setTexture(const sf::Texture& texture, bool resetRect = false);
		virtual void setTextureRect(const IntRect rect);

		Vec2f getLocalSize() const;
		Vec2f getGlobalSize() const;

		Transform& getTransform();
		Transform getTransform() const;

		virtual void update(const float deltaTime) override = 0;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Sprite m_Sprite;
	};
}
