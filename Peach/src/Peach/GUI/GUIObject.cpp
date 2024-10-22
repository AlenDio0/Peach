#include "peachpch.h"
#include "GUIObject.h"

namespace Peach
{
	GUIObject::GUIObject(sf::Shape& container)
		: m_Shape(&container)
	{
		PEACH_CORE_TRACE("GUIObject costruito");
	}

	GUIObject::~GUIObject()
	{
		PEACH_CORE_TRACE("GUIObject distrutto");
	}

	void GUIObject::setCallback(const std::function<void()>& callback)
	{
		m_Callback = callback;
	}

	void GUIObject::setPosition(const sf::Vector2f& position)
	{
		m_Shape->setPosition(position);
	}

	void GUIObject::setPrimaryColor(const sf::Color& color)
	{
		m_PrimaryColor = color;
	}

	void GUIObject::setSecondaryColor(const sf::Color& color)
	{
		m_SecondaryColor = color;
	}

	void GUIObject::setOutlineThickness(const float& thickness)
	{
		m_Shape->setOutlineThickness(thickness);
	}

	void GUIObject::setTexture(const sf::Texture* texture)
	{
		m_Shape->setTexture(texture);
	}

	void GUIObject::callback() const
	{
		if (!m_Callback)
		{
			return;
		}

		m_Callback();
	}

	const sf::Color& GUIObject::getPrimaryColor() const
	{
		return m_PrimaryColor;
	}

	const sf::Color& GUIObject::getSecondaryColor() const
	{
		return m_SecondaryColor;
	}

	const sf::Vector2f& GUIObject::getPosition() const
	{
		return m_Shape->getPosition();
	}

	bool GUIObject::isCursorOn(const sf::Vector2i& mouseposition) const
	{
		return m_Shape->getGlobalBounds().contains((sf::Vector2f)mouseposition);
	}
}
