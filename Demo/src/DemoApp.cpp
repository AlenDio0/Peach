#include <Peach.h>
#include "DemoState.h"

Peach::Application* Peach::CreateApplication()
{
	Peach::Log::initFile("logs/demoapp.log", 1, 256);

	Peach::Application* app = new Peach::Application();
	app->initAssetFile();

	app->addState<DemoState>(false);

	return app;
}
