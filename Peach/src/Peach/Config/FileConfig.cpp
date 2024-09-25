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
		if (!isGood())
		{
			generate();
		}
	}

	const bool& FileConfig::isGood() const
	{
		return std::filesystem::exists(m_Name + ".ini");
	}

	INIType FileConfig::operator[](const INIKey& key) const
	{
		return getValue(key);
	}

	INIType FileConfig::getValue(const INIKey& key) const
	{
		m_File.read(m_Structure);
		return m_Structure[m_Name][getKeyToString(key)];
	}

	void FileConfig::setValue(const INIKey& key, const INIType& value)
	{
		m_File.read(m_Structure);
		m_Structure[m_Name][getKeyToString(key)] = value;
		m_File.write(m_Structure);
	}
}