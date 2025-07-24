#pragma once

#ifdef _WIN32
#ifdef _WIN64
#define PEACH_PLATFORM_WINDOWS
#else
#error Peach doesn't support Win32
#endif // _WIN64
#endif // _WIN32

#ifdef PEACH_PLATFORM_WINDOWS
#ifdef PEACH_BUILD_DLL
#define PEACH_API __declspec(dllexport)
#else
#define PEACH_API __declspec(dllimport)
#endif // PEACH_BUILD_DLL
#else
#error Peach only supports Windows
#endif // PEACH_PLATFORM_WINDOWS

#include <string>

#define PEACH_EXPAND_MACRO(x) x
#define PEACH_STRINGIFY_MACRO(x) #x

#define PEACH_ASSERT_IMPL(type, x, msg, ...) { if(!(x)) { PEACH##type##ERROR(msg, __VA_ARGS__); __debugbreak(); } }
#define PEACH_ASSERT_MSG(type, x, ...) PEACH_ASSERT_IMPL(type, x, "Asserzione fallita: {}", __VA_ARGS__)
#define PEACH_ASSERT_NOMSG(type, x) PEACH_ASSERT_IMPL(type, x, "Asserzione '{}' fallita a '{}:{}'", PEACH_STRINGIFY_MACRO(x), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define PEACH_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define PEACH_ASSERT_GET_MACRO(...) PEACH_EXPAND_MACRO(PEACH_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PEACH_ASSERT_MSG, PEACH_ASSERT_NOMSG))

#define PEACH_CORE_ASSERT(...) PEACH_EXPAND_MACRO(PEACH_ASSERT_GET_MACRO(__VA_ARGS__)(_ ,__VA_ARGS__))
#define PEACH_ASSERT(...) PEACH_EXPAND_MACRO(PEACH_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))

#include <memory>

namespace Peach
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr Scope<T> MakeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
