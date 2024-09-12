#pragma once

#include "Peach/Core.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Peach
{
	enum class GUIType
	{
		None = 0,
		Button
	};

	class PEACH_API GUIObject
	{
	public:
		GUIObject(sf::Shape& container);
		virtual ~GUIObject();

		virtual void setSize(const sf::Vector2f& size) = 0;
		virtual void setPosition(const sf::Vector2f& position);
		void setPrimaryColor(const sf::Color& color);
		void setSecondaryColor(const sf::Color& color);
		void setOutlineThickness(const float& thickness);
		void setTexture(const sf::Texture* texture);

		const sf::Color& getPrimaryColor() const;
		const sf::Color& getSecondaryColor() const;
		const sf::Vector2f& getPosition() const;

		bool isCursorOn(const sf::Vector2i& mouseposition) const;

		virtual GUIType getType() const = 0;

		virtual void update() = 0;
		virtual void render(sf::RenderTarget* target) const = 0;
	protected:
		sf::Color m_PrimaryColor;
		sf::Color m_SecondaryColor;
	private:
		sf::Shape* m_Shape;
	};
}
