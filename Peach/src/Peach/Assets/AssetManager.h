#pragma once

#include "Peach/Core.h"

#include "Asset.h"

namespace Peach
{
	using AssetRef = std::shared_ptr<Asset>;
	using AssetMap = std::unordered_map<uint32_t, AssetRef>;

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
		void loadAsset(const uint32_t& key, const std::string& path, bool force = true)
		{
			PEACH_CORE_TRACE("AssetManager::loadAsset(key: {}, path: {}, force: {})", key, path, force);
			if (m_Assets[key])
			{
				if (force)
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Verra' rimpiazzato l'Asset precedente", key, path);
				}
				else
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}), Impossibile caricare Asset, rimpiazzo non forzato", key, path);
					return;
				}
			}

			switch (T::getStaticType())
			{
			case AssetType::Texture:
				m_Assets[key] = AssetRef(new Texture());
				break;
			case AssetType::Font:
				m_Assets[key] = AssetRef(new Font());
				break;
			case AssetType::Sound:
				m_Assets[key] = AssetRef(new Sound());
				break;
			default:
				throw "Inserita classe Asset non valida";
				return;
			}

			if (m_Assets[key]->load(path))
			{
				PEACH_CORE_INFO("AssetManager::loadAsset(key: {}, path: {}), Caricato Asset con successo", key, path);
			}
			else
			{
				PEACH_CORE_ERROR("AssetManager::loadAsset(key: {}, path: {}), Caricamento Asset fallito", key, path);
			}
		}

		template<typename T>
		T* getAsset(const uint32_t& key)
		{
			return static_cast<T*>(m_Assets[key].get());
		}
	private:
		AssetMap m_Assets;
	};
}
