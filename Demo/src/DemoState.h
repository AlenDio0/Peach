#pragma once
#include <Peach/Data.h>
#include <Peach/State.h>
#include <Peach/GUI/GUIManager.h>

class DemoState : public Peach::State
{
public:
	DemoState(Peach::DataRef data);
	~DemoState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	Peach::GUIManager m_GUIManager;
	enum
	{
		RIMPIAZZA = 0,
		IMPOSTAZIONI
	};
};
