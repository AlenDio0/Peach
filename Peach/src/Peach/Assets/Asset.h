#pragma once

#include "Peach/Core/Core.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Peach
{
	struct Asset
	{
		virtual bool load(const std::string& path) = 0;
	};

	struct Texture : public sf::Texture, public Asset
	{
		virtual bool load(const std::string& path) override { return loadFromFile(path); }
	};

	struct Font : public sf::Font, public Asset
	{
		virtual bool load(const std::string& path) override { return loadFromFile(path); }
	};

	struct Sound : public sf::SoundBuffer, public Asset
	{
		virtual bool load(const std::string& path) override { return loadFromFile(path); }
	};
}
