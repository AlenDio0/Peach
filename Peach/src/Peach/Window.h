#pragma once

#include "Core.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API Window
	{
	public:
		Window();
		~Window();

		const bool& create(sf::String title, sf::Vector2u size);
		void close();

		const bool& isRunning() const;

		const sf::String& getTitle() const;
		const sf::Vector2u getSize() const;
		const sf::Vector2u getOriginalSize() const;

		const bool& pollEvent(sf::Event& event) const;

		void clear(const sf::Color& color = {});
		void draw(const sf::Drawable& drawable);
		void display();
	private:
		sf::RenderWindow* m_Window;

		sf::String m_Title;
		sf::Vector2u m_OriginalSize;
	};
}
