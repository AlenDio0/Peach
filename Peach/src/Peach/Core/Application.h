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
		void addState(bool replacing = false) const { m_Data->machine.addState(MakeRef<T>(m_Data), replacing); }
		void removeState();

		Ref<State> getCurrentState() const;

		template<typename T>
		void loadAsset(const AssetKey& key, const std::string& path, bool force = true) const { m_Data->assets.loadAsset<T>(key, path, force); }
		void loadTexture(const AssetKey& key, const std::string& path, bool force = true) const;
		void loadFont(const AssetKey& key, const std::string& path, bool force = true) const;
		void loadSound(const AssetKey& key, const std::string& path, bool force = true) const;
		void initAssetFile();

		void run();
	protected:
		Ref<Data> m_Data;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
