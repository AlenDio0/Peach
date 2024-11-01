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

	void GuiObject::addCallback(const std::function<void()>& callback)
	{
		m_CallbackSink.push_back(callback);
	}

	void GuiObject::setPosition(const sf::Vector2f& position)
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

	const sf::Vector2f& GuiObject::getPosition() const
	{
		return m_Shape->getPosition();
	}

	bool GuiObject::isCursorOn(const sf::Vector2i& mouseposition) const
	{
		return m_Shape->getGlobalBounds().contains((sf::Vector2f)mouseposition);
	}

	GuiObject::Appearance GuiObject::getAppearance() const
	{
		return m_Appearance;
	}

	GuiType GuiObject::getType() const
	{
		return GuiType::None;
	}

	void GuiObject::callback() const
	{
		for (auto& cback : m_CallbackSink)
		{
			if (!cback)
			{
				continue;
			}

			cback();
		}
	}

	void GuiObject::handleEvent(const sf::Event& event)
	{
	}
}
