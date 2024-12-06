#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::Data> data)
	: Peach::State(data, "Game"), m_Level(Peach::TileMapParser::parse("level.txt", getTexture("tiles")))
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
		m_Controller.handleEvent(event);
	}
}

void GameState::onUpdate()
{
	m_Controller.update();

	m_Level.update();
}

void GameState::onRender()
{
	getRenderer()->setView(getRenderer()->getDefaultView());

	getRenderer()->clear();

	m_Level.render(getRenderer());

	getWindow().display();
}

void GameState::initBinds()
{
	m_Controller.bind(sf::Keyboard::Escape,
		[&]() {
			removeState();
		}, "Rimuove lo Stato attuale", true);
	m_Controller.bind(sf::Keyboard::A,
		[&]() {
			for (size_t i = 0; i < 1000; i++)
			{
				auto tile = new Peach::Tile(getAsset<Peach::Texture>("tiles"), nullptr);
				tile->setID(10);
				m_Level.getEntityManager().addEntity(tile);
			}
		}, "Test Memory leak - EntityManager", true);
	m_Controller.bind(sf::Keyboard::B,
		[&]() {
			auto& tilemap = m_Level.getTileMap();
			tilemap.setSize(tilemap.getSize() * 10);
		}, "Test Memory leak - TileMap", true);
}
