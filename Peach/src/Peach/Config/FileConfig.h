#pragma once

#include "Peach/Core/Core.h"

#include <mini/ini.h>
#include <filesystem>
#include <sstream>

namespace Peach
{
	template<typename TKey>
	class PEACH_API FileConfig
	{
	public:
		FileConfig(std::string name)
			: m_Name(name), m_File(name + ".ini")
		{
		}

		void validateFile()
		{
			bool exists = std::filesystem::exists(m_Name + ".ini");
			if (!exists)
			{
				generate();
			}
		}
		virtual void generate() = 0;

		const mINI::INIStructure& getStructure()
		{
			m_File.read(m_Structure);
			return m_Structure;
		}

		template<typename T>
		T getValue(std::string section, const TKey& key) const
		{
			const auto& keystr = getKeyToString(key);

			m_File.read(m_Structure);
			std::stringstream ss(m_Structure[section][keystr]);
			T value;
			if (!(ss >> value))
			{
				throw "Impossibile convertire stringa a T";
			}

			return value;
		}
		template<typename T>
		T getValue(const TKey& key) const
		{
			return getValue<T>(m_Name, key);
		}

		void setValue(std::string_view section, const TKey& key, std::string_view value)
		{
			const auto& keystr = getKeyToString(key);

			m_File.read(m_Structure);
			m_Structure[section][keystr] = value;
			m_File.write(m_Structure);
		}
		template<typename T>
		void setValue(std::string_view section, const TKey& key, const T& value)
		{
			std::stringstream ss;
			ss << value;
			setValue(section, key, ss.str());
		}
		template<typename T>
		void setValue(const TKey& key, const T& value)
		{
			setValue<T>(m_Name, key, value);
		}

		virtual std::string getKeyToString(const TKey& key) const = 0;
	protected:
		mINI::INIFile m_File;
		mutable mINI::INIStructure m_Structure;
	private:
		std::string m_Name;
	};
}
