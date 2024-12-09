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

		static bool find(const std::string& buff, const std::string& find);

		static bool isEnd(const std::string& buff);

		static std::string consumeLine();
		static float nextFloat(const std::string& buff);
		static int nextInt(const std::string& buff);
		static uint32_t nextUInt(const std::string& buff);

		static Vec2f stringToVec2f(const std::string& str);
		static Vec2i stringToVec2i(const std::string& str);
		static Vec2u stringToVec2u(const std::string& str);

		static std::vector<size_t> stringToVectorU(const std::string& str);
	private:
		Parser() {}
		~Parser() {}
	private:
		static inline std::fstream m_File;
	};
}
