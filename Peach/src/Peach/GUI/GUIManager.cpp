#include "peachpch.h"
#include "GUIManager.h"

#include "Button.h"
#include "Checkbox.h"

namespace Peach
{
	PEACH_API sf::Vector2i GUIManager::m_MousePosition;

	GUIManager::GUIManager()
	{
		PEACH_CORE_TRACE("GUIManager costruito");
	}

	GUIManager::~GUIManager()
	{
		PEACH_CORE_TRACE("GUIManager distrutto");
	}

	Ref<GUIObject> GUIManager::operator[](const uint32_t& key)
	{
		return m_Objects[key];
	}

	void GUIManager::add(const uint32_t& key, GUIObject* value)
	{
		PEACH_CORE_TRACE("GUIManager::add(key: {}, object: {})", key, value ? "EXISTS" : "NULL");
		m_Objects[key] = Ref<GUIObject>(value);
	}

	sf::Cursor::Type GUIManager::getCursor() const
	{
		for (const auto& [key, value] : m_Objects)
		{
			if (value->isCursorOn(m_MousePosition))
			{
				return sf::Cursor::Hand;
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
				for (const auto& [key, value] : m_Objects)
				{
					if (value->isCursorOn(m_MousePosition))
					{
						value->callback();

						switch (value->getType())
						{
						case GUIType::Button:
						{
							Button* button = static_cast<Button*>(value.get());

							button->setState(Button::State::PRESSED);

							PEACH_CORE_TRACE("GUIManager::handleEvent(...), Premuto pulsante ({}, \"{}\")", key, button->getLabel().toAnsiString());
						}
						break;
						case GUIType::Checkbox:
						{
							Checkbox* checkbox = static_cast<Checkbox*>(value.get());

							checkbox->setActive(!checkbox->getActive());

							PEACH_CORE_TRACE("GUIManager::handleEvent(...), Premuto checkbox ({}, \"{}\")", key, checkbox->getActive() ? "ATTIVATO" : "DISATTIVATO");
						}
						break;
						}
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
