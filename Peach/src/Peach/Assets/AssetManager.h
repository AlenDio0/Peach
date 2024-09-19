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
		void loadAsset(const uint32_t& key, const std::string& path)
		{
			if (m_Assets[key])
			{
				if (m_Assets[key]->getPath() == path)
				{
					PEACH_CORE_INFO("AssetManager::loadAsset(key: {}, path: {}) non sostituira' l'Asset (path uguale)", key, path);
					return;
				}
				else
				{
					PEACH_CORE_WARN("AssetManager::loadAsset(key: {}, path: {}) sostituira' l'Asset \"{}\"", key, path, m_Assets[key]->getPath());
				}
			}

			switch (T::getStaticType())
			{
			case AssetType::Texture:
				m_Assets[key] = AssetRef(new Texture(path));
				break;
			case AssetType::Font:
				m_Assets[key] = AssetRef(new Font(path));
				break;
			case AssetType::Sound:
				m_Assets[key] = AssetRef(new Sound(path));
				break;
			default:
				PEACH_CORE_ERROR("AssetManager::loadAsset(key: {}, path: {}) c'e' stato un erorre nel caricamento", key, path);
				return;
			}

			PEACH_CORE_TRACE("AssetManager::loadAsset(key: {}, path: {}) caricato correttamente", key, path);
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
