#include "GameState.h"

GameState::GameState(Peach::Ref<Peach::AppData> data)
	: Peach::AppState(data, "Game")
{
	auto entity = m_Scene.createEntity();
	Peach::Vec2f scale = entity.addComponent<Peach::TransformComponent>(Peach::Vec2f(100.f, 100.f), Peach::Vec2f(1.5f, 1.5f)).scale;
	entity.addComponent<Peach::SpriteComponent>(getTexture("player"));
	entity.addComponent<Peach::HitboxComponent>(Peach::FloatRect(Peach::Vec2f(), (Peach::Vec2f)getTexture("player").getSize() * scale));
	entity.addComponent<Peach::UpdateComponent>([](Peach::Entity entity, float deltaTime)
		{
			auto& transform = entity.getComponent<Peach::TransformComponent>();
			Peach::Vec2f velocity = {}, speed = { 500.f, 500.f };

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				velocity.y = -speed.y * deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				velocity.y = speed.y * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				velocity.x = -speed.x * deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity.x = speed.x * deltaTime;
			}

			transform.position += velocity;
		});

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
	m_Scene.update(deltaTime);
}

void GameState::onRender()
{
	getWindow().setView(getWindow().getDefaultView());

	getWindow().clear();

	m_Scene.render(getWindow());
	m_Scene.renderHitbox(getWindow());

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
			getWindow().setFramerateLimit(limited ? 10 : getWindow().getConfig().getValue<int>(Peach::WindowConfig::FPSLIMIT));
		}, "Test - Limit Framerate");
}
