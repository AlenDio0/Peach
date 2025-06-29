#pragma once

#include "Entity.h"

#include "Peach/System/Manager.h"

namespace Peach
{
	class PEACH_API EntityManager : public Manager<Entity>
	{
	public:
		EntityManager();
		virtual ~EntityManager() override;

		virtual void handleEvent(const sf::Event& event) override {}
		virtual void update(const float deltaTime) override;
	};
}
