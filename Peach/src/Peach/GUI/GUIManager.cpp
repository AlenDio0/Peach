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

	Ref<GUIObject> GUIManager::operator[](GUIKey key)
	{
		return m_Objects[key];
	}

	void GUIManager::add(GUIKey key, GUIObject* object)
	{
		PEACH_CORE_TRACE("GUIManager::add(key: {}, object: {})", key, object ? "EXISTS" : "NULL");
		if (!object)
		{
			PEACH_CORE_ERROR("GUIManager::add(...), Impossibile aggiungere un GUIObject nullo");
			return;
		}

		m_Objects[key] = Ref<GUIObject>(object);
	}

	void GUIManager::remove(GUIKey key)
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

		for (const auto& [key, object] : m_Objects)
		{
			if (object->isCursorOn(m_MousePosition))
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
			for (auto& [key, object] : m_Objects)
			{
				objects[key] = object.get();
			}

			return objects;
		}

		for (const auto& type : types)
		{
			for (auto& [key, object] : m_Objects)
			{
				if (object->getType() == type)
				{
					objects[key] = object.get();
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
			break;
		}

		for (auto& [key, object] : m_Objects)
		{
			object->handleEvent(event);
		}
	}

	void GUIManager::update()
	{
		for (auto& [key, object] : m_Objects)
		{
			object->update();
		}
	}

	void GUIManager::render(sf::RenderTarget* target) const
	{
		for (const auto& [key, object] : m_Objects)
		{
			object->render(target);
		}
	}
}
