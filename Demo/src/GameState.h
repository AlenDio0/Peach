#pragma once

#include <Peach/State/State.h>

#include <Peach\Game.h>

class GameState : public Peach::State
{
public:
	GameState(Peach::Ref<Peach::Data> data);
	~GameState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	Peach::Level m_Level;
	Peach::InputController m_Controller;
	// TODO: Add a player and boxes to collide
private:
	void initBinds();
};

