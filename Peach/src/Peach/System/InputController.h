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
		void addBind(sf::Keyboard::Key key, const std::function<void()>& callback);
		void addBind(sf::Keyboard::Key key, const std::function<void()>& callback, const std::string& description);

		void addBind(sf::Mouse::Button button, const std::function<void()>& callback);
		void addBind(sf::Mouse::Button button, const std::function<void()>& callback, const std::string& description);

		void handleEvent(sf::Event event);
		void onKeyPressedEvent(sf::Event::KeyEvent event);
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);
	private:
		struct KeyBind
		{
			sf::Keyboard::Key key;
			std::function<void()> callback;
			std::string description;
		};
		struct MouseBind
		{
			sf::Mouse::Button button;
			std::function<void()> callback;
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
