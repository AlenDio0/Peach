#pragma once

#include "Asset.h"
#include "Peach/Config/AssetConfig.h"

namespace Peach
{
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

			PEACH_CORE_TRACE("[AssetManager] {} Assets distrutti", m_Assets.size());
			m_Assets.clear();
		}

		void initFile()
		{
			AssetConfig config;

			for (const auto& [section, map] : config.getStructure())
			{
				for (const auto& [key, path] : map)
				{
					if (path.empty())
					{
						continue;
					}

					if (section == "texture")
					{
						loadAsset<Texture>(key, path, true);
					}
					else if (section == "font")
					{
						loadAsset<Font>(key, path, true);
					}
					else if (section == "sound")
					{
						loadAsset<Sound>(key, path, true);
					}
				}
			}
		}

		template<typename T>
		void loadAsset(std::string key, const std::string& path, bool force = true)
		{
			for (auto& c : key)
			{
				c = tolower(c);
			}

			PEACH_CORE_TRACE("AssetManager::loadAsset(key: {}, path: {}, force: {})", key, path, force);
			if (m_Assets.find(key) != m_Assets.end())
			{
				if (!force)
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Impossibile caricare Asset, rimpiazzo non forzato", key, path);
					return;
				}

				PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Verra' rimpiazzato l'Asset precedente", key, path);
			}

			if (!std::is_base_of<Asset, T>())
			{
				PEACH_CORE_ERROR("AssetManager::loadAsset(key: {}, path: {}), Impossibile creare un non derivato Asset", key, path);
				return;
			}

			m_Assets[key] = MakeRef<T>();
			if (!m_Assets[key]->load(path))
			{
				PEACH_CORE_ERROR("AssetManager::loadAsset(key: {}, path: {}), Caricamento Asset fallito", key, path);
				return;
			}

			PEACH_CORE_INFO("AssetManager::loadAsset(key: {}, path: {}), Caricato Asset con successo", key, path);
		}

		template<typename T>
		Ref<T> getAsset(std::string key)
		{
			for (auto& c : key)
			{
				c = tolower(c);
			}

			if (m_Assets.find(key) == m_Assets.end())
			{
				PEACH_CORE_ERROR("AssetManager::getAsset(key: {}), Ritornato valore nullo. Asset con key non trovata", key);
				return nullptr;
			}

			if (auto asset = std::dynamic_pointer_cast<T>(m_Assets.at(key)))
			{
				return asset;
			}

			PEACH_CORE_ERROR("AssetManager::getAsset(key: {}), Ritornato valore nullo. Asset non coincide con il tipo", key);
			return nullptr;

		}
	private:
		std::unordered_map<std::string, Ref<Asset>> m_Assets;
	};
}
