#pragma once

#ifdef PEACH_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
	Peach::Log::init();

	auto app = Peach::CreateApplication();
	app->run();
	delete app;

	return 0;
}
#endif
