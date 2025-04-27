#pragma once

#include "Core.h"

#include "Log.h"
#include "Window.h"
#include "Peach/State/StateMachine.h"
#include "Peach/Assets/AssetManager.h"

namespace Peach
{
	struct Data
	{
		Data()
		{
			PEACH_CORE_TRACE("Data inizializzato");
		}

		~Data()
		{
			PEACH_CORE_TRACE("Data distrutto");
		}

		Window window;
		StateMachine machine;
		AssetManager assets;
	};
}
