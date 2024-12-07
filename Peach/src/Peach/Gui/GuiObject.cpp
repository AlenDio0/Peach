#include "peachpch.h"
#include "GuiObject.h"

namespace Peach
{
	GuiObject::GuiObject(sf::Shape& container, bool debuglog)
		: m_Shape(&container), m_DebugLog(debuglog)
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GuiObject costruito");
		}
	}

	GuiObject::~GuiObject()
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GuiObject distrutto");
		}
	}

	void GuiObject::addCallback(sf::Event::EventType type, const std::function<void(GuiObject&, sf::Event)>& callback)
	{
		m_Callbacks.push_back({ type, callback });
	}

	void GuiObject::setPosition(Vec2f position)
	{
		m_Shape->setPosition(position);
	}

	void GuiObject::setAppearance(Appearance appearance)
	{
		m_Appearance = appearance;
		m_Shape->setOutlineThickness(m_Appearance.outline_thickness);
	}

	void GuiObject::setOutlineThickness(float thickness)
	{
		m_Appearance.outline_thickness = thickness;
		m_Shape->setOutlineThickness(m_Appearance.outline_thickness);
	}

	void GuiObject::setPrimaryColor(sf::Color color)
	{
		m_Appearance.primary_color = color;
	}

	void GuiObject::setSecondaryColor(sf::Color color)
	{
		m_Appearance.secondary_color = color;
	}

	void GuiObject::setBackgroundColor(sf::Color color)
	{
		m_Appearance.background_color = color;
	}

	Vec2f GuiObject::getSize() const
	{
		return m_Shape->getGlobalBounds().getSize();
	}

	Vec2f GuiObject::getPosition() const
	{
		return m_Shape->getPosition();
	}

	bool GuiObject::isCursorOn(Vec2i mouseposition) const
	{
		return m_Shape->getGlobalBounds().contains((Vec2f)mouseposition);
	}

	bool GuiObject::isCursorOn(sf::Event::MouseMoveEvent event) const
	{
		return isCursorOn(Vec2i(event.x, event.y));
	}

	bool GuiObject::isCursorOn(sf::Event::MouseButtonEvent event) const
	{
		return isCursorOn(Vec2i(event.x, event.y));
	}

	GuiObject::Appearance GuiObject::getAppearance() const
	{
		return m_Appearance;
	}

	void GuiObject::callback(sf::Event event)
	{
		for (const auto& [type, cback] : m_Callbacks)
		{
			if (event.type != type)
			{
				continue;
			}

			if (cback)
			{
				cback(*this, event);
			}
		}
	}

	void GuiObject::handleEvent(sf::Event event)
	{
		callback(event);

		handleSpecEvent(event);
	}

	void GuiObject::handleSpecEvent(sf::Event event)
	{
	}
}
