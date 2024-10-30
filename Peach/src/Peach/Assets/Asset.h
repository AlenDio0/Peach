#pragma once

#include "Peach/Core/Core.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>

namespace Peach
{
	class Asset
	{
	public:
		enum class Type
		{
			None = 0,
			Texture,
			Font,
			Sound
		};
	public:
		virtual bool load(const std::filesystem::path& path) = 0;

		static Type getType()
		{
			return Type::None;
		}
	};

	class Texture : public sf::Texture, public Asset
	{
	public:
		virtual bool load(const std::filesystem::path& path)
		{
			return loadFromFile(path.string());
		}

		static Type getType()
		{
			return Type::Texture;
		}
	};

	class Font : public sf::Font, public Asset
	{
	public:
		virtual bool load(const std::filesystem::path& path)
		{
			return loadFromFile(path.string());
		}

		static Type getType()
		{
			return Type::Font;
		}
	};

	class Sound : public sf::SoundBuffer, public Asset
	{
	public:
		virtual bool load(const std::filesystem::path& path)
		{
			return loadFromFile(path.string());
		}

		static Type getType()
		{
			return Type::Sound;
		}
	};
}
