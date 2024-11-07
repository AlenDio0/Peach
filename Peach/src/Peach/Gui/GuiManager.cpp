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

	UUID GuiManager::add(Ref<GuiObject> object)
	{
		UUID uuid;

		PEACH_CORE_TRACE("GuiManager::add(object: {}), [uuid: {}]", uuid, object);
		if (!object)
		{
			PEACH_CORE_ERROR("GuiManager::add(...), Impossibile aggiungere un GuiObject nullo");
			return 0;
		}

		m_Objects[uuid] = object;
		return uuid;
	}

	UUID GuiManager::add(GuiObject* object)
	{
		return add(Ref<GuiObject>(object));
	}

	void GuiManager::remove(UUID uuid)
	{
		PEACH_CORE_TRACE("GuiManager::remove(uuid: {})", uuid);
		m_Objects.erase(uuid);
	}

	void GuiManager::remove(Ref<GuiObject> object)
	{
		PEACH_CORE_TRACE("GuiManager::remove(object: {})", object);
		for (auto& [uuid, value] : m_Objects)
		{
			if (value == object)
			{
				remove(uuid);
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

		for (const auto& [uuid, object] : m_Objects)
		{
			if (object->isCursorOn(m_MousePosition))
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
			}
		}

		return cursor;
	}

	WeakMap<GuiObject> GuiManager::getGuiObjects(const std::vector<GuiType>& types)
	{
		WeakMap<GuiObject> objects;

		if (types.empty())
		{
			for (auto& [uuid, object] : m_Objects)
			{
				objects[uuid] = object;
			}

			return objects;
		}

		for (const auto& type : types)
		{
			for (auto& [uuid, object] : m_Objects)
			{
				if (object->getType() == type)
				{
					objects[uuid] = object;
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

		for (auto& [uuid, object] : m_Objects)
		{
			object->handleEvent(event);
		}
	}

	void GuiManager::update()
	{
		for (auto& [uuid, object] : m_Objects)
		{
			object->update();
		}
	}

	void GuiManager::render(sf::RenderTarget* target) const
	{
		for (const auto& [uuid, object] : m_Objects)
		{
			object->render(target);
		}
	}
}
