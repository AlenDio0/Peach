#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::Data> data)
	: Peach::State(data, "Game"), m_Level("level.txt", m_Data->assets.getAsset<Peach::Texture>("TEXTURE_TILES"))
{
	initBinds();
}

GameState::~GameState()
{
}

void GameState::onEvent()
{
	for (sf::Event event; m_Data->window.pollEvent(event);)
	{
		m_Controller.handleEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Data->window.close();
			break;
		}
	}
}

void GameState::onUpdate()
{
	m_Controller.update();
}

void GameState::onRender()
{
	m_Data->window.getRenderer()->setView(m_Data->window.getRenderer()->getView());

	m_Data->window.getRenderer()->clear();

	m_Level.render(m_Data->window.getRenderer());

	m_Data->window.display();
}

void GameState::initBinds()
{
	/*
	const auto& tilesize = m_Map.getTileSize();
	const auto& mapsize = m_Map.getSize();
	*/
	m_Controller.bind(sf::Keyboard::Escape,
		[&]() {
			m_Data->machine.removeState();
		}, "Rimuove lo Stato attuale", true);
	/*
	m_Controller.bind(sf::Keyboard::Num1,
		[&]() {
			m_Map.setTileSize({ tilesize.x + 1.f, tilesize.y + 1.f });
		}, "Aumenta la grandezza dei tile", true);
	m_Controller.bind(sf::Keyboard::Num2,
		[&]() {
			m_Map.setTileSize({ tilesize.x - 1.f, tilesize.y - 1.f });
		}, "Diminuisce la grandezza dei tile", true);
	m_Controller.bind(sf::Keyboard::Num3,
		[&]() {
			m_Map.setSize({ mapsize.x + 1, mapsize.y });
		}, "Aumenta la mappa verso destra", true);
	m_Controller.bind(sf::Keyboard::Num4,
		[&]() {
			m_Map.setSize({ mapsize.x - 1, mapsize.y });
		}, "Diminuisce la mappa verso sinistra", true);
	m_Controller.bind(sf::Keyboard::Num5,
		[&]() {
			m_Map.setSize({ mapsize.x, mapsize.y + 1 });
		}, "Aumenta la mappa verso il basso", true);
	m_Controller.bind(sf::Keyboard::Num6,
		[&]() {
			m_Map.setSize({ mapsize.x, mapsize.y - 1 });
		}, "Diminuisce la mappa verso l'alto", true);
	m_Controller.bind(sf::Keyboard::Up,
		[&]() {
			m_View.width += 1;
			m_View.height += 1;
		}, "Aumenta la grandezza della visuale", true);
	m_Controller.bind(sf::Keyboard::Down,
		[&]() {
			if (m_View.width == 0)
			{
				return;
			}
			m_View.width -= 1;
			m_View.height -= 1;
		}, "Diminuisce la grandezza della visuale", true);
	m_Controller.bind(sf::Keyboard::Right,
		[&]() {
			m_View.x += 1;
			m_View.y += 1;
		}, "Sposta la visuale verso in basso a sinistra", true);
	m_Controller.bind(sf::Keyboard::Left,
		[&]() {
			m_View.x -= 1;
			m_View.y -= 1;
		}, "Sposta la visuale verso in alto a destro", true);

	m_Controller.bind(sf::Mouse::Left,
		[&]() {
			m_Map.setTexture(sf::Texture());
		}, "Rimuove la texture dei tile", true);
	m_Controller.bind(sf::Mouse::Right,
		[&]() {
			m_Map.setTexture(m_Data->assets.getAsset<Peach::Texture>("TEXTURE_TILES"));
		}, "Imposta la texture dei tile", true);*/
}
