#pragma once

#include "Peach/Core/Core.h"

#include <filesystem>
#include <fstream>

namespace Peach
{
	class PEACH_API Parser
	{
	protected:
		static bool open(const std::filesystem::path& filePath);

		static std::fstream& getFile();
		static bool isEOF();

		static bool find(const std::string_view buff, const std::string_view find);

		static bool isEnd(const std::string_view buff);

		static std::string consumeLine();
		static float nextFloat(const std::string_view buff);
		static int nextInt(const std::string_view buff);
		static uint32_t nextUInt(const std::string_view buff);

		static Vec2f stringToVec2f(const std::string_view str);
		static Vec2i stringToVec2i(const std::string_view str);
		static Vec2u stringToVec2u(const std::string_view str);

		static std::vector<size_t> stringToVectorU(const std::string_view str);
	private:
		Parser() {}
		~Parser() {}
	private:
		static inline std::fstream m_File;
	};
}
