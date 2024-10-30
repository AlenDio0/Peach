#pragma once

#ifdef PEACH_PLATFORM_WINDOWS || PEACH_PLATFORM_LINUX || PEACH_PLATFORM_MACOS
int main(int argc, char** argv)
{
	Peach::Log::init();

	auto app = Peach::CreateApplication();
	app->run();
	delete app;

	return 0;
}
#endif
