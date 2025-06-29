#include "peachpch.h"
#include "EntityManager.h"

namespace Peach
{
	EntityManager::EntityManager()
	{
		PEACH_CORE_TRACE("EntityManager costruito");
	}

	EntityManager::~EntityManager()
	{
		PEACH_CORE_TRACE("EntityManager distrutto");
	}

	void EntityManager::update(const float deltaTime)
	{
		for (auto& [uuid, obj] : getObjects())
		{
			if (auto entity = obj.lock())
			{
				entity->update(deltaTime);
			}
		}
	}
}
