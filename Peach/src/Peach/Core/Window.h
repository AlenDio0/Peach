#pragma once

#include "Core.h"

#include "Peach/Config/WindowConfig.h"
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

		void setMouseCursor(const sf::Cursor& cursor);
		void setMaxFps(unsigned int fps);

		WindowConfig& getConfig();
		bool isRunning() const;

		bool pollEvent(sf::Event& event) const;
		void handleEvent(const sf::Event& event);
		void onClosed();

		sf::RenderTarget* getRenderer();
		void display();
	private:
		Scope<sf::RenderWindow> m_Window;

		WindowConfig m_Config;
	};
}
