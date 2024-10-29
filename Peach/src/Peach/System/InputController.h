#pragma once

#include "Peach/Core.h"

#include <functional>
#include <stack>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Peach
{
	class PEACH_API InputController
	{
	public:
		void bind(sf::Keyboard::Key key, const std::function<void()>& callback, const std::string& description = "", bool logcall = false);
		void bind(sf::Mouse::Button button, const std::function<void()>& callback, const std::string& description = "", bool logcall = false);

		void handleEvent(const sf::Event& event);
		void onKeyPressed(const sf::Event& event);
		void onMousePressed(const sf::Event& event);

		void update();
	private:
		struct Bind
		{
			std::function<void()> callback;
			std::string description;
		};
	private:
		std::unordered_map<sf::Keyboard::Key, Bind> m_KeyBinds;
		std::unordered_map<sf::Mouse::Button, Bind> m_MouseBinds;
		std::stack<sf::Keyboard::Key> m_Keys;
		std::stack<sf::Mouse::Button> m_Buttons;
	private:
		std::string keyToString(sf::Keyboard::Key key) const;
		std::string buttonToString(sf::Mouse::Button button) const;
	};
}
