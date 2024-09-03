#include "peachpch.h"
#include "Application.h"

namespace Peach
{
	Application::Application()
	{
		PEACH_CORE_INFO("Applicazione inizializzata");
	}

	Application::~Application()
	{
		delete m_Data;

		PEACH_CORE_INFO("Applicazione distrutta");
	}

	void Application::addState(IStateRef newState, bool isReplacing)
	{
		m_Data->machine.addState(newState, isReplacing);
	}

	void Application::removeState()
	{
		m_Data->machine.removeState();
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
				PEACH_CORE_FATAL("Non c'e' nessuno stato da far partire");
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

		PEACH_CORE_INFO("Applicazione chiusa nello stato \"{}\"", m_Data->machine.getCurrentState()->getName());
	}
}
