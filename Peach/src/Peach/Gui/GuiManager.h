#pragma once

#include "GuiObject.h"

#include "Peach/System/UUID.h"

namespace Peach
{
	// TODO: Change from raw ptr to weak ptr
	template<typename T>
	using RawMap = std::unordered_map<UUID, T*>;
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
		T* getGuiObject(UUID uuid)
		{
			try
			{
				return static_cast<T*>(m_Objects.at(uuid).get());
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("GuiManager::getGuiObject(uuid: {}), Catturata eccezione: {}", uuid, e.what());
				return nullptr;
			}
		}

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
