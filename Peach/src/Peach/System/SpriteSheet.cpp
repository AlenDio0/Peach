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

	size_t SpriteSheet::getMaxID() const
	{
		return Vec2<size_t>(m_Size).area();
	}

	IntRect SpriteSheet::getRect(size_t id) const
	{
		int64_t max = getMaxID();

		if ((int64_t)id >= max)
		{
			PEACH_CORE_WARN("SpriteSheet::getRect(id: {}), ID fuori dal range [maxid: {}], ritornato l'ultimo ID", id, max);
			return getRect(max - 1);
		}

		Vec2u position = Vec2u((uint32_t)id % m_Size.x, (uint32_t)id / m_Size.x);

		return IntRect(position * m_SpriteSize, m_SpriteSize);
	}

	void SpriteSheet::adjustSize()
	{
		m_Size = (Vec2u)m_Texture->getSize() / m_SpriteSize;
	}
}
