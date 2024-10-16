#pragma once

#include "Peach/Core.h"

#include "Peach/System.h"
#include <SFML/Graphics/Texture.hpp>

namespace Peach
{
	using SpriteID = uint32_t;

	class PEACH_API SpriteSheet
	{
	public:
		SpriteSheet(const sf::Texture& texture, const Vec2u spritesize);

		void setTexture(const sf::Texture& texture);
		void setSpriteSize(const Vec2u& spritesize);

		const SpriteID& getMaxID() const;
		IntRect getRect(const SpriteID& id) const;
	private:
		const sf::Texture* m_Texture;
		Vec2u m_SpriteSize;
		Vec2u m_Size;
	private:
		void adjustSize();
	};
}
