#include "peachpch.h"
#include "GUIObject.h"

namespace Peach
{
	GUIObject::GUIObject(sf::Shape& container)
		: m_Shape(&container)
	{
		PEACH_CORE_TRACE("GUIObject creato");
	}

	GUIObject::~GUIObject()
	{
		PEACH_CORE_TRACE("GUIObject distrutto");
	}

	void GUIObject::invertColor()
	{
		sf::Color color = getFillColor();
		setFillColor(getSecondaryColor());
		setSecondaryColor(color);
	}

	void GUIObject::setFillColor(const sf::Color& color)
	{
		m_Shape->setFillColor(color);
	}

	void GUIObject::setSecondaryColor(const sf::Color& color)
	{
		m_Shape->setOutlineColor(color);
	}

	void GUIObject::setOutlineThickness(const float& thickness)
	{
		m_Shape->setOutlineThickness(thickness);
	}

	void GUIObject::setTexture(const sf::Texture* texture)
	{
		m_Shape->setTexture(texture);
	}

	void GUIObject::setPosition(sf::Vector2f& position)
	{
		m_Shape->setPosition(position);
	}

	const sf::Color& GUIObject::getFillColor() const
	{
		return m_Shape->getFillColor();
	}

	const sf::Color& GUIObject::getSecondaryColor() const
	{
		return m_Shape->getOutlineColor();
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
