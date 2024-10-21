#include "peachpch.h"
#include "Window.h"

namespace Peach
{
	Window::Window()
		: m_Window(MakeScope<sf::RenderWindow>())
	{
		PEACH_CORE_INFO("Window costruito");
	}

	Window::~Window()
	{
		PEACH_CORE_INFO("Window distrutto");
	}

	bool Window::create()
	{
		using WKey = WindowConfig::Key;

		std::string title = m_Config.getValue<std::string>(WKey::TITLE);
		Vec2u size = { m_Config.getValue<uint32_t>(WKey::WIDTH), m_Config.getValue<uint32_t>(WKey::HEIGHT) };
		uint32_t style = m_Config.getValue<uint32_t>(WKey::STYLE);
		bool vsync = m_Config.getValue<bool>(WKey::VSYNC);
		uint32_t fpslimit = m_Config.getValue<uint32_t>(WKey::FPSLIMIT);

		PEACH_CORE_INFO("Window::create(), [title: {}, size: {}, vsync: {}, fpslimit: {}]", title, size, vsync, fpslimit);

		m_Window->create(sf::VideoMode(size.x, size.y), title, style);
		m_Window->setVerticalSyncEnabled(vsync);
		m_Window->setFramerateLimit(fpslimit);

		PEACH_RETURN_ASSERT(m_Window, "Window::create(), Window e' nullo");
	}


	void Window::close()
	{
		PEACH_CORE_INFO("Window::close(), Window e' in fase di chiusura");

		m_Window->close();
	}

	bool Window::isRunning() const
	{
		return m_Window->isOpen() && m_Window;
	}

	WindowConfig& Window::getConfig()
	{
		return m_Config;
	}

	void Window::setMouseCursor(const sf::Cursor& cursor)
	{
		m_Window->setMouseCursor(cursor);
	}

	bool Window::pollEvent(sf::Event& event) const
	{
		return m_Window->pollEvent(event);
	}

	sf::RenderTarget* Window::getRenderer()
	{
		return m_Window.get();
	}

	void Window::display()
	{
		m_Window->display();
	}
}
