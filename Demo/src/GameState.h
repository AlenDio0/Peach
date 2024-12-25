#pragma once

#include <Peach/State/State.h>

#include <Peach/Game.h>

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
			auto& scale = getTransform().scale *= 1.10f;

			addComponent<Peach::RigidBody>(Peach::FloatRect(Peach::Vec2f(4.f, 32.f) * scale, Peach::Vec2f(24.f, 32.f) * scale), true);
			addComponent<Peach::Movement>(Peach::Vec2f(0.2f, 0.2f), Peach::Vec2f(20.f, 20.f), 0.6f);
		}
		~Player() = default;

		void update()
		{
			auto& [velocity, _, __, acceleration] = *has<Peach::Movement>().lock();

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

