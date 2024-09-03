#pragma once

#include "Core.h"
#include "Data.h"

#include <memory>

namespace Peach
{
	class PEACH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void addState(IStateRef newState, bool isReplacing);
		void removeState();

		void run();
	protected:
		DataRef m_Data = new Data();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
