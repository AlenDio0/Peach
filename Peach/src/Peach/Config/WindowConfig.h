#pragma once

#include "FileConfig.h"

namespace Peach
{
	using WKey = uint8_t;

	class PEACH_API WindowConfig : public FileConfig<WKey>
	{
	public:
		enum Key : WKey
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

		virtual void generate() override
		{
			setValue(TITLE, "PeachApp");
			setValue(WIDTH, 500);
			setValue(HEIGHT, 500);
			setValue(STYLE, 7);
			setValue(VSYNC, true);
			setValue(FPSLIMIT, 120);
		}

		virtual std::string getKeyToString(const WKey& key) const override
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
