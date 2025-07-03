#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::AppData> data)
	: Peach::AppState(data, "Game"),
	m_Level(Peach::TileMapParser::parse("level.txt", getTexture("tiles"))), m_Physics(m_Level),
	m_Player(getTexture("player"), Peach::Vec2f(70.f, 100.f))
{
	m_Level.getEntityManager().add(Peach::MakeRef<Player>(m_Player));
	//m_Level.getEntityManager().add(Peach::MakeRef<Player>(getTexture("player"), Peach::Vec2f(250.f, 100.f)));
	m_Level.getEntityManager().add(Peach::MakeRef<NPC>(getTexture("player"), Peach::Vec2f(220.f, 100.f)));

	m_Physics.setGravity(0.f);

	initBinds();
}

GameState::~GameState()
{
}

void GameState::onEvent(const sf::Event& event)
{
	getWindow().handleEvent(event);
	m_Input.handleEvent(event);
}

void GameState::onUpdate(const float deltaTime)
{
	m_Level.update(deltaTime);

	m_Physics.update(deltaTime);
}

void GameState::onRender()
{
	getWindow().setView(getWindow().getDefaultView());

	getWindow().clear();

	m_Level.render(getWindow());
	m_Physics.renderBoxes(getWindow());

	getWindow().display();
}

void GameState::initBinds()
{
	m_Input.addBind(sf::Keyboard::Escape,
		[&](sf::Event::KeyEvent) {
			removeState();
		}, "Rimuove lo Stato attuale");
	m_Input.addBind(sf::Keyboard::Num1,
		[&](sf::Event::KeyEvent) {
			for (size_t i = 0; i < 1000; i++)
			{
				auto tile = new Peach::Tile(getAsset<Peach::Texture>("tiles"), nullptr);
				tile->setID(10);
				m_Level.getEntityManager().add(tile);
			}
		}, "Test Memory leak - EntityManager");
	m_Input.addBind(sf::Keyboard::Num2,
		[&](sf::Event::KeyEvent) {
			auto& tilemap = m_Level.getTileMap();
			tilemap.setSize(tilemap.getSize() * 2);
		}, "Test Memory leak - TileMap");

	m_Input.addBind(sf::Keyboard::E,
		[&](sf::Event::KeyEvent) {
			static bool limited = false;
			limited = !limited;

			auto& data = m_Data.lock();
			getWindow().setFramerateLimit(limited ? 2 : getWindow().getConfig().getValue<int>(Peach::WindowConfig::FPSLIMIT));
		}, "Test - Limit Framerate");
}
