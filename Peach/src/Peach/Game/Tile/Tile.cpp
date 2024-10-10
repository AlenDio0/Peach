#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const Vec2f& size, const Vec2f& position)
		: GameObject(size, position, { {}, size }), m_Type(0)
	{
		update();
	}

	Tile::Tile(const FloatRect& rect)
		: Tile({ rect.width, rect.height }, { rect.x, rect.y })
	{
	}

	void Tile::setType(const TileType& type)
	{
		m_Type = type;
	}

	const TileType& Tile::getType() const
	{
		return m_Type;
	}

	void Tile::render(sf::RenderTarget* target)
	{
		target->draw(m_Shape);
	}
}