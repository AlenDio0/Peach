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

		template<typename T>
		void addState(bool replacing = false)
		{
			m_Data->machine.addState(MakeRef<T>(m_Data), replacing);
		}
		void removeState();

		template<typename T>
		void loadAsset(const AssetKey& key, const std::string& path, bool force = true)
		{
			m_Data->assets.loadAsset<T>(key, path, force);
		}

		void run();
	protected:
		Ref<Data> m_Data;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
