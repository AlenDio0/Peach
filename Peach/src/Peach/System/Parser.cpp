#include "peachpch.h"
#include "Parser.h"

namespace Peach
{
	bool Parser::open(const std::filesystem::path& filePath)
	{
		if (m_File.is_open())
		{
			m_File.close();
		}

		m_File.open(filePath, std::ios::in);
		return m_File.is_open();
	}

	std::fstream& Parser::getFile()
	{
		return m_File;
	}

	bool Parser::isEOF()
	{
		return m_File.eof();
	}

	bool Parser::find(const std::string_view buff, const std::string_view find)
	{
		return buff.find(find) != std::string::npos;
	}

	bool Parser::isEnd(const std::string_view buff)
	{
		return buff == "END";
	}

	std::string Parser::consumeLine()
	{
		std::string out;
		std::getline(m_File, out);
		return out;
	}

	float Parser::nextFloat(const std::string_view buff)
	{
		bool first = true;
		bool in = false;
		bool afterpoint = false;
		std::string num;

		for (const char& c : buff)
		{
			if (first && (c == '-' || c == '+'))
			{
				in = true;
			}
			else if (isdigit(c))
			{
				in = true;
				first = false;
			}
			else if (c == '.' && !afterpoint && in)
			{
				afterpoint = true;
			}
			else if (in)
			{
				break;
			}
			else
			{
				continue;
			}

			num += c;
		}

		return stof(num);
	}

	int Parser::nextInt(const std::string_view buff)
	{
		return (int)nextFloat(buff);
	}

	uint32_t Parser::nextUInt(const std::string_view buff)
	{
		return (uint32_t)std::abs(nextInt(buff));
	}

	Vec2f Parser::stringToVec2f(const std::string_view str)
	{
		long long in_x = -1, in_y = -1;

		size_t i = -1;
		for (const char& c : str)
		{
			i++;
			if (c == '[')
			{
				in_x = i;
				continue;
			}

			if (in_x == -1 && in_y == -1)
			{
				continue;
			}

			if (c == ',')
			{
				in_y = i;
				break;
			}
		}

		Vec2f out;
		out.x = nextFloat(str.substr(in_x));
		out.y = nextFloat(str.substr(in_y));

		return out;
	}

	Vec2i Parser::stringToVec2i(const std::string_view str)
	{
		return (Vec2i)stringToVec2f(str);
	}

	Vec2u Parser::stringToVec2u(const std::string_view str)
	{
		Vec2i out = stringToVec2i(str);
		out.x = std::abs(out.x);
		out.y = std::abs(out.y);
		return (Vec2u)out;
	}
	std::vector<size_t> Parser::stringToVectorU(const std::string_view str)
	{
		std::vector<size_t> out;
		bool in = false;
		bool next = false;

		size_t i = -1;
		for (const char& c : str)
		{
			i++;
			if (!in)
			{
				if (c == '[')
				{
					next = true;
					in = true;
				}
				continue;
			}
			if (c == ']')
			{
				break;
			}
			if (c == ',')
			{
				next = true;
				continue;
			}
			if (!next)
			{
				continue;
			}

			next = false;
			std::string_view sub(str.data() + i, str.size() - i);
			out.push_back(nextUInt(sub));
		}
		return out;
	}
}
