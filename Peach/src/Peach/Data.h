#pragma once

#include "Core.h"

#include "Peach/Log.h"

#include "Window.h"
#include "StateMachine.h"

namespace Peach
{
	struct PEACH_API Data
	{
		Data()
		{
			PEACH_CORE_INFO("Data inizializzato");
		}

		~Data()
		{
			PEACH_CORE_INFO("Data distrutto");
		}

		Window window;
		StateMachine machine;
	};

	using DataRef = Data*;
}
