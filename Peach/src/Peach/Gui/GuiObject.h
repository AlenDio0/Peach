#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/Vec2.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

namespace Peach
{
	class PEACH_API GuiObject
	{
	public:
		struct PEACH_API Appearance
		{
			Appearance()
				: Appearance(sf::Color::Black, sf::Color::Black, sf::Color::White)
			{
			}
			Appearance(sf::Color primary, sf::Color secondary, sf::Color background)
				: Appearance(0.f, primary, secondary, background)
			{
			}
			Appearance(float outline, sf::Color primary, sf::Color secondary, sf::Color background)
				: outlineThickness(outline), primaryColor(primary), secondaryColor(secondary), backgroundColor(background)
			{
			}

			float outlineThickness;

			sf::Color primaryColor;
			sf::Color secondaryColor;
			sf::Color backgroundColor;
		};
	public:
		GuiObject(sf::Shape& container, bool debugLog = true);
		virtual ~GuiObject();

		void addCallback(const sf::Event::EventType type, const std::function<void(GuiObject&, sf::Event)>& callback);
		virtual void setSize(const Vec2f size) = 0;
		virtual void setPosition(const Vec2f position);

		void setAppearance(const Appearance appearance);
		void setOutlineThickness(const float thickness);
		void setPrimaryColor(const sf::Color color);
		void setSecondaryColor(const sf::Color color);
		void setBackgroundColor(const sf::Color color);

		Vec2f getSize() const;
		Vec2f getPosition() const;
		bool isCursorOn(const Vec2i mouseposition) const;
		bool isCursorOn(const sf::Event::MouseMoveEvent event) const;
		bool isCursorOn(const sf::Event::MouseButtonEvent event) const;

		Appearance getAppearance() const;

		void callback(const sf::Event& event);
		void handleEvent(const sf::Event& event);

		virtual void update(const float deltaTime) = 0;
		virtual void render(sf::RenderTarget& target) const = 0;
	protected:
		virtual void handleSpecEvent(const sf::Event& event);
	private:
		struct EventCallback
		{
			sf::Event::EventType type;
			std::function<void(GuiObject&, sf::Event)> callback;
		};
	private:
		sf::Shape* m_Shape;
		Appearance m_Appearance;

		std::vector<EventCallback> m_Callbacks;

		bool m_DebugLog;
	};
}
