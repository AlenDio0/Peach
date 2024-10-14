#pragma once

#include "Core.h"

#include "Peach/Log.h"

#include "Window.h"
#include "State/StateMachine.h"
#include "Assets/AssetManager.h"

namespace Peach
{
	struct Data
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
		AssetManager assets;
	};

	using DataRef = Data*;
}
