#include "peachpch.h"
#include "InputController.h"

namespace Peach
{
	void InputController::bind(sf::Keyboard::Key key, const std::function<void()>& callback, const std::string& description, bool logcall)
	{
		PEACH_CORE_TRACE("InputController::bind(key: {}, description: {})", keyToString(key), description);

		m_KeyBinds[key] = { callback, (logcall ? description : "") };
	}

	void InputController::bind(sf::Mouse::Button button, const std::function<void()>& callback, const std::string& description, bool logcall)
	{
		PEACH_CORE_TRACE("InputController::bind(button: {}, description: {})", buttonToString(button), description);

		m_MouseBinds[button] = { callback, (logcall ? description : "") };
	}

	void InputController::handleEvent(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			for (const auto& [key, callback] : m_KeyBinds)
			{
				if (key == event.key.code)
				{
					m_Keys.push(key);
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			for (const auto& [button, callback] : m_MouseBinds)
			{
				if (button == event.mouseButton.button)
				{
					m_Buttons.push(button);
				}
			}
			break;
		}
	}

	void InputController::update()
	{
		while (!m_Keys.empty())
		{
			auto& bind = m_KeyBinds[m_Keys.top()];
			if (!bind.description.empty())
			{
				PEACH_CORE_INFO
				(
					"InputController::update(), Chiamato bind: {}, Descrizione: {}",
					keyToString(m_Keys.top()), bind.description
				);
			}
			bind.callback();

			m_Keys.pop();
		}

		while (!m_Buttons.empty())
		{
			auto& bind = m_MouseBinds[m_Buttons.top()];
			if (!bind.description.empty())
			{
				PEACH_CORE_INFO
				(
					"InputController::update(), Chiamato bind: {}, Descrizione: {}",
					buttonToString(m_Buttons.top()), bind.description
				);
			}
			bind.callback();

			m_Buttons.pop();
		}
	}

	std::string InputController::keyToString(sf::Keyboard::Key key) const
	{
		return sf::Keyboard::getDescription(sf::Keyboard::delocalize(key)).toAnsiString();
	}

	std::string InputController::buttonToString(sf::Mouse::Button button) const
	{
		using Button = sf::Mouse::Button;
		switch (button)
		{
		case Button::Left:
			return "LEFT";
		case Button::Right:
			return "RIGHT";
		case Button::Middle:
			return "MIDDLE";
		case Button::XButton1:
			return "XButton1";
		case Button::XButton2:
			return "XButton2";
		default:
			return "UNKNOWN";
		}
	}
}
