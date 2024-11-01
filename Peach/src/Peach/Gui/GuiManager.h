#pragma once

#include "GuiObject.h"

namespace Peach
{
	using GuiKey = uint32_t;
	template<typename T>
	using RawMap = std::unordered_map<uint32_t, T*>;
	template<typename T>
	using RefMap = std::unordered_map<uint32_t, Ref<T>>;

	class PEACH_API GuiManager
	{
	public:
		GuiManager();
		~GuiManager();

		Ref<GuiObject> operator[](GuiKey key);

		void add(GuiKey key, GuiObject* object);
		void remove(GuiKey key);
		void remove(GuiObject* object);

		const sf::Cursor& getCursor() const;

		template<typename T = GuiObject>
		RawMap<T> getGuiObjects(GuiType type)
		{
			RawMap<T> objects;
			for (auto& [key, object] : m_Objects)
			{
				if (object->getType() == type)
				{
					objects[key] = static_cast<T*>(object.get());
				}
			}

			return objects;
		}
		RawMap<GuiObject> getGuiObjects(const std::vector<GuiType>& types = {});

		void handleEvent(const sf::Event& event);

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		RefMap<GuiObject> m_Objects;

		static sf::Vector2i m_MousePosition;
	};
}
