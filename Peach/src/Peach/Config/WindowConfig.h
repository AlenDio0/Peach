#pragma once
#include "FileConfig.h"

namespace Peach
{
	class PEACH_API WindowConfig : public FileConfig
	{
	public:
		enum Key : INIKey
		{
			TITLE,
			WIDTH,
			HEIGHT,
			STYLE,
			VSYNC,
			FPSLIMIT
		};
	public:
		WindowConfig()
			: FileConfig("window")
		{
			validateFile();
		}

		virtual void generate()
		{
			setValue(TITLE, "PeachApp");
			setValue(WIDTH, "500");
			setValue(HEIGHT, "500");
			setValue(STYLE, "7");
			setValue(VSYNC, "1");
			setValue(FPSLIMIT, "120");
		}

		virtual std::string getKeyToString(const INIKey& key) const
		{
			switch (key)
			{
			case Key::TITLE:
				return "title";
			case Key::WIDTH:
				return "width";
			case Key::HEIGHT:
				return "height";
			case Key::STYLE:
				return "style";
			case Key::VSYNC:
				return "vsync";
			case Key::FPSLIMIT:
				return "fpslimit";
			default:
				return "";
			}
		}
	};
}
