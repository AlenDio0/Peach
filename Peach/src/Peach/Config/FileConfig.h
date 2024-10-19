#pragma once

#include "Peach/Core.h"

#include <mini/ini.h>

namespace Peach
{
	using INIKey = uint8_t;
	using INIType = std::string;

	class PEACH_API FileConfig
	{
	public:
		FileConfig(const std::string& name);
		virtual ~FileConfig() = default;

		void validateFile();
		virtual void generate() = 0;

		INIType operator[](const INIKey& key) const;
		INIType getValue(const INIKey& key) const;

		void setValue(const INIKey& key, const INIType& value);

		virtual std::string getKeyToString(const INIKey& key) const = 0;
	protected:
		mINI::INIFile m_File;
		mutable mINI::INIStructure m_Structure;
	private:
		std::string m_Name;
	};
}
