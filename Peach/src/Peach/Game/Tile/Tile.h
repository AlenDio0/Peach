#pragma once

#include "Peach/Core.h"

#include "Peach/System.h"
#include <SFML/Graphics.hpp>

namespace Peach
{
	using TileType = uint16_t;

	class PEACH_API Tile
	{
	public:
		Tile(const Vec2f& size, const Vec2f& position = {});
		Tile(const FloatRect& rect);
		~Tile() = default;

		void setType(const TileType& type);
		void setSize(const Vec2f& size);
		void setPosition(const Vec2f& position);
		void setTexture(const sf::Texture& texture);
		void setTextureRect(const IntRect& rect);

		const TileType& getType() const;
		const Vec2f& getSize() const;
		const Vec2f& getPosition() const;

		void render(sf::RenderTarget* target) const;
	private:
		sf::RectangleShape m_Shape;

		TileType m_Type;
	};
}
