#pragma once

#include "Core.h"

#include "Log.h"
#include "Window.h"
#include "Peach/State/StateMachine.h"
#include "Peach/Assets/AssetManager.h"

namespace Peach
{
	struct AppData
	{
		AppData()
		{
			PEACH_CORE_TRACE("AppData inizializzato");
		}

		virtual ~AppData()
		{
			PEACH_CORE_TRACE("AppData distrutto");
		}

		Window window;
		StateMachine machine;
		AssetManager assets;
	};
}
