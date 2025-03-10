#pragma once

#include "GuiObject.h"

#include "Peach/System/UUID.h"

namespace Peach
{
	class PEACH_API GuiManager
	{
	public:
		GuiManager();
		~GuiManager();

		UUID add(const Ref<GuiObject>& object);
		UUID add(GuiObject* object);

		void remove(const UUID uuid);
		void remove(const Ref<GuiObject>& object);
		void remove(GuiObject* object);
		template<typename T>
		void remove()
		{
			for (const auto& [uuid, obj] : getGuiObjects<T>())
			{
				remove(uuid);
			}
		}

		const sf::Cursor& getCursor() const;

		template<typename T = GuiObject>
		std::weak_ptr<T> getGuiObject(const UUID uuid)
		{
			try
			{
				auto object = std::dynamic_pointer_cast<T>(m_Objects.at(uuid));
				PEACH_ASSERT(object, "GuiManager::getGuiObject(...), Ritornato valore nullo, std::dynamic_pointer_cast fallito");

				return object;
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("GuiManager::getGuiObject(uuid: {}), Ritornato valore nullo. Catturata eccezione: {}", uuid, e.what());
				return Ref<T>(nullptr);
			}
		}

		template<typename T = GuiObject>
		std::unordered_map<UUID, std::weak_ptr<T>> getGuiObjects()
		{
			std::unordered_map<UUID, std::weak_ptr<T>> objects;
			for (auto& [key, object] : m_Objects)
			{
				auto obj = std::dynamic_pointer_cast<T>(object);
				if (obj)
				{
					objects[key] = obj;
				}
			}

			return objects;
		}

		void handleEvent(const sf::Event& event);

		void update(const float deltaTime);
		void render(sf::RenderTarget& target) const;
	private:
		std::unordered_map<UUID, Ref<GuiObject>> m_Objects;

		static sf::Vector2i m_MousePosition;
	};
}
