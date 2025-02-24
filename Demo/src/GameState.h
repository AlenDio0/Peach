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

