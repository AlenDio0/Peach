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
		T getValue(const INIKey& key) const
		{
			const auto& keystr = getKeyToString(key);

			m_File.read(m_Structure);
			INIType strvalue = m_Structure[m_Name][keystr];
			std::stringstream ss(strvalue);
			T value;
			if (!(ss >> value))
			{
				throw "Impossibile convertire stringa a T";
			}

			return value;
		}

		void setValue(const INIKey& key, const INIType& value);
		template<typename T>
		void setValue(const INIKey& key, const T& value)
		{
			std::stringstream ss;
			ss << value;
			setValue(key, ss.str());
		}

		virtual std::string getKeyToString(const INIKey& key) const = 0;
	protected:
		mINI::INIFile m_File;
		mutable mINI::INIStructure m_Structure;
	private:
		std::string m_Name;
	};
}
