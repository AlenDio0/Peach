#include "peachpch.h"
#include "Window.h"

namespace Peach
{
	Window::Window()
		: m_Window(new sf::RenderWindow())
	{
		PEACH_CORE_INFO("Window costruito");
	}

	Window::~Window()
	{
		delete m_Window;

		PEACH_CORE_INFO("Window distrutto");
	}

	bool Window::create()
	{
		using WKey = WindowConfig::Key;

		std::string title = m_Config[WKey::TITLE];
		uint32_t width = std::abs(stoi(m_Config[WKey::WIDTH]));
		uint32_t height = std::abs(stoi(m_Config[WKey::HEIGHT]));
		uint32_t style = stoi(m_Config[WKey::STYLE]);
		bool vsync = stoi(m_Config[WKey::VSYNC]);
		uint32_t fpslimit = std::abs(stoi(m_Config[WKey::FPSLIMIT]));

		PEACH_CORE_INFO("Window::create(), [title: {}, size: {} {}, vsync: {}, fpslimit: {}]", title, width, height, vsync, fpslimit);

		m_Window->create(sf::VideoMode(width, height), title, style);
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
		return m_Window;
	}

	void Window::display()
	{
		m_Window->display();
	}
}
