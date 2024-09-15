#pragma once

#include "Peach/Core.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Peach
{
	enum class AssetType
	{
		None = -1,
		Texture,
		Font,
		Sound
	};

	class Asset
	{
	public:
		Asset(const std::string& path)
		{
			m_Path = path;
		}

		virtual AssetType getType() const
		{
			return AssetType::None;
		}

		const std::string& getPath() const
		{
			return m_Path;
		}

	private:
		std::string m_Path;
	};

	class Texture : public sf::Texture, public Asset
	{
	public:
		Texture(const std::string& path)
			: Asset(path)
		{
			loadFromFile(path);
		}

		static AssetType getStaticType()
		{
			return AssetType::Texture;
		}

		AssetType getType() const
		{
			return getStaticType();
		}
	};

	class Font : public sf::Font, public Asset
	{
	public:
		Font(const std::string& path)
			: Asset(path)
		{
			loadFromFile(path);
		}

		static AssetType getStaticType()
		{
			return AssetType::Font;
		}

		AssetType getType() const
		{
			return getStaticType();
		}
	};

	class Sound : public sf::SoundBuffer, public Asset
	{
	public:
		Sound(const std::string& path)
			: Asset(path)
		{
			loadFromFile(path);
		}

		static AssetType getStaticType()
		{
			return AssetType::Sound;
		}

		AssetType getType() const
		{
			return getStaticType();
		}
	};
}
