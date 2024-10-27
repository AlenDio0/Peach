#pragma once

#include "Peach/Core.h"

#include "GUIObject.h"

namespace Peach
{
	template<typename T>
	using RawMap = std::unordered_map<uint32_t, T*>;
	template<typename T>
	using RefMap = std::unordered_map<uint32_t, Ref<T>>;

	class PEACH_API GUIManager
	{
	public:
		GUIManager();
		~GUIManager();

		Ref<GUIObject> operator[](const uint32_t& key);

		void add(const uint32_t& key, GUIObject* object);
		void remove(const uint32_t& key);
		void remove(GUIObject* object);

		const sf::Cursor& getCursor() const;

		template<typename T = GUIObject>
		RawMap<T> getGUIObjects(const GUIType& type)
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
		RawMap<GUIObject> getGUIObjects(const std::vector<GUIType>& types = {});

		void handleEvent(const sf::Event& event);
		void onMouseMoved(const sf::Event& event);
		void onMousePressed(const sf::Event& event);
		void onTextEntered(const sf::Event& event);

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		RefMap<GUIObject> m_Objects;

		static sf::Vector2i m_MousePosition;
	};
}
