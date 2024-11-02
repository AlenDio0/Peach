#include "peachpch.h"
#include "SpriteSheet.h"

namespace Peach
{
	SpriteSheet::SpriteSheet(const sf::Texture& texture, const Vec2u& spritesize)
		: m_SpriteSize(spritesize)
	{
		setTexture(texture);
	}

	void SpriteSheet::setTexture(const sf::Texture& texture)
	{
		m_Texture = &texture;
		adjustSize();
	}

	void SpriteSheet::setSpriteSize(const Vec2u& spritesize)
	{
		m_SpriteSize = spritesize;
		adjustSize();
	}

	const sf::Texture& SpriteSheet::getTexture() const
	{
		return *m_Texture;
	}

	const Vec2u& SpriteSheet::getSpriteSize() const
	{
		return m_SpriteSize;
	}

	const Vec2u& SpriteSheet::getSize() const
	{
		return m_Size;
	}

	SpriteID SpriteSheet::getMaxID() const
	{
		return m_Size.x * m_Size.y;
	}

	IntRect SpriteSheet::getRect(SpriteID id) const
	{
		const int& max = getMaxID();

		if ((int)id >= max)
		{
			PEACH_CORE_WARN("SpriteSheet::getRect(id: {}), ID fuori dal range [maxid: {}], ritornato l'ultimo ID", id, max);
			return getRect(max - 1);
		}

		const Vec2u& position = { id % m_Size.x, id / m_Size.x };

		return IntRect(position * m_SpriteSize, m_SpriteSize);
	}

	void SpriteSheet::adjustSize()
	{
		m_Size = (Vec2u)m_Texture->getSize() / m_SpriteSize;
	}
}
