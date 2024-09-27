#pragma once
#include <Peach\State.h>

class GameState : public Peach::State
{
public:
	GameState(Peach::DataRef data);
	~GameState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	// TODO: Add a player and boxes to collide
};

