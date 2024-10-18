#pragma once

#include "Peach/Core.h"

#include <functional>
#include <stack>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Peach
{
	class PEACH_API PlayerController
	{
	public:
		void bind(const sf::Keyboard::Key& key, const std::function<void()>& callbackback, const std::string& description = "", bool logcall = false);
		void bind(const sf::Mouse::Button& button, const std::function<void()>& callback, const std::string& description = "", bool logcall = false);

		void handleEvent(sf::Event& event);
		void update();
	private:
		struct Bind
		{
			std::function<void()> callback;
			std::string description = "";
		};
	private:
		std::unordered_map<sf::Keyboard::Key, Bind> m_KeyBinds;
		std::unordered_map<sf::Mouse::Button, Bind> m_MouseBinds;
		std::stack<sf::Keyboard::Key> m_Keys;
		std::stack<sf::Mouse::Button> m_Buttons;
	private:
		std::string keyToString(const sf::Keyboard::Key& key) const;
		std::string buttonToString(const sf::Mouse::Button& button) const;
	};
}
