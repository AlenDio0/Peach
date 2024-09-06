#include "peachpch.h"
#include "GUIManager.h"

namespace Peach
{
	GUIManager::GUIManager()
	{
		PEACH_CORE_TRACE("GUIManager creato");
	}

	GUIManager::~GUIManager()
	{
		PEACH_CORE_TRACE("GUIManager distrutto");
	}

	std::shared_ptr<GUIObject> GUIManager::operator[](const uint32_t& key)
	{
		return m_Objects[key];
	}

	void GUIManager::add(const uint32_t& key, GUIObjectRef value)
	{
		m_Objects[key] = value;
	}

	const sf::Cursor::Type& GUIManager::getCursor() const
	{
		for (const auto& [key, value] : m_CursorOn)
		{
			if (value)
			{
				return sf::Cursor::Hand;
			}
		}

		return sf::Cursor::Arrow;
	}

	const uint32_t& GUIManager::getPressed()
	{
		if (m_Pressed.empty())
		{
			return -1;
		}

		uint32_t pressed = m_Pressed.top();
		m_Pressed.pop();
		return pressed;
	}

	void GUIManager::handleEvent(sf::Event event)
	{
		switch (event.type)
		{
		case sf::Event::MouseMoved:
			for (auto& [key, value] : m_Objects)
			{
				if (value->isCursorOn({ event.mouseMove.x, event.mouseMove.y }))
				{
					if (!m_CursorOn[key])
					{
						value->invertColor();

						m_CursorOn[key] = true;
					}
				}
				else if (m_CursorOn[key])
				{
					value->invertColor();

					m_CursorOn[key] = false;
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button != sf::Mouse::Button::Left)
			{
				break;
			}

			for (const auto& [key, value] : m_CursorOn)
			{
				if (value)
				{
					PEACH_CORE_INFO("Premuto l'oggetto \"{}\"", key);
					m_Pressed.push(key);
				}
			}
			break;
		default:
			break;
		}
	}

	void GUIManager::render(sf::RenderTarget* target) const
	{
		for (auto& [key, value] : m_Objects)
		{
			value->render(target);
		}
	}
}
