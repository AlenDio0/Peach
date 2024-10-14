#include <Peach.h>
#include "DemoState.h"

class DemoApp : public Peach::Application
{
public:
public:
	DemoApp()
	{
		m_Data->window.create();

		m_Data->assets.loadAsset<Peach::Texture>("TEXTURE_CHECK", "assets/check.png");
		m_Data->assets.loadAsset<Peach::Font>("FONT_CONSOLA", "assets/consola.ttf");
		m_Data->assets.loadAsset<Peach::Sound>("SOUND_GENERIC", "assets/sound.mp3");

		m_Data->assets.loadAsset<Peach::Texture>("TEXTURE_TILES", "assets/tiles.png");

		addState(Peach::Ref<Peach::IState>(new DemoState(m_Data)), false);
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
