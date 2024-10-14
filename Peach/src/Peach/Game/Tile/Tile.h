#pragma once

#include "Peach/Core.h"

#include "Peach/Game/GameObject.h"

namespace Peach
{
	using TileType = uint16_t;

	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const Vec2f& size, const Vec2f& position = {});
		Tile(const FloatRect& rect);

		void setType(const TileType& type);

		const TileType& getType() const;

		virtual void render(sf::RenderTarget* target);
	private:
		TileType m_Type;
	};
}
