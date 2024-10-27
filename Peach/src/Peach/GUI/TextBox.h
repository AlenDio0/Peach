#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	class PEACH_API TextBox : public GUIObject
	{
	public:
		enum class Restriction
		{
			None = 0,
			Regular,
			AlphaDigit,
			Alpha,
			Digit
		};
	public:
		TextBox(const sf::Vector2f& size, const sf::Font& font, bool selected = false);
		TextBox(const sf::Vector2f& size, const sf::Font& font, size_t length, bool selected = false);
		TextBox(const sf::Vector2f& size, const std::string& placeholder, const sf::Font& font, size_t length, bool selected = false);
		~TextBox() = default;

		void setSelected(bool selected);
		void setRestriction(Restriction restriction);
		void setSize(const sf::Vector2f& size);
		void setPosition(const sf::Vector2f& position);
		void setPlaceholder(const std::string& placeholder);
		void setCharSize(uint32_t size);
		void setFont(const sf::Font& font);

		virtual void onPressed();

		std::string getBuff() const;
		const sf::Vector2f& getSize() const;

		static GUIType getStaticType();
		GUIType getType() const;

		void onTextEntered(uint32_t input);

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		sf::RectangleShape m_Container;
		sf::Text m_TextLabel;
		std::ostringstream m_Buff;
		size_t m_Length;

		std::string m_Placeholder;

		bool m_Selected;

		Restriction m_Restriction;

		static inline sf::Clock m_BlinkTimer;
	private:
		enum
		{
			DELETE_KEY = 8,
			ENTER_KEY = 13,
			ESCAPE_KEY = 27,
		};
	};
}
