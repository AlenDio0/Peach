#pragma once

#include <Peach/State/AppState.h>

#include <Peach/Game.h>

class GameState : public Peach::AppState
{
public:
	GameState(Peach::Ref<Peach::Data> data);
	~GameState();

	virtual void onEvent(sf::Event event) override;
	virtual void onUpdate() override;
	virtual void onRender() override;
private:
	class Player : public Peach::GameObject
	{
	public:
		Player(const Peach::Texture& texture, Peach::Vec2f position)
			: GameObject(texture)
		{
			getTransform().position = position;

			addComponent<Peach::RigidBody>(Peach::FloatRect(8.f, 32.f, 16.f, 32.f), true);
			addComponent<Peach::Movement>(Peach::Vec2f(), Peach::Vec2f(6.f, 6.f), 0.6f);
		}
		~Player() = default;

		void update()
		{
			auto physics = has<Peach::Movement>().lock();
			if (!physics)
			{
				return;
			}
			auto& [velocity, _, acceleration] = *physics;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				velocity += Peach::Vec2f::up() * acceleration;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				velocity += Peach::Vec2f::down() * acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				velocity += Peach::Vec2f::left() * acceleration;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity += Peach::Vec2f::right() * acceleration;
			}
		}
	};

private:
	Peach::Level m_Level;
	Peach::PhysicsEngine m_Physics;

	Player m_Player;
	Peach::InputController m_Input;

private:
	void initBinds();
};

