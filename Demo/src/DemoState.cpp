#include "DemoState.h"

#include <Peach/Log.h>

DemoState::DemoState(Peach::DataRef data)
	: State(data, "Demo")
{
	m_Circle = sf::CircleShape(m_Data->window.getSize().y / 2.f);
	m_Circle.setFillColor(sf::Color::Green);
}

void DemoState::onEvent()
{
	for (sf::Event event; m_Data->window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Data->window.close();
			break;
		case sf::Event::MouseMoved:
			//PEACH_TRACE("MouseMovedEvent: {} {}", sf::Mouse::getPosition(*m_Data->window).x, sf::Mouse::getPosition(*m_Data->window).y);
			break;
		case sf::Event::KeyPressed:
			PEACH_TRACE("KeyPressedEvent: {}", sf::Keyboard::getDescription(event.key.scancode).toAnsiString());

			switch (event.key.code)
			{
			case sf::Keyboard::A:
				m_Data->machine.addState(Peach::IStateRef(new DemoState(m_Data)), true);
				break;
			case sf::Keyboard::B:
				PEACH_TRACE("Window Size: {}, {}", m_Data->window.getSize().x, m_Data->window.getSize().y);
				break;
			}
			break;
		}
	}
}

void DemoState::onUpdate()
{
}

void DemoState::onRender()
{
	m_Data->window.clear();

	m_Data->window.draw(m_Circle);

	m_Data->window.display();
}
