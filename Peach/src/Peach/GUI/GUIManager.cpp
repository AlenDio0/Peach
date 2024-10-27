#include "peachpch.h"
#include "GUIManager.h"

#include "Button.h"
#include "TextBox.h"

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

	void GUIManager::add(const uint32_t& key, GUIObject* object)
	{
		PEACH_CORE_TRACE("GUIManager::add(key: {}, object: {})", key, object ? "EXISTS" : "NULL");
		if (!object)
		{
			PEACH_CORE_ERROR("GUIManager::add(...), Impossibile aggiungere un GUIObject nullo");
			return;
		}

		m_Objects[key] = Ref<GUIObject>(object);
	}

	void GUIManager::remove(const uint32_t& key)
	{
		m_Objects.erase(key);
	}

	void GUIManager::remove(GUIObject* object)
	{
		for (auto& [key, value] : m_Objects)
		{
			if (value.get() == object)
			{
				remove(key);
				break;
			}
		}
	}

	const sf::Cursor& GUIManager::getCursor() const
	{
		static sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Arrow);

		for (const auto& [key, value] : m_Objects)
		{
			if (value->isCursorOn(m_MousePosition))
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
			}
		}

		return cursor;
	}

	RawMap<GUIObject> GUIManager::getGUIObjects(const std::vector<GUIType>& types)
	{
		RawMap<GUIObject> objects;

		if (types.empty())
		{
			for (auto& [key, value] : m_Objects)
			{
				objects[key] = value.get();
			}

			return objects;
		}

		for (const auto& type : types)
		{
			for (auto& [key, value] : m_Objects)
			{
				if (value->getType() == type)
				{
					objects[key] = value.get();
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
			onMouseMoved(event);
			break;
		case sf::Event::MouseButtonPressed:
			onMousePressed(event);
			break;
		case sf::Event::TextEntered:
			onTextEntered(event);
			break;
		}
	}

	void GUIManager::onMouseMoved(const sf::Event& event)
	{
		m_MousePosition = { event.mouseMove.x, event.mouseMove.y };
		for (auto& [key, value] : m_Objects)
		{
			if (!value->isCursorOn(m_MousePosition))
			{
				if (value->getType() == GUIType::Button)
				{
					Button* button = static_cast<Button*>(value.get());
					button->setState(Button::State::IDLE);
				}

				continue;
			}

			value->onHover();
		}
	}

	void GUIManager::onMousePressed(const sf::Event& event)
	{
		if (event.mouseButton.button != sf::Mouse::Button::Left)
		{
			return;
		}

		for (const auto& [key, value] : m_Objects)
		{
			if (!value->isCursorOn(m_MousePosition))
			{
				if (value->getType() == GUIType::TextBox)
				{
					TextBox* textbox = static_cast<TextBox*>(value.get());
					textbox->setSelected(false);
				}

				continue;
			}

			value->onPressed();
		}
	}

	void GUIManager::onTextEntered(const sf::Event& event)
	{
		auto& textboxes = getGUIObjects<TextBox>(GUIType::TextBox);
		for (auto& [key, textbox] : textboxes)
		{
			textbox->onTextEntered(event.text.unicode);
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
