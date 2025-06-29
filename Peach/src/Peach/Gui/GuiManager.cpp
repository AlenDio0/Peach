#include "peachpch.h"
#include "GuiManager.h"

namespace Peach
{
	GuiManager::GuiManager()
	{
		PEACH_CORE_TRACE("GuiManager costruito");
	}

	GuiManager::~GuiManager()
	{
		PEACH_CORE_TRACE("GuiManager distrutto");
	}

	const sf::Cursor& GuiManager::getCursor() const
	{
		static sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Arrow);

		for (const auto& [uuid, obj] : getObjects())
		{
			if (auto gui = obj.lock())
			{
				if (gui->isCursorOn(m_MousePosition))
				{
					cursor.loadFromSystem(sf::Cursor::Hand);
				}
			}
		}

		return cursor;
	}

	void GuiManager::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseMoved:
			m_MousePosition = { event.mouseMove.x, event.mouseMove.y };
			break;
		}

		for (auto& [key, obj] : getObjects())
		{
			if (auto gui = obj.lock())
			{
				gui->handleEvent(event);
			}
		}
	}

	void GuiManager::update(const float deltaTime)
	{
		for (auto& [key, obj] : getObjects())
		{
			if (auto gui = obj.lock())
			{
				gui->update(deltaTime);
			}
		}
	}

	void GuiManager::render(sf::RenderTarget& target) const
	{
		for (const auto& [key, obj] : getObjects())
		{
			if (auto gui = obj.lock())
			{
				gui->render(target);
			}
		}
	}
}
