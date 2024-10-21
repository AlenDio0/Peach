#pragma once

#include "Core.h"

#include "Config/WindowConfig.h"

#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API Window
	{
	public:
		Window();
		~Window();

		bool create();
		void close();

		bool isRunning() const;

		WindowConfig& getConfig();

		void setMouseCursor(const sf::Cursor& cursor);

		sf::RenderTarget* getRenderer();
		void display();

		bool pollEvent(sf::Event& event) const;
	private:
		Scope<sf::RenderWindow> m_Window;

		WindowConfig m_Config;
	};
}
