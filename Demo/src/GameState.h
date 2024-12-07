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
	Peach::TileMap m_TileMap;
	Peach::InputController m_Input;
	// TODO: Add a player and boxes to collide
private:
	void initBinds();
};

