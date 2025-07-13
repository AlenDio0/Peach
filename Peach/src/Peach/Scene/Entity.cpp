#include "peachpch.h"
#include "Entity.h"

namespace Peach
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_Handle(handle), m_Scene(scene)
	{
	}

	const UUID& Entity::getUUID()
	{
		return getComponent<IDComponent>().id;
	}

	const std::string& Entity::getTag()
	{
		return getComponent<TagComponent>().tag;
	}

	Entity::operator uint32_t() const
	{
		return (uint32_t)m_Handle;
	}

	Entity::operator entt::entity() const
	{
		return m_Handle;
	}
}
