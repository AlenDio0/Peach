#pragma once

#include "Peach/Core.h"

#include <mini/ini.h>
#include <sstream>

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

		template<typename T>
		T getValue(const INIType& section, const INIKey& key) const
		{
			const auto& keystr = getKeyToString(key);

			m_File.read(m_Structure);
			INIType strvalue = m_Structure[section][keystr];
			std::stringstream ss(strvalue);
			T value;
			if (!(ss >> value))
			{
				throw "Impossibile convertire stringa a T";
			}

			return value;
		}
		template<typename T>
		T getValue(const INIKey& key) const
		{
			return getValue<T>(m_Name, key)
		}

		void setValue(const INIType& section, const INIKey& key, const INIType& value);
		template<typename T>
		void setValue(const INIType& section, const INIKey& key, const T& value)
		{
			std::stringstream ss;
			ss << value;
			setValue(section, key, ss.str());
		}
		template<typename T>
		void setValue(const INIKey& key, const T& value)
		{
			setValue<T>(m_Name, key, ss.str());
		}

		virtual std::string getKeyToString(const INIKey& key) const = 0;
	protected:
		mINI::INIFile m_File;
		mutable mINI::INIStructure m_Structure;
	private:
		std::string m_Name;
	};
}
