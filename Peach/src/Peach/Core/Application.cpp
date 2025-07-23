#include "peachpch.h"
#include "Application.h"

namespace Peach
{
	Application::Application()
		: m_Data(MakeRef<AppData>())
	{
		PEACH_CORE_INFO("Applicazione costruita");

		m_Data->window = MakeScope<Window>();
		m_Data->window->init();
	}

	Application::~Application()
	{
		PEACH_CORE_INFO("Applicazione distrutta");
	}

	void Application::removeState()
	{
		m_Data->machine.removeState();
	}

	const Scope<State>& Application::getCurrentState() const
	{
		return m_Data->machine.getCurrentState();
	}

	void Application::loadTexture(const std::string& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Texture>(key, path, force);
	}

	void Application::loadFont(const std::string& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Font>(key, path, force);
	}

	void Application::loadSound(const std::string& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Sound>(key, path, force);
	}

	void Application::initAssetFile()
	{
		m_Data->assets.initFile();
	}

	void Application::run()
	{
		Timer clock;

		do
		{
			float deltaTime = clock.elapsedTimeSec();
			clock.reset();

			m_Data->machine.update();
			if (!getCurrentState())
			{
				PEACH_CORE_FATAL("Application::run(), Impossibile continuare l'applicazione, AppState attuale nullo");
				return;
			}

			sf::Event event;
			if (getCurrentState()->isWaitEvent() && m_Data->window->waitEvent(event))
			{
				getCurrentState()->onEvent(event);
			}
			else while (m_Data->window->pollEvent(event))
			{
				getCurrentState()->onEvent(event);
			}

			getCurrentState()->onUpdate(deltaTime);
			getCurrentState()->onRender();
		} while (m_Data->window->isOpen());

		PEACH_CORE_INFO("Application::run(), Applicazione chiusa nello AppState \"{}\"", getCurrentState() ? getCurrentState()->getName() : "Unknown");
	}
}
