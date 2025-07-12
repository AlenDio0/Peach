#include "peachpch.h"
#include "Entity.h"

namespace Peach
{
	Entity::Entity(EntityHandle handle, Scene* scene)
		: m_Handle(handle), m_Scene(scene)
	{
	}
}
