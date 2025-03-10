#include "peachpch.h"
#include "InputController.h"

namespace Peach
{
	void InputController::addBind(sf::Keyboard::Key key, const std::function<void(sf::Event::KeyEvent)>& callback, const std::string& description)
	{
		PEACH_CORE_TRACE("InputController::bind(key: {}, description: {})", keyToString(key), description);

		m_KeyBinds.emplace_back(key, callback, description);
	}

	void InputController::addBind(sf::Mouse::Button button, const std::function<void(sf::Event::MouseButtonEvent)>& callback, const std::string& description)
	{
		PEACH_CORE_TRACE("InputController::bind(button: {}, description: {})", buttonToString(button), description);

		m_MouseBinds.emplace_back(button, callback, description);
	}

	void InputController::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			onKeyPressedEvent(event.key);
			break;
		case sf::Event::MouseButtonPressed:
			onMousePressedEvent(event.mouseButton);
			break;
		}
	}

	void InputController::onKeyPressedEvent(const sf::Event::KeyEvent event)
	{
		for (const auto& [key, callback, description] : m_KeyBinds)
		{
			if (key != event.code)
			{
				continue;
			}

			PEACH_CORE_INFO("InputController::onKeyPressed(), Chiamato bind: {}, Descrizione: {}", keyToString(key), description);
			if (callback)
			{
				callback(event);
			}
		}
	}

	void InputController::onMousePressedEvent(const sf::Event::MouseButtonEvent event)
	{
		for (const auto& [button, callback, description] : m_MouseBinds)
		{
			if (button != event.button)
			{
				continue;
			}

			PEACH_CORE_INFO("InputController::onMousePressed(), Chiamato bind: {}, Descrizione: {}", buttonToString(button), description);
			if (callback)
			{
				callback(event);
			}
		}
	}

	std::string InputController::keyToString(const sf::Keyboard::Key key) const
	{
		return sf::Keyboard::getDescription(sf::Keyboard::delocalize(key)).toAnsiString();
	}

	std::string InputController::buttonToString(const sf::Mouse::Button button) const
	{
		using Button = sf::Mouse::Button;
		switch (button)
		{
		case Button::Left:
			return "Left";
		case Button::Right:
			return "Right";
		case Button::Middle:
			return "Middle";
		case Button::XButton1:
			return "XButton1";
		case Button::XButton2:
			return "XButton2";
		default:
			return "Unknown";
		}
	}
}
