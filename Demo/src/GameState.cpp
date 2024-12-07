#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::Data> data)
	: Peach::State(data, "Game"), m_TileMap(Peach::TileMapParser::parse("level.txt", getTexture("tiles")))
{
	initBinds();
}

GameState::~GameState()
{
}

void GameState::onEvent()
{
	for (sf::Event event; pollEvent(event);)
	{
		getWindow().handleEvent(event);
		m_Input.handleEvent(event);
	}
}

void GameState::onUpdate()
{
	m_TileMap.update();
}

void GameState::onRender()
{
	getRenderer()->setView(getRenderer()->getView());

	getRenderer()->clear();

	m_TileMap.render(getRenderer());

	getWindow().display();
}

void GameState::initBinds()
{
	m_Input.addBind(sf::Keyboard::Escape,
		[&]() {
			removeState();
		}, "Rimuove lo Stato attuale");
}
