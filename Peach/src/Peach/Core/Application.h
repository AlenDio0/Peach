#pragma once

#include "Core.h"

#include "AppData.h"
#include <memory>

namespace Peach
{
	class PEACH_API Application
	{
	public:
		Application();
		virtual ~Application();

		template<typename T>
		void addState(bool replacing = false) const { m_Data->machine.addState(MakeScope<T>(m_Data), replacing); }
		void removeState();

		const Scope<State>& getCurrentState() const;

		template<typename T>
		void loadAsset(const std::string& key, const std::string& path, bool force = true) const { m_Data->assets.loadAsset<T>(key, path, force); }
		void loadTexture(const std::string& key, const std::string& path, bool force = true) const;
		void loadFont(const std::string& key, const std::string& path, bool force = true) const;
		void loadSound(const std::string& key, const std::string& path, bool force = true) const;
		void initAssetFile();

		void run();
	protected:
		Ref<AppData> m_Data;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
