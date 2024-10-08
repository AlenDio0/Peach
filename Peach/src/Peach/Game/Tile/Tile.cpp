#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const Vec2f& size, const Vec2f& position)
		: m_Shape(size), m_Type(0)
	{
		setPosition(position);
	}

	void Tile::setType(const TileType& type)
	{
	}

	void Tile::setSize(const sf::Vector2f& size)
	{
		m_Shape.setSize(size);
	}

	void Tile::setPosition(const sf::Vector2f& position)
	{
		m_Shape.setPosition(position);
	}

	void Tile::setTexture(const sf::Texture& texture)
	{
		m_Shape.setTexture(&texture);
	}

	void Tile::setTextureRect(const sf::IntRect& rect)
	{
		m_Shape.setTextureRect(rect);
	}

	const TileType& Tile::getType() const
	{
		return m_Type;
	}

	const sf::Vector2f& Tile::getSize() const
	{
		return m_Shape.getSize();
	}

	const sf::Vector2f& Tile::getPosition() const
	{
		return m_Shape.getPosition();
	}

	void Tile::render(sf::RenderTarget* target) const
	{
		target->draw(m_Shape);
	}
}