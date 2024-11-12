#pragma once

#include "Peach/Game/GameObject.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API Tile : public GameObject
	{
	public:
		Tile(const sf::Texture& texture, RigidBody body, std::function<void(Tile&)> changedid = nullptr, bool debuglog = false);
		virtual ~Tile() = default;

		void setTexture(const sf::Texture& texture, bool resetrect = false);
		void setTextureRect(IntRect rect);

		void setID(size_t id);

		size_t getID() const;

		virtual void update() override;
		virtual void render(sf::RenderTarget* target) const override;
	private:
		sf::Sprite m_Sprite;

		std::function<void(Tile&)> m_ChangedID;
	};
}
