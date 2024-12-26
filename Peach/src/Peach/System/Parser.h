#pragma once

#include "Peach/Core/Core.h"

#include <filesystem>
#include <fstream>

namespace Peach
{
	class PEACH_API Parser
	{
	protected:
		static bool open(const std::filesystem::path& filepath);

		static std::fstream& getFile();
		static bool isEOF();

		static bool find(std::string_view buff, std::string_view find);

		static bool isEnd(std::string_view buff);

		static std::string consumeLine();
		static float nextFloat(std::string_view buff);
		static int nextInt(std::string_view buff);
		static uint32_t nextUInt(std::string_view buff);

		static Vec2f stringToVec2f(std::string_view str);
		static Vec2i stringToVec2i(std::string_view str);
		static Vec2u stringToVec2u(std::string_view str);

		static std::vector<size_t> stringToVectorU(std::string_view str);
	private:
		Parser() {}
		~Parser() {}
	private:
		static inline std::fstream m_File;
	};
}
