#include "peachpch.h"
#include "Entity.h"

namespace Peach
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_Handle(handle), m_Scene(scene)
	{
	}
}
