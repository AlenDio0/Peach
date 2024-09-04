#include "peachpch.h"
#include "Window.h"

namespace Peach
{
	Window::Window()
		: m_Window(new sf::RenderWindow())
	{
		PEACH_CORE_INFO("Window inizializzato");
	}

	Window::~Window()
	{
		delete m_Window;

		PEACH_CORE_INFO("Window distrutto");
	}

	const bool& Window::create(sf::String title, sf::Vector2u size)
	{
		m_Window->create(sf::VideoMode(size.x, size.y), title);

		PEACH_CORE_INFO("Window creata: {} ({}, {})", title.toAnsiString(), size.x, size.y);

		m_Title = title;
		m_OriginalSize = size;

		PEACH_RETURN_ASSERT(m_Window, "Window è nullo");
	}

	void Window::close()
	{
		PEACH_CORE_INFO("Window e' in fase di chiusura");

		m_Window->close();
	}

	const bool& Window::isRunning() const
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

	const bool& Window::pollEvent(sf::Event& event) const
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
