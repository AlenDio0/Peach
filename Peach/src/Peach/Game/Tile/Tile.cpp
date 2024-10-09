#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const Vec2f& size, const Vec2f& position)
		: m_Shape(size), m_Type(0)
	{
		setPosition(position);
	}

	Tile::Tile(const FloatRect& rect)
		: m_Shape({ rect.width, rect.height })
	{
		setPosition({ rect.x, rect.y });
	}

	void Tile::setType(const TileType& type)
	{
		m_Type = type;
	}

	void Tile::setSize(const Vec2f& size)
	{
		m_Shape.setSize(size);
	}

	void Tile::setPosition(const Vec2f& position)
	{
		m_Shape.setPosition(position);
	}

	void Tile::setTexture(const sf::Texture& texture)
	{
		m_Shape.setTexture(&texture);
	}

	void Tile::setTextureRect(const IntRect& rect)
	{
		m_Shape.setTextureRect(rect);
	}

	const TileType& Tile::getType() const
	{
		return m_Type;
	}

	const Vec2f& Tile::getSize() const
	{
		return m_Shape.getSize();
	}

	const Vec2f& Tile::getPosition() const
	{
		return m_Shape.getPosition();
	}

	void Tile::render(sf::RenderTarget* target) const
	{
		target->draw(m_Shape);
	}
}