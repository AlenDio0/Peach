#pragma once

#include <Peach/State/AppState.h>

#include <Peach/Gui/GuiManager.h>
#include <Peach/Assets/AssetManager.h>
#include <Peach/System/InputController.h>

class DemoState : public Peach::AppState
{
public:
	DemoState(Peach::Ref<Peach::AppData> data);
	~DemoState();

	virtual void onEvent(const sf::Event& event) override;
	virtual void onUpdate(const float deltaTime) override;
	virtual void onRender() override;
private:
	Peach::GuiManager m_GuiManager;
	Peach::InputController m_Input;

	Peach::Ref<Peach::Sound> m_RemovedSound;

	Peach::UUID m_InsertPin;
	Peach::UUID m_TextBox;
};
