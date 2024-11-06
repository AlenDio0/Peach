#pragma once

#include <Peach/State/State.h>

#include <Peach/Gui/GuiManager.h>
#include <Peach/Assets/AssetManager.h>

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
	enum
	{
		RIMPIAZZA = 0,
		GIOCA,
		BOX,
		TEXTBOX1,
		TEXTBOX2,
		TEXTBOX3
	};

	sf::Sound m_Sound;
};
