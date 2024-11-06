#pragma once

#include <Peach/State/State.h>

#include <Peach/Gui/GuiManager.h>
#include <Peach/Assets/AssetManager.h>
#include <Peach/System/InputController.h>

class DemoState : public Peach::State
{
public:
	DemoState(Peach::Ref<Peach::Data> data);
	~DemoState();

	virtual void onEvent() override;
	virtual void onUpdate() override;
	virtual void onRender() override;
private:
	Peach::GuiManager m_GuiManager;
	Peach::InputController m_Input;

	sf::Sound m_Sound;

	Peach::UUID m_InsertPin;
};
