#pragma once

#include "Core.h"

#include "Peach/Config/WindowConfig.h"
#include <SFML/Graphics.hpp>

namespace Peach
{
	class PEACH_API Window : public sf::RenderWindow
	{
	public:
		Window();
		virtual ~Window();

		virtual void init();

		WindowConfig& getConfig();

		virtual void handleEvent(const sf::Event& event);
	private:
		WindowConfig m_Config;
	};
}
