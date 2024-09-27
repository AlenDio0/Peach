#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const sf::Vector2f& size, const sf::Vector2f& position)
		: type(0), m_Shape(size)
	{
		setPosition(position);
	}

	void Tile::setSize(const sf::Vector2f& size)
	{
		m_Shape.setSize(size);
	}

	void Tile::setPosition(const sf::Vector2f& position)
	{
		m_Shape.setPosition(position);
	}

	void Tile::setTexture(sf::Texture* texture)
	{
		m_Shape.setTexture(texture);
	}

	void Tile::setTextureRect(const sf::IntRect& rect)
	{
		m_Shape.setTextureRect(rect);
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