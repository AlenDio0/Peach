#pragma once

#include "FileConfig.h"

namespace Peach
{
	using Key = std::string;

	class PEACH_API AssetConfig : public FileConfig<Key>
	{
	public:
		AssetConfig()
			: FileConfig("assets")
		{
			validateFile();
		}

		std::string getTexture(const Key& key)
		{
			return getValue<std::string>("texture", key);
		}
		std::string getFont(const Key& key)
		{
			return getValue<std::string>("font", key);
		}
		std::string getSound(const Key& key)
		{
			return getValue<std::string>("sound", key);
		}

		virtual void generate()
		{
			setValue("texture", "", "");
			setValue("font", "", "");
			setValue("sound", "", "");
		}

		virtual std::string getKeyToString(const Key& key) const
		{
			return key;
		}
	};
}
