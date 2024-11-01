#pragma once

#include "Peach/Game/GameObject.h"

namespace Peach
{
	using TileID = uint32_t;

	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const Vec2f& size, const Vec2f& position = {}, bool debuglog = false);
		Tile(const FloatRect& rect);

		void setID(TileID id);

		TileID getID() const;

		virtual void render(sf::RenderTarget* target);
	private:
		TileID m_ID;
	};
}
