#include "peachpch.h"
#include "GuiManager.h"

namespace Peach
{
	PEACH_API sf::Vector2i GuiManager::m_MousePosition;

	GuiManager::GuiManager()
	{
		PEACH_CORE_TRACE("GuiManager costruito");
	}

	GuiManager::~GuiManager()
	{
		PEACH_CORE_TRACE("GuiManager distrutto");

		PEACH_CORE_TRACE("[GuiManager] {} GuiObject distrutti", m_Objects.size());
		m_Objects.clear();
	}

	Ref<GuiObject> GuiManager::operator[](GuiKey key)
	{
		return m_Objects[key];
	}

	void GuiManager::add(GuiKey key, Ref<GuiObject> object)
	{
		PEACH_CORE_TRACE("GuiManager::add(key: {}, object: {})", key, object ? "EXISTS" : "NULL");
		if (!object)
		{
			PEACH_CORE_ERROR("GuiManager::add(...), Impossibile aggiungere un GuiObject nullo");
			return;
		}

		m_Objects[key] = object;
	}

	void GuiManager::add(GuiKey key, GuiObject* object)
	{
		add(key, Ref<GuiObject>(object));
	}

	void GuiManager::remove(GuiKey key)
	{
		PEACH_CORE_TRACE("GuiManager::remove(key: {})", key);
		m_Objects.erase(key);
	}

	void GuiManager::remove(Ref<GuiObject> object)
	{
		PEACH_CORE_TRACE("GuiManager::remove(object: {})", object ? "EXISTS" : "NULL");
		for (auto& [key, value] : m_Objects)
		{
			if (value == object)
			{
				remove(key);
				break;
			}
		}
	}

	void GuiManager::remove(GuiObject* object)
	{
		remove(Ref<GuiObject>(object));
	}

	const sf::Cursor& GuiManager::getCursor() const
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

	RawMap<GuiObject> GuiManager::getGuiObjects(const std::vector<GuiType>& types)
	{
		RawMap<GuiObject> objects;

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

	void GuiManager::handleEvent(const sf::Event& event)
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

	void GuiManager::update()
	{
		for (auto& [key, object] : m_Objects)
		{
			object->update();
		}
	}

	void GuiManager::render(sf::RenderTarget* target) const
	{
		for (const auto& [key, object] : m_Objects)
		{
			object->render(target);
		}
	}
}
