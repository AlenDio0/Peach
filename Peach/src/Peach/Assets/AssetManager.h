#pragma once

#include "Peach/Core.h"

#include "Asset.h"

namespace Peach
{
	using AssetKey = std::string;
	using AssetMap = std::unordered_map<AssetKey, Ref<Asset>>;

	class AssetManager
	{
	public:
		AssetManager()
		{
			PEACH_CORE_TRACE("AssetManager costruito");
		}

		~AssetManager()
		{
			PEACH_CORE_TRACE("AssetManager distrutto");
		}

		template<typename T>
		void loadAsset(const AssetKey& key, const std::filesystem::path& path, bool force = true)
		{
			PEACH_CORE_TRACE("AssetManager::loadAsset(key: {}, path: {}, force: {})", key, path.string(), force);
			if (m_Assets[key])
			{
				if (force)
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Verra' rimpiazzato l'Asset precedente", key, path.string());
				}
				else
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Impossibile caricare Asset, rimpiazzo non forzato", key, path.string());
					return;
				}
			}

			if (T::getType() == Asset::Type::None)
			{
				throw "AssetType non definito";
			}

			m_Assets[key] = Ref<Asset>(new T());

			if (m_Assets[key]->load(path))
			{
				PEACH_CORE_INFO("AssetManager::loadAsset(key: {}, path: {}), Caricato Asset con successo", key, path.string());
			}
			else
			{
				PEACH_CORE_ERROR("AssetManager::loadAsset(key: {}, path: {}), Caricamento Asset fallito", key, path.string());
			}
		}

		template<typename T>
		T& getAsset(const AssetKey& key)
		{
			return *static_cast<T*>(m_Assets[key].get());
		}
	private:
		AssetMap m_Assets;
	};
}
