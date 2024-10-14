#pragma once
#include <Peach/State/State.h>

#include <Peach\Game\Level\Tile\TileMap.h>
#include <Peach\Game\Player\PlayerController.h>

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
	Peach::PlayerController m_Controller;

	Peach::IntRect m_View;
	// TODO: Add a player and boxes to collide
private:
	void initBinds();
};

