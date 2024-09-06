#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	class PEACH_API Button : public GUIObject
	{
	public:
		Button(const sf::Vector2f& size, const sf::String& label, const sf::Font* font);
		virtual ~Button() = default;

		virtual void setSecondaryColor(const sf::Color& color) override;
		virtual void setPosition(const sf::Vector2f& position);
		virtual void setSize(const sf::Vector2f& size);
		void setLabel(const sf::String& label);
		void setCharSize(const sf::Uint32& size);
		void setFont(const sf::Font& font);
		void setLabelStyle(const sf::Text::Style& style);

		const sf::Vector2f& getSize() const;
		const sf::String& getLabel() const;

		virtual void render(sf::RenderTarget* target) const;
	protected:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;
	};
}
