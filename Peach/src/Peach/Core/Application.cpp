#include "peachpch.h"
#include "Application.h"

namespace Peach
{
	Application::Application()
		: m_Data(MakeRef<Data>())
	{
		PEACH_CORE_INFO("Applicazione costruita");

		m_Data->window.create();
	}

	Application::~Application()
	{
		PEACH_CORE_INFO("Applicazione distrutta");
	}

	void Application::removeState()
	{
		m_Data->machine.removeState();
	}

	void Application::loadTexture(const AssetKey& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Texture>(key, path, force);
	}

	void Application::loadFont(const AssetKey& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Font>(key, path, force);
	}

	void Application::loadSound(const AssetKey& key, const std::string& path, bool force) const
	{
		loadAsset<Peach::Sound>(key, path, force);
	}

	void Application::initAssetFile()
	{
		m_Data->assets.initFile();
	}

	void Application::run()
	{
		const std::chrono::microseconds FRAME_DURATION(16667);
		std::chrono::microseconds lag(0);
		std::chrono::steady_clock::time_point previous_time = std::chrono::steady_clock::now();

		do
		{
			std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);
			lag += delta_time;
			previous_time += delta_time;

			m_Data->machine.update();
			if (!m_Data->machine.getCurrentState())
			{
				PEACH_CORE_FATAL("Application::run(), Impossibile continuare l'applicazione, State attuale nullo");
				return;
			}

			while (FRAME_DURATION <= lag)
			{
				lag -= FRAME_DURATION;

				m_Data->machine.getCurrentState()->onEvent();

				m_Data->machine.getCurrentState()->onUpdate();

				if (FRAME_DURATION > lag)
				{
					m_Data->machine.getCurrentState()->onRender();
				}
			}
		} while (m_Data->window.isRunning());

		PEACH_CORE_INFO("Application::run(), Applicazione chiusa nello State \"{}\"", m_Data->machine.getCurrentState()->getName());
		m_Data->machine.clean();
	}
}
