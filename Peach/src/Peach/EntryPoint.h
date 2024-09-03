#pragma once

#ifdef PEACH_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
	Peach::Log::init();

	PEACH_CORE_INFO("Log inizializzati");

	auto app = Peach::CreateApplication();
	app->run();
	delete app;

	return 0;
}
#endif
