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

		bool create(const sf::String& title, const sf::Vector2u& size);
		void close();

		bool isRunning() const;

		const sf::String& getTitle() const;
		const sf::Vector2u getOriginalSize() const;

		void setMouseCursor(const sf::Cursor& cursor);

		sf::RenderTarget* getRenderer();
		void display();

		bool pollEvent(sf::Event& event) const;
	private:
		sf::RenderWindow* m_Window;

		sf::String m_Title;
		sf::Vector2u m_OriginalSize;
	};
}
