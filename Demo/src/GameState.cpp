#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::AppData> data)
	: Peach::AppState(data, "Game")
{
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
}

void GameState::onRender()
{
	getWindow().setView(getWindow().getDefaultView());

	getWindow().clear();

	getWindow().display();
}

void GameState::initBinds()
{
	m_Input.addBind(sf::Keyboard::Escape,
		[&](sf::Event::KeyEvent) {
			removeState();
		}, "Rimuove lo Stato attuale");

	m_Input.addBind(sf::Keyboard::E,
		[&](sf::Event::KeyEvent) {
			static bool limited = false;
			limited = !limited;

			auto& data = m_Data.lock();
			getWindow().setFramerateLimit(limited ? 2 : getWindow().getConfig().getValue<int>(Peach::WindowConfig::FPSLIMIT));
		}, "Test - Limit Framerate");
}
