#include <Peach.h>
#include "DemoState.h"

Peach::Application* Peach::CreateApplication()
{
	Peach::Log::initFile("logs/demoapp.log", 1, 2);

	Peach::Application* app = new Peach::Application();

	app->loadAsset<Peach::Texture>("TEXTURE_CHECK", "assets/check.png");
	app->loadAsset<Peach::Font>("FONT_CONSOLA", "assets/consola.ttf");
	app->loadAsset<Peach::Sound>("SOUND_GENERIC", "assets/sound.mp3");
	app->loadAsset<Peach::Texture>("TEXTURE_TILES", "assets/tiles.png");

	app->addState<DemoState>(false);

	return app;
}
