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
				: outline_thickness(outline), primary_color(primary), secondary_color(secondary), background_color(background)
			{
			}

			float outline_thickness;

			sf::Color primary_color;
			sf::Color secondary_color;
			sf::Color background_color;
		};
	public:
		GuiObject(sf::Shape& container, bool debuglog = true);
		virtual ~GuiObject();

		void addCallback(sf::Event::EventType type, const std::function<void(GuiObject&, sf::Event)>& callback);
		virtual void setSize(Vec2f size) = 0;
		virtual void setPosition(Vec2f position);

		void setAppearance(Appearance appearance);
		void setOutlineThickness(float thickness);
		void setPrimaryColor(sf::Color color);
		void setSecondaryColor(sf::Color color);
		void setBackgroundColor(sf::Color color);

		Vec2f getSize() const;
		Vec2f getPosition() const;
		bool isCursorOn(Vec2i mouseposition) const;
		bool isCursorOn(sf::Event::MouseMoveEvent event) const;
		bool isCursorOn(sf::Event::MouseButtonEvent event) const;

		Appearance getAppearance() const;

		void callback(sf::Event event);
		void handleEvent(sf::Event event);

		virtual void update() = 0;
		virtual void render(sf::RenderTarget* target) const = 0;
	protected:
		virtual void handleSpecEvent(sf::Event event);
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
