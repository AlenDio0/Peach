#include "peachpch.h"
#include "Scene.h"

#include "Entity.h"

namespace Peach
{
	Entity Scene::createEntity()
	{
		Entity entity = { m_Registry.create(), this };

		return entity;
	}
}
