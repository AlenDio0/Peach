#pragma once

#include "Peach/Game/GameObject.h"

namespace Peach
{
	using TileID = uint32_t;

	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const sf::Texture& texture, RigidBody body, std::function<void(Tile&)> changedid = NULL, bool debuglog = false);
		virtual ~Tile() = default;

		void setID(TileID id);

		TileID getID() const;
	private:
		TileID m_ID;

		std::function<void(Tile&)> m_ChangedID;
	};
}
