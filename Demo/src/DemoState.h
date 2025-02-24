#pragma once

#include <Peach/State/AppState.h>

#include <Peach/Gui/GuiManager.h>
#include <Peach/Assets/AssetManager.h>
#include <Peach/System/InputController.h>

class DemoState : public Peach::AppState
{
public:
	DemoState(Peach::Ref<Peach::Data> data);
	~DemoState();

	virtual void onEvent(sf::Event event) override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onRender() override;
private:
	Peach::GuiManager m_GuiManager;
	Peach::InputController m_Input;

	sf::Sound m_Sound;

	Peach::UUID m_InsertPin;
};
