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

	bool Window::create(const sf::String& title, const sf::Vector2u& size)
	{
		m_Window->create(sf::VideoMode(size.x, size.y), title);

		PEACH_CORE_INFO("Window::create(title: {}, size: {} {})", title.toAnsiString(), size.x, size.y);

		m_Title = title;
		m_OriginalSize = size;

		PEACH_RETURN_ASSERT(m_Window, "Window::create(...), Window e' nullo");
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

	const sf::String& Window::getTitle() const
	{
		return m_Title;
	}

	const sf::Vector2u Window::getOriginalSize() const
	{
		return m_OriginalSize;
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
