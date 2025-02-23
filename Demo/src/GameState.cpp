#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::Data> data)
	: Peach::AppState(data, "Game"),
	m_Level(Peach::TileMapParser::parse("level.txt", getTexture("tiles"))),
	m_Physics(m_Level.getTileMap(), m_Level.getEntityManager()),
	m_Player(getTexture("player"), Peach::Vec2f(m_Level.getTileMap().getTileSize() * 2.f))
{
	m_Level.getEntityManager().addEntity(Peach::MakeRef<Player>(m_Player));

	m_Physics.setGravity(0.f);

	initBinds();
}

GameState::~GameState()
{
}

void GameState::onEvent(sf::Event event)
{
	getWindow().handleEvent(event);
	m_Input.handleEvent(event);
}

void GameState::onUpdate()
{
	m_Level.update();

	m_Player.update();

	m_Physics.update();
}

void GameState::onRender()
{
	getRenderer()->setView(getRenderer()->getDefaultView());

	getRenderer()->clear();

	m_Level.render(getRenderer());
	m_Physics.renderBoxes(getRenderer());

	getWindow().display();
}

void GameState::initBinds()
{
	m_Input.addBind(sf::Keyboard::Escape,
		[&]() {
			removeState();
		}, "Rimuove lo Stato attuale");
	m_Input.addBind(sf::Keyboard::Num1,
		[&]() {
			for (size_t i = 0; i < 1000; i++)
			{
				auto tile = new Peach::Tile(getAsset<Peach::Texture>("tiles"), nullptr);
				tile->setID(10);
				m_Level.getEntityManager().addEntity(tile);
			}
		}, "Test Memory leak - EntityManager");
	m_Input.addBind(sf::Keyboard::Num2,
		[&]() {
			auto& tilemap = m_Level.getTileMap();
			tilemap.setSize(tilemap.getSize() * 2);
		}, "Test Memory leak - TileMap");
}
