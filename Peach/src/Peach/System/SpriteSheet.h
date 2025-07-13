#pragma once

#include "Peach/Core/Core.h"

#include "Peach/Assets/Asset.h"
#include <SFML/Graphics/Texture.hpp>

namespace Peach
{
	class PEACH_API SpriteSheet
	{
	public:
		SpriteSheet(const Peach::Texture& texture, const Vec2u& spritesize);

		void setTexture(const Peach::Texture& texture);
		void setSpriteSize(const Vec2u& spritesize);

		const Peach::Texture& getTexture() const;
		const Vec2u& getSpriteSize() const;
		const Vec2u& getSize() const;

		size_t getMaxID() const;
		IntRect getRect(const size_t id) const;
	private:
		const Peach::Texture* m_Texture;
		Vec2u m_SpriteSize;
		Vec2u m_Size;
	private:
		void adjustSize();
	};
}
