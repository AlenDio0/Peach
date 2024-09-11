#include "peachpch.h"
#include "GUIManager.h"

namespace Peach
{
	PEACH_API sf::Vector2i GUIManager::m_MousePosition;

	GUIManager::GUIManager()
		: m_Pressed(-1)
	{
		PEACH_CORE_TRACE("GUIManager creato");
	}

	GUIManager::~GUIManager()
	{
		PEACH_CORE_TRACE("GUIManager distrutto");
	}

	GUIObjectRef GUIManager::operator[](const uint32_t& key)
	{
		return m_Objects[key];
	}

	void GUIManager::add(const uint32_t& key, GUIObject* value)
	{
		m_Objects[key] = GUIObjectRef(value);
	}

	sf::Cursor::Type GUIManager::getCursor() const
	{
		for (const auto& [key, value] : m_Objects)
		{
			switch (value->getType())
			{
			case GUIType::Button:
				if (static_cast<Button*>(value.get())->getState() == Button::State::HOVER)
				{
					return sf::Cursor::Hand;
				}
				break;
			}
		}

		return sf::Cursor::Arrow;
	}

	GUIObjectMap GUIManager::getGUIObjects(const std::vector<GUIType>& types)
	{
		if (types.empty())
		{
			return m_Objects;
		}

		GUIObjectMap objects;
		for (const auto& type : types)
		{
			for (auto& [key, value] : m_Objects)
			{
				if (value->getType() == type)
				{
					objects[key] = value;
				}
			}
		}

		return objects;
	}

	bool GUIManager::pollPressed(uint32_t& pressed)
	{
		if (m_Pressed == -1)
		{
			return false;
		}

		pressed = m_Pressed;
		m_Pressed = -1;

		return true;
	}

	void GUIManager::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseMoved:
			m_MousePosition = { event.mouseMove.x, event.mouseMove.y };
			for (auto& [key, value] : m_Objects)
			{
				switch (value->getType())
				{
				case GUIType::Button:
				{
					Button* button = static_cast<Button*>(value.get());
					if (button->isCursorOn(m_MousePosition))
					{
						button->setState(Button::State::HOVER);
					}
					else
					{
						button->setState(Button::State::IDLE);
					}
				}
				break;
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				auto buttons = getGUIObjects({ GUIType::Button });
				for (const auto& [key, value] : buttons)
				{
					Button* button = static_cast<Button*>(value.get());
					if (button->isCursorOn(m_MousePosition))
					{
						m_Pressed = key;
						button->setState(Button::State::PRESSED);

						PEACH_CORE_INFO("Premuto pulsante ({}, \"{}\")", key, button->getLabel().toAnsiString());
					}
				}
			}
			break;
		}
	}

	void GUIManager::update()
	{
		for (auto& [key, value] : m_Objects)
		{
			value->update();
		}
	}

	void GUIManager::render(sf::RenderTarget* target) const
	{
		for (const auto& [key, value] : m_Objects)
		{
			value->render(target);
		}
	}
}
