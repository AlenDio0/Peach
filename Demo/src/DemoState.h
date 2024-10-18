#pragma once
#include <Peach/State/State.h>
#include <Peach/GUI/GUIManager.h>
#include <Peach/Assets/AssetManager.h>

class DemoState : public Peach::State
{
public:
	DemoState(Peach::Ref<Peach::Data> data);
	~DemoState();

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	Peach::GUIManager m_GUIManager;
	enum
	{
		RIMPIAZZA = 0,
		GIOCA,
		BOX
	};

	sf::Sound m_Sound;
};
