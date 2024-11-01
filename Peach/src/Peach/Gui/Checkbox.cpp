#include "peachpch.h"
#include "Checkbox.h"

namespace Peach
{
	Checkbox::Checkbox(const sf::Vector2f& size, bool active)
		: GuiObject(m_Container, false), m_Active(active)
	{
		PEACH_CORE_TRACE("Checkbox costruito");

		setSize(size);

		setPosition({ 0, 0 });
	}

	Checkbox::~Checkbox()
	{
		PEACH_CORE_TRACE("Checkbox distrutto");
	}

	void Checkbox::setSize(const sf::Vector2f& size)
	{
		m_Container.setSize(size);
		m_Check.setScale(size.x / m_Check.getTextureRect().width, size.y / m_Check.getTextureRect().height);
	}

	void Checkbox::setPosition(const sf::Vector2f& position)
	{
		m_Container.setPosition(position);
		m_Check.setPosition(position);
	}

	void Checkbox::setCheckTexture(const sf::Texture& texture)
	{
		m_Check.setTexture(texture);
		setSize(getSize());
	}

	const sf::Vector2f& Checkbox::getSize() const
	{
		return m_Container.getSize();
	}

	bool Checkbox::isActive() const
	{
		return m_Active;
	}

	void Checkbox::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			onMousePressedEvent(event.mouseButton);
			break;
		}
	}

	void Checkbox::onMousePressedEvent(const sf::Event::MouseButtonEvent& event)
	{
		if (event.button != sf::Mouse::Button::Left)
		{
			return;
		}

		if (isCursorOn({ event.x, event.y }))
		{
			m_Active = !m_Active;

			callback();
		}
	}

	GuiType Checkbox::getType() const
	{
		return GuiType::Checkbox;
	}

	void Checkbox::update()
	{
		const auto [_, primary, secondary, background] = getAppearance();

		m_Check.setColor(primary);
		m_Container.setOutlineColor(secondary);
		m_Container.setFillColor(background);
	}

	void Checkbox::render(sf::RenderTarget* target) const
	{
		target->draw(m_Container);

		if (m_Active)
		{
			target->draw(m_Check);
		}
	}
}
