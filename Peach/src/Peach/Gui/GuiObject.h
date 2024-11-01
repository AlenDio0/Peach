#pragma once

#include "Peach/Core/Core.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

namespace Peach
{
	enum class GuiType
	{
		None = 0,
		Button,
		Checkbox,
		TextBox
	};

	class PEACH_API GuiObject
	{
	public:
		struct PEACH_API Appearance
		{
			Appearance()
				: Appearance(sf::Color::Black, sf::Color::Black, sf::Color::White)
			{
			}Appearance(sf::Color primary, sf::Color secondary, sf::Color background)
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

		void addCallback(const std::function<void()>& callback);
		virtual void setSize(const sf::Vector2f& size) = 0;
		virtual void setPosition(const sf::Vector2f& position);

		void setAppearance(Appearance appearance);
		void setOutlineThickness(float thickness);
		void setPrimaryColor(sf::Color color);
		void setSecondaryColor(sf::Color color);
		void setBackgroundColor(sf::Color color);

		const sf::Vector2f& getPosition() const;
		bool isCursorOn(const sf::Vector2i& mouseposition) const;

		Appearance getAppearance() const;

		virtual GuiType getType() const;

		void callback() const;
		virtual void handleEvent(const sf::Event& event);

		virtual void update() = 0;
		virtual void render(sf::RenderTarget* target) const = 0;
	private:
		sf::Shape* m_Shape;
		Appearance m_Appearance;

		std::vector<std::function<void()>> m_CallbackSink;

		bool m_DebugLog;
	};
}
