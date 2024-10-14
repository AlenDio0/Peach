#pragma once
#include <Peach/State/State.h>

#include <Peach\Game\Tile\TileMap.h>

class GameState : public Peach::State
{
public:
	GameState(Peach::DataRef data);
	~GameState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	Peach::TileMap m_Map;

	Peach::IntRect m_View;
	// TODO: Add a player and boxes to collide
};

