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

	void GUIObject::addCallback(const std::function<void()>& callback)
	{
		m_CallbackSink.push_back(callback);
	}

	void GUIObject::setPosition(const sf::Vector2f& position)
	{
		m_Shape->setPosition(position);
	}

	void GUIObject::setPrimaryColor(sf::Color color)
	{
		m_PrimaryColor = color;
	}

	void GUIObject::setSecondaryColor(sf::Color color)
	{
		m_SecondaryColor = color;
	}

	void GUIObject::setOutlineThickness(float thickness)
	{
		m_Shape->setOutlineThickness(thickness);
	}

	void GUIObject::setTexture(const sf::Texture* texture)
	{
		m_Shape->setTexture(texture);
	}

	void GUIObject::onHover()
	{
	}

	void GUIObject::onPressed()
	{
	}

	void GUIObject::callback() const
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

	sf::Color GUIObject::getPrimaryColor() const
	{
		return m_PrimaryColor;
	}

	sf::Color GUIObject::getSecondaryColor() const
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
