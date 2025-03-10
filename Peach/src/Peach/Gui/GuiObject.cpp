#include "peachpch.h"
#include "GuiObject.h"

namespace Peach
{
	GuiObject::GuiObject(sf::Shape& container, bool debugLog)
		: m_Shape(&container), m_DebugLog(debugLog)
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

	void GuiObject::addCallback(const sf::Event::EventType type, const std::function<void(GuiObject&, sf::Event)>& callback)
	{
		m_Callbacks.push_back({ type, callback });
	}

	void GuiObject::setPosition(const Vec2f position)
	{
		m_Shape->setPosition(position);
	}

	void GuiObject::setAppearance(const Appearance appearance)
	{
		m_Appearance = appearance;
		m_Shape->setOutlineThickness(m_Appearance.outlineThickness);
	}

	void GuiObject::setOutlineThickness(const float thickness)
	{
		m_Appearance.outlineThickness = thickness;
		m_Shape->setOutlineThickness(m_Appearance.outlineThickness);
	}

	void GuiObject::setPrimaryColor(const sf::Color color)
	{
		m_Appearance.primaryColor = color;
	}

	void GuiObject::setSecondaryColor(const sf::Color color)
	{
		m_Appearance.secondaryColor = color;
	}

	void GuiObject::setBackgroundColor(const sf::Color color)
	{
		m_Appearance.backgroundColor = color;
	}

	Vec2f GuiObject::getSize() const
	{
		return m_Shape->getGlobalBounds().getSize();
	}

	Vec2f GuiObject::getPosition() const
	{
		return m_Shape->getPosition();
	}

	bool GuiObject::isCursorOn(const Vec2i mouseposition) const
	{
		return m_Shape->getGlobalBounds().contains((Vec2f)mouseposition);
	}

	bool GuiObject::isCursorOn(const sf::Event::MouseMoveEvent event) const
	{
		return isCursorOn(Vec2i(event.x, event.y));
	}

	bool GuiObject::isCursorOn(const sf::Event::MouseButtonEvent event) const
	{
		return isCursorOn(Vec2i(event.x, event.y));
	}

	GuiObject::Appearance GuiObject::getAppearance() const
	{
		return m_Appearance;
	}

	void GuiObject::callback(const sf::Event& event)
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

	void GuiObject::handleEvent(const sf::Event& event)
	{
		callback(event);

		handleSpecEvent(event);
	}

	void GuiObject::handleSpecEvent(const sf::Event& event)
	{
	}
}
