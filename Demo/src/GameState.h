#pragma once

#include <Peach/State/AppState.h>

#include <Peach/Game.h>

class GameState : public Peach::AppState
{
public:
	GameState(Peach::Ref<Peach::Data> data);
	~GameState();

	virtual void onEvent(const sf::Event& event) override;
	virtual void onUpdate(const float deltaTime) override;
	virtual void onRender() override;
private:
	class Player : public Peach::GameObject
	{
	public:
		Player(const Peach::Texture& texture, Peach::Vec2f position)
			: GameObject(texture)
		{
			getTransform().position = position;
			auto& scale = getTransform().scale *= 1.10f;

			addComponent<Peach::RigidBody>(Peach::FloatRect(Peach::Vec2f(4.f, 32.f) * scale, Peach::Vec2f(24.f, 32.f) * scale), true);
			addComponent<Peach::LinearMovement>(200.f, 200.f);
		}
		~Player() = default;

		void update(float deltaTime)
		{
			auto& movement = *has<Peach::LinearMovement>().lock();
			Peach::Vec2f& velocity = movement.velocity, speed = movement.speed;
			velocity *= 0.f;

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
		}
	};
	class NPC : public Peach::GameObject
	{
	public:
		NPC(const Peach::Texture& texture, Peach::Vec2f position)
			: GameObject(texture)
		{
			getTransform().position = position;

			addComponent<Peach::RigidBody>(Peach::FloatRect(Peach::Vec2f(0.f, 0.f), Peach::Vec2f(texture.getSize()) * getTransform().scale), true);
			//addComponent<Peach::LinearMovement>(200.f, 200.f);
		}
		~NPC() = default;

		void update(float deltaTime)
		{
			//auto& movement = *has<Peach::LinearMovement>().lock();
			//Peach::Vec2f& velocity = movement.velocity, speed = movement.speed;
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

