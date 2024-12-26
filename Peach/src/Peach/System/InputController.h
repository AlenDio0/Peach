#pragma once

#include "Peach/Core/Core.h"

#include <functional>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Peach
{
	class PEACH_API InputController
	{
	public:
		void addBind(sf::Keyboard::Key key, const std::function<void(sf::Event::KeyEvent)>& callback, const std::string& description = "Unknown");
		void addBind(sf::Mouse::Button button, const std::function<void(sf::Event::MouseButtonEvent)>& callback, const std::string& description = "Unknown");

		void handleEvent(sf::Event event);
		void onKeyPressedEvent(sf::Event::KeyEvent event);
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);
	private:
		struct KeyBind
		{
			KeyBind(sf::Keyboard::Key key, const std::function<void(sf::Event::KeyEvent)>& callback, const std::string& description)
				: key(key), callback(callback), description(description)
			{
			}
			sf::Keyboard::Key key;
			std::function<void(sf::Event::KeyEvent)> callback;
			std::string description;
		};
		struct MouseBind
		{
			MouseBind(sf::Mouse::Button button, const std::function<void(sf::Event::MouseButtonEvent)>& callback, const std::string& description)
				: button(button), callback(callback), description(description)
			{
			}
			sf::Mouse::Button button;
			std::function<void(sf::Event::MouseButtonEvent)> callback;
			std::string description;
		};
	private:
		std::string keyToString(sf::Keyboard::Key key) const;
		std::string buttonToString(sf::Mouse::Button button) const;
	private:
		std::vector<KeyBind> m_KeyBinds;
		std::vector<MouseBind> m_MouseBinds;
	};
}
