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
		void addBind(sf::Keyboard::Key key, const std::function<void()>& callback, const std::string& description = "Unknown");
		void addBind(sf::Mouse::Button button, const std::function<void()>& callback, const std::string& description = "Unknown");

		void handleEvent(sf::Event event);
		void onKeyPressedEvent(sf::Event::KeyEvent event);
		void onMousePressedEvent(sf::Event::MouseButtonEvent event);
	private:
		template<typename T>
		struct Bind
		{
			Bind(T key, const std::function<void()>& callback, const std::string& description)
				: key(key), callback(callback), description(description)
			{
			}
			T key;
			std::function<void()> callback;
			std::string description;
		};

		using KeyBind = Bind<sf::Keyboard::Key>;
		using MouseBind = Bind<sf::Mouse::Button>;
	private:
		std::string keyToString(sf::Keyboard::Key key) const;
		std::string buttonToString(sf::Mouse::Button button) const;
	private:
		std::vector<KeyBind> m_KeyBinds;
		std::vector<MouseBind> m_MouseBinds;
	};
}
