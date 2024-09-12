#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	typedef std::shared_ptr<GUIObject> GUIObjectRef;
	using GUIObjectMap = std::unordered_map<uint32_t, GUIObjectRef>;

	class PEACH_API GUIManager
	{
	public:
		GUIManager();
		~GUIManager();

		GUIObjectRef operator[](const uint32_t& key);

		void add(const uint32_t& key, GUIObject* value);

		sf::Cursor::Type getCursor() const;

		GUIObjectMap getGUIObjects(const std::vector<GUIType>& types = {});

		bool pollPressed(uint32_t& pressed);

		void handleEvent(const sf::Event& event);
		void update();
		void render(sf::RenderTarget* target) const;
	private:
		GUIObjectMap m_Objects;
		uint32_t m_Pressed;

		static sf::Vector2i m_MousePosition;
	};
}
