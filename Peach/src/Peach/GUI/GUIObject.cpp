#include "peachpch.h"
#include "GuiObject.h"

namespace Peach
{
	GuiObject::GuiObject(sf::Shape& container)
		: m_Shape(&container)
	{
		PEACH_CORE_TRACE("GuiObject costruito");
	}

	GuiObject::~GuiObject()
	{
		PEACH_CORE_TRACE("GuiObject distrutto");
	}

	void GuiObject::addCallback(const std::function<void()>& callback)
	{
		m_CallbackSink.push_back(callback);
	}

	void GuiObject::setPosition(const sf::Vector2f& position)
	{
		m_Shape->setPosition(position);
	}

	void GuiObject::setPrimaryColor(sf::Color color)
	{
		m_PrimaryColor = color;
	}

	void GuiObject::setSecondaryColor(sf::Color color)
	{
		m_SecondaryColor = color;
	}

	void GuiObject::setOutlineThickness(float thickness)
	{
		m_Shape->setOutlineThickness(thickness);
	}

	void GuiObject::setTexture(const sf::Texture* texture)
	{
		m_Shape->setTexture(texture);
	}

	void GuiObject::handleEvent(const sf::Event& event)
	{
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

	sf::Color GuiObject::getPrimaryColor() const
	{
		return m_PrimaryColor;
	}

	sf::Color GuiObject::getSecondaryColor() const
	{
		return m_SecondaryColor;
	}

	const sf::Vector2f& GuiObject::getPosition() const
	{
		return m_Shape->getPosition();
	}

	bool GuiObject::isCursorOn(const sf::Vector2i& mouseposition) const
	{
		return m_Shape->getGlobalBounds().contains((sf::Vector2f)mouseposition);
	}
}
