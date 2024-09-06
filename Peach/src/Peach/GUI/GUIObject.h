#pragma once

#include "Peach/Core.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Peach
{
	class PEACH_API GUIObject
	{
	public:
		GUIObject(sf::Shape& container);
		virtual ~GUIObject();

		virtual void invertColor();

		virtual void setFillColor(const sf::Color& color);
		virtual void setSecondaryColor(const sf::Color& color);
		virtual void setSize(const sf::Vector2f& size) = 0;
		virtual void setPosition(sf::Vector2f& position);
		void setOutlineThickness(const float& thickness);
		void setTexture(const sf::Texture* texture);

		const sf::Color& getFillColor() const;
		const sf::Color& getSecondaryColor() const;
		const sf::Vector2f& getPosition() const;

		bool isCursorOn(const sf::Vector2i& mouseposition) const;

		virtual void render(sf::RenderTarget* target) const = 0;
	private:
		sf::Shape* m_Shape;
	};
}
