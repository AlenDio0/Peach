#pragma once

#include "Peach/Core.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	using TileType = uint16_t;

	class PEACH_API Tile
	{
	public:
		TileType type;
	public:
		Tile(const sf::Vector2f& size, const sf::Vector2f& position = {});
		~Tile() = default;

		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setTexture(sf::Texture* texture);
		void setTextureRect(const sf::IntRect& rect);

		const sf::Vector2f& getSize() const;
		const sf::Vector2f& getPosition() const;

		void render(sf::RenderTarget* target) const;
	private:
		sf::RectangleShape m_Shape;
	};
}
