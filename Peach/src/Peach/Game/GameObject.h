#pragma once

#include "Peach/Core/Core.h"

#include "Components.h"
#include <SFML/Graphics.hpp>
#include "Peach/Core/Log.h"

namespace Peach
{
	class PEACH_API GameObject
	{
	public:
		GameObject();
		GameObject(const sf::Texture& texture, RigidBody body, bool dynamic = false, bool debuglog = true);
		virtual ~GameObject();

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setTextureRect(IntRect rect);

		void setPosition(Vec2f position);
		void setScale(Vec2f scale);
		void setHitBox(FloatRect hitbox);

		virtual void update() {}
		virtual void render(sf::RenderTarget* target) const;
	protected:
		void renderSprite(sf::RenderTarget* target) const;
	private:
		RigidBody m_Body;
		sf::Sprite m_Sprite;
		bool m_DebugLog;

		bool m_Dynamic;
	};
}
