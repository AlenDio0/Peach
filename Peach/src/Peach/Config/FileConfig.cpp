#include "peachpch.h"
#include "FileConfig.h"

#include <filesystem>

namespace Peach
{
	FileConfig::FileConfig(const std::string& name)
		: m_Name(name), m_File(name + ".ini")
	{
	}

	void FileConfig::validateFile()
	{
		bool exists = std::filesystem::exists(m_Name + ".ini");
		if (!exists)
		{
			generate();
		}
	}

	void FileConfig::setValue(const INIKey& key, const INIType& value)
	{
		const auto& keystr = getKeyToString(key);

		m_File.read(m_Structure);
		m_Structure[m_Name][keystr] = value;
		m_File.write(m_Structure);
	}
}