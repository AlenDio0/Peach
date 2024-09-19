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
		virtual bool load(const std::string& path) = 0;

		virtual AssetType getType() const
		{
			return AssetType::None;
		}
	};

	class Texture : public sf::Texture, public Asset
	{
	public:
		virtual bool load(const std::string& path)
		{
			return loadFromFile(path);
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
		virtual bool load(const std::string& path)
		{
			return loadFromFile(path);
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
		virtual bool load(const std::string& path)
		{
			return loadFromFile(path);
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
