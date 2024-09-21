#include <Peach.h>
#include "DemoState.h"

class DemoApp : public Peach::Application
{
public:
public:
	DemoApp()
	{
		m_Data->window.create("Titolo", { 500, 500 });

		m_Data->assets.loadAsset<Peach::Texture>("TEXTURE_CHECK", "assets/check.png");
		m_Data->assets.loadAsset<Peach::Font>("FONT_CONSOLA", "assets/consola.ttf");
		m_Data->assets.loadAsset<Peach::Sound>("SOUND_GENERIC", "assets/sound.mp3");

		addState(Peach::IStateRef(new DemoState(m_Data)), false);
	}

	~DemoApp()
	{
	}
};

Peach::Application* Peach::CreateApplication()
{
	Peach::Log::initFile("logs/demoapp.log", 1, 2);

	return new DemoApp();
}
