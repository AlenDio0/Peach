#pragma once

#include "Peach/Core/Core.h"

#include "Peach/System/UUID.h"

#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Peach
{
	template<typename T>
	class Manager
	{
	public:
		virtual ~Manager()
		{
			clear();

			PEACH_CORE_TRACE("Manager distrutto");
		}

		virtual UUID add(const Ref<T>& object, UUID uuid = UUID())
		{
			preAdd(object, uuid);

			PEACH_CORE_TRACE("Manager::add(object: {}), [uuid: {}]", object, uuid);
			if (!object)
			{
				PEACH_CORE_ERROR("Manager::add(...), Impossibile aggiungere un Object nullo");
				return 0;
			}

			m_Objects[uuid] = object;
			return uuid;
		}
		UUID add(T* object, UUID uuid = UUID())
		{
			return add(Ref<T>(object), uuid);
		}

		void remove(const Ref<T>& object)
		{
			PEACH_CORE_TRACE("Manager::remove(object: {})", object);
			for (auto& [key, obj] : m_Objects)
			{
				if (obj == object)
				{
					remove(key);
					break;
				}
			}
		}
		void remove(T* object)
		{
			remove(Ref<T>(object));
		}
		void remove(const UUID uuid)
		{
			PEACH_CORE_TRACE("Manager::remove(uuid: {})", uuid);
			m_Objects.erase(uuid);
		}

		void clear()
		{
			PEACH_CORE_TRACE("[Manager] {} Objects distrutti", m_Objects.size());
			m_Objects.clear();
		}

		std::weak_ptr<T> getObject(const UUID uuid) const
		{
			try
			{
				return m_Objects.at(uuid);
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("Manager::getObject(uuid: {}), Ritornato valore nullo. Catturata eccezione: {}", uuid, e.what());
				return Ref<T>(nullptr);
			}
		}
		template<typename U = T>
		std::weak_ptr<U> getObject(const UUID uuid) const
		{
			try
			{
				if (auto obj = getObject(uuid).lock())
				{
					auto object = std::dynamic_pointer_cast<U>(obj);
					PEACH_ASSERT(object, "Manager::getObject(uuid: {}), Ritornato valore nullo, std::dynamic_pointer_cast fallito", uuid);

					return object;
				}
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("Manager::getObject(uuid: {}), Ritornato valore nullo. Catturata eccezione: {}", uuid, e.what());
				return Ref<U>(nullptr);
			}
		}
		std::unordered_map<UUID, std::weak_ptr<T>> getObjects() const
		{
			std::unordered_map<UUID, std::weak_ptr<T>> objects;
			for (auto& [key, obj] : m_Objects)
			{
				objects[key] = obj;
			}

			return objects;
		}
		template<typename U = T>
		std::unordered_map<UUID, std::weak_ptr<U>> getObjects() const
		{
			std::unordered_map<UUID, std::weak_ptr<U>> objects;
			for (auto& [key, obj] : getObjects())
			{
				objects[key] = getObject<U>(key);
			}

			return objects;
		}

		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(const float deltaTime) = 0;
		virtual void render(sf::RenderTarget& target) const {};
	protected:
		virtual void preAdd(const Ref<T>& object, UUID& uuid) {}
	private:
		std::unordered_map<UUID, Ref<T>> m_Objects;
	};
}
