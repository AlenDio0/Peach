#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	using GUIObjectMap = std::unordered_map<uint32_t, Ref<GUIObject>>;

	class PEACH_API GUIManager
	{
	public:
		GUIManager();
		~GUIManager();

		Ref<GUIObject> operator[](const uint32_t& key);

		void add(const uint32_t& key, GUIObject* value);

		sf::Cursor::Type getCursor() const;

		GUIObjectMap getGUIObjects(const std::vector<GUIType>& types = {});

		void handleEvent(const sf::Event& event);
		void update();
		void render(sf::RenderTarget* target) const;
	private:
		GUIObjectMap m_Objects;

		static sf::Vector2i m_MousePosition;
	};
}
