#include "GameState.h"

GameState::GameState(Peach::DataRef data)
	: Peach::State(data, "Game")
{
}

GameState::~GameState()
{
}

void GameState::onEvent()
{
	for (sf::Event event; m_Data->window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Data->window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_Data->machine.removeState();
				break;
			}
			break;
		}
	}
}

void GameState::onUpdate()
{
}

void GameState::onRender()
{
	m_Data->window.getRenderer()->setView(m_Data->window.getRenderer()->getView());

	m_Data->window.getRenderer()->clear();

	m_Data->window.display();
}
