#pragma once

#include "Peach/Core/Core.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API State
	{
	public:
		virtual ~State() = default;

		virtual void onAdd() = 0;
		virtual void onRemove() = 0;
		virtual void onEvent(sf::Event event) = 0;
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onRender() = 0;

		virtual const std::string& getName() const = 0;
	};
}
