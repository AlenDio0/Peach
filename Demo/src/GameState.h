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
			auto& scale = getTransform().scale *= 1.4f;

			addComponent<Peach::RigidBody>(Peach::FloatRect(4.f * scale.x, 24.f * scale.y, 24.f * scale.x, 40.f * scale.y), true);
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

