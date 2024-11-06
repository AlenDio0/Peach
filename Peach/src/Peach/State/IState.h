#pragma once

#include "Peach/Core/Core.h"

#include <string>

namespace Peach
{
	class PEACH_API IState
	{
	public:
		virtual ~IState() = default;

		virtual void onAdd() = 0;
		virtual void onRemove() = 0;
		virtual void onEvent() = 0;
		virtual void onUpdate() = 0;
		virtual void onRender() = 0;

		virtual const std::string& getName() const = 0;
	};
}
