#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	typedef std::shared_ptr<GUIObject> GUIObjectRef;

	class PEACH_API GUIManager
	{
	public:
		GUIManager();
		~GUIManager();

		GUIObjectRef operator[](const uint32_t& key);

		void add(const uint32_t& key, GUIObjectRef value);

		const sf::Cursor::Type& getCursor() const;

		const uint32_t& getPressed();

		void handleEvent(sf::Event event);
		void render(sf::RenderTarget* target) const;
	private:
		std::unordered_map<uint32_t, GUIObjectRef> m_Objects;
		std::unordered_map<uint32_t, bool> m_CursorOn;

		std::stack<uint32_t> m_Pressed;
	};
}
