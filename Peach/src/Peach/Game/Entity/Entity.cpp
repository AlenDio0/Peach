#include "peachpch.h"
#include "Entity.h"

namespace Peach
{
	Entity::Entity()
		: Entity(true) {
	}

	Entity::Entity(bool debugLog)
		: m_DebugLog(debugLog)
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("Entity costruito");
		}
	}

	Entity::~Entity()
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("Entity distrutto");
		}
	}
}