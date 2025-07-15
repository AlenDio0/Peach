#include "GameState.h"

#include <Peach/System/Random.h>
#include <Peach/System/Timer.h>

GameState::GameState(Peach::Ref<Peach::AppData> data)
	: Peach::AppState(data, "Game"), m_Scene("level.txt", getTexture("tiles"))
{
	using Key = sf::Keyboard::Key;

	createPlayer({ Key::W, Key::S, Key::A, Key::D });
	createPlayer({ Key::Up, Key::Down, Key::Left, Key::Right });
	createPlayer({ Key::T, Key::G, Key::F, Key::H });

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
	static Peach::Timer timer;
	if (timer.elapsedTimeSec() > 0.5f)
	{
		timer.reset();
		getWindow().setTitle("FPS: " + std::to_string((int)(1 / deltaTime)));
	}

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

Peach::Entity GameState::createPlayer(std::array<sf::Keyboard::Key, 4> keys)
{
	static uint32_t playerCount = 0;
	playerCount++;

	Peach::Entity player = m_Scene.createEntity("Player " + std::to_string(playerCount));
	Peach::Vec2f& scale = player.addComponent<Peach::TransformComponent>(Peach::Vec2f(75.f + (PEACH_RANDOM_UINT(0, 9) * 32.f), 75.f + (PEACH_RANDOM_UINT(0, 5) * 48.f)), Peach::Vec2f(2.f, 2.f)).scale;
	sf::Sprite& sprite = player.addComponent<Peach::SpriteComponent>(getTexture("player"), 1.f).sprite;
	player.addComponent<Peach::HitboxComponent>(Peach::FloatRect(Peach::Vec2f(), (Peach::Vec2f)sprite.getLocalBounds().getSize() * scale));
	auto& textComp = player.addComponent<Peach::TextComponent>(player.getComponent<Peach::TagComponent>().tag, getFont("consola"), 25u);
	textComp.offset = Peach::Vec2f(((sprite.getLocalBounds().getSize().x * scale.x) / 2.f) - (textComp.text.getGlobalBounds().getSize().x / 2.f), -32.f);

	player.addComponent<Peach::VelocityComponent>();
	player.addComponent<KeyComponent>(keys);
	player.addComponent<Peach::UpdateComponent>([&](Peach::Entity entity, float deltaTime)
		{
			Peach::Vec2f& position = entity.getComponent<Peach::TransformComponent>().position;
			Peach::Vec2f& velocity = entity.getComponent<Peach::VelocityComponent>().velocity *= 0.f;
			auto& keys = entity.getComponent<KeyComponent>().keys;
			Peach::Vec2f speed = { 300.f, 300.f };

			if (sf::Keyboard::isKeyPressed(keys[0]))
			{
				velocity.y = -speed.y * deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(keys[1]))
			{
				velocity.y = speed.y * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(keys[2]))
			{
				velocity.x = -speed.x * deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(keys[3]))
			{
				velocity.x = speed.x * deltaTime;
			}

			position += velocity;

			if (position.x <= 0.f || position.x >= getWindow().getSize().x || position.y <= 0.f || position.y >= getWindow().getSize().y)
			{
				createPlayer(keys);
				m_Scene.destroyEntity(entity);
			}
		});

	return player;
}
