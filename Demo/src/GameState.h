#pragma once

#include <Peach/State/State.h>

#include <Peach/Game.h>

enum Tile
{
	Wall_UpLeftAngle = 0,
	Wall_Up = 1,
	Wall_UpRightAngle = 2,
	Wall_Left = 8,
	Wall_Right = 10,
	Wall_DownLeftAngle = 16,
	Wall_Down = 17,
	Wall_DownRightAngle = 18,
	Parquet = 9,
};

class GameState : public Peach::State
{
public:
	GameState(Peach::Ref<Peach::Data> data);
	~GameState();

	virtual void onEvent() override;
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
			addComponent<Peach::Physics>(Peach::Vec2f(), Peach::Vec2f(6.f, 6.f), 0.6f);
		}
		~Player() = default;

		void update()
		{
			auto physics = has<Peach::Physics>().lock();
			if (!physics)
			{
				return;
			}
			auto& [velocity, _, acceleration] = *physics;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				velocity.y -= acceleration;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				velocity.y += acceleration;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				velocity.x -= acceleration;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity.x += acceleration;
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

