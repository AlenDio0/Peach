#pragma once

#include "Asset.h"
#include "Peach/Config/AssetConfig.h"

namespace Peach
{
	using AssetKey = std::string;
	using AssetMap = std::unordered_map<AssetKey, Ref<Asset>>;

	class AssetManager
	{
	public:
		AssetManager()
			: m_Config(NULL)
		{
			PEACH_CORE_TRACE("AssetManager costruito");
		}

		~AssetManager()
		{
			PEACH_CORE_TRACE("AssetManager distrutto");

			m_Assets.clear();
			delete m_Config;
		}

		void initFile()
		{
			if (m_Config)
			{
				return;
			}
			m_Config = new AssetConfig();

			for (const auto& [section, map] : m_Config->getStructure())
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
		void loadAsset(AssetKey key, const std::filesystem::path& path, bool force = true)
		{
			for (auto& c : key)
			{
				if (c >= 'A' && c <= 'Z')
				{
					c += 32;
				}
			}

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
				throw std::exception("Asset non ha un AssetType definito");
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
		const T* getAsset(AssetKey key)
		{
			for (auto& c : key)
			{
				if (c >= 'A' && c <= 'Z')
				{
					c += 32;
				}
			}

			try
			{
				return static_cast<T*>(m_Assets.at(key).get());
			}
			catch (const std::exception& e)
			{
				PEACH_CORE_ERROR("AssetManager::(key: {}), Catturata eccezione: {}", key, e.what());
				return NULL;
			}
		}
	private:
		AssetMap m_Assets;
		AssetConfig* m_Config;
	};
}
