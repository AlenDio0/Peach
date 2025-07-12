#pragma once

#include "Peach/Core/Core.h"

#include "Registry.h"

namespace Peach
{
	class Entity;

	class Scene
	{
	public:
		Entity createEntity();
	private:
		Registry m_Registry;

		friend class Entity;
	};
}
