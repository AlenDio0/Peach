#pragma once

#include "GuiObject.h"

#include "Peach/System/UUID.h"

namespace Peach
{
	template<typename T>
	using WeakMap = std::unordered_map<UUID, std::weak_ptr<T>>;
	template<typename T>
	using RefMap = std::unordered_map<UUID, Ref<T>>;

	class PEACH_API GuiManager
	{
	public:
		GuiManager();
		~GuiManager();

		UUID add(Ref<GuiObject> object);
		UUID add(GuiObject* object);

		void remove(UUID uuid);
		void remove(Ref<GuiObject> object);
		void remove(GuiObject* object);

		const sf::Cursor& getCursor() const;

		template<typename T = GuiObject>
		std::weak_ptr<T> getGuiObject(UUID uuid)
		{
			try
			{
				return std::dynamic_pointer_cast<T>(m_Objects.at(uuid));
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("GuiManager::getGuiObject(uuid: {}), Catturata eccezione: {}", uuid, e.what());
				return Ref<T>(nullptr);
			}
		}

		template<typename T = GuiObject>
		WeakMap<T> getGuiObjects(GuiType type)
		{
			WeakMap<T> objects;
			for (auto& [key, object] : m_Objects)
			{
				if (object->getType() == type)
				{
					objects[key] = std::static_pointer_cast<T>(object);
				}
			}

			return objects;
		}
		WeakMap<GuiObject> getGuiObjects(const std::vector<GuiType>& types = {});

		void handleEvent(const sf::Event& event);

		void update();
		void render(sf::RenderTarget* target) const;
	private:
		RefMap<GuiObject> m_Objects;

		static sf::Vector2i m_MousePosition;
	};
}
