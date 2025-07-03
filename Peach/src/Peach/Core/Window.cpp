#include "peachpch.h"
#include "Window.h"

namespace Peach
{
	Window::Window()
	{
		PEACH_CORE_INFO("Window costruito");
	}

	Window::~Window()
	{
		PEACH_CORE_INFO("Window distrutto");
	}

	void Window::init()
	{
		using WKey = WindowConfig::Key;

		std::string title = m_Config.getValue<std::string>(WKey::TITLE);
		Vec2u size = { m_Config.getValue<uint32_t>(WKey::WIDTH), m_Config.getValue<uint32_t>(WKey::HEIGHT) };
		uint32_t style = m_Config.getValue<uint32_t>(WKey::STYLE);
		bool vsync = m_Config.getValue<bool>(WKey::VSYNC);
		uint32_t fpslimit = m_Config.getValue<uint32_t>(WKey::FPSLIMIT);

		PEACH_CORE_INFO("Window::init(), [title: {}, size: {}, vsync: {}, fpslimit: {}]", title, size, vsync, fpslimit);

		create(sf::VideoMode(size.x, size.y), title, style);
		setVerticalSyncEnabled(vsync);
		setFramerateLimit(fpslimit);
	}

	WindowConfig& Window::getConfig()
	{
		return m_Config;
	}

	void Window::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			close();
			break;
		}
	}
}
