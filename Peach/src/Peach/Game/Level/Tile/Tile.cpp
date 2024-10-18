#include "peachpch.h"
#include "Tile.h"

namespace Peach
{
	Tile::Tile(const Vec2f& size, const Vec2f& position)
		: GameObject(size, position, { {}, size }), m_ID(0)
	{
		update();
	}

	Tile::Tile(const FloatRect& rect)
		: Tile({ rect.width, rect.height }, { rect.x, rect.y })
	{
	}

	void Tile::setID(const TileID& type)
	{
		m_ID = type;
	}

	const TileID& Tile::getID() const
	{
		return m_ID;
	}

	void Tile::render(sf::RenderTarget* target)
	{
		target->draw(m_Shape);
	}
}