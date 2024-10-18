#pragma once

#include "Peach/Core.h"

#include "Peach/Game/GameObject.h"

namespace Peach
{
	using TileID = uint32_t;

	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const Vec2f& size, const Vec2f& position = {});
		Tile(const FloatRect& rect);

		void setID(const TileID& id);

		const TileID& getID() const;

		virtual void render(sf::RenderTarget* target);
	private:
		TileID m_ID;
	};
}
