#pragma once

#include <Peach/State/AppState.h>

#include <Peach/System/InputController.h>
#include <Peach/Scene/Entity.h>

class GameState : public Peach::AppState
{
public:
	GameState(Peach::Ref<Peach::AppData> data);
	~GameState();

	virtual void onEvent(const sf::Event& event) override;
	virtual void onUpdate(const float deltaTime) override;
	virtual void onRender() override;
private:
	Peach::InputController m_Input;
	Peach::Scene m_Scene;

private:
	void initBinds();
};

