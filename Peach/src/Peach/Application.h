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

		void run();
	protected:
		Ref<Data> m_Data;
	protected:
		void addState(Ref<IState> newstate, bool replacing);
		void removeState();

		template<typename T>
		void loadAsset(const AssetKey& key, const std::string& path, bool force = true)
		{
			m_Data->assets.loadAsset(key, path, force);
		}
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
