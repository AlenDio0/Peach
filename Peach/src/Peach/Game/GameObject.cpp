#include "peachpch.h"
#include "GameObject.h"

namespace Peach
{
	GameObject::GameObject()
		: GameObject(true)
	{
	}

	GameObject::GameObject(bool debuglog)
		: m_DebugLog(debuglog)
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GameObject costruito");
		}
	}

	GameObject::~GameObject()
	{
		if (m_DebugLog)
		{
			PEACH_CORE_TRACE("GameObject distrutto");
		}
	}
}