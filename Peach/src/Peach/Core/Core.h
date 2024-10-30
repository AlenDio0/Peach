#pragma once

#ifdef PEACH_PLATFORM_WINDOWS
#ifdef PEACH_BUILD_DLL
#define PEACH_API __declspec(dllexport)
#else
#define PEACH_API __declspec(dllimport)
#endif // PEACH_BUILD_DLL
#else
#ifdef PEACH_PLATFORM_LINUX || PEACH_PLATFORM_MACOS
#ifdef PEACH_BUILD_DLL
#define PEACH_API __attribute__((visibility("default")))
#else
#define PEACH_API
#endif // PEACH_BUILD_DLL
#else
#error Peach only supports Windows, Linux and macOS
#endif // PEACH_PLATFORM_WINDOWS
#endif // PEACH_PLATFORM_LINUX || PEACH_PLATFORM_MACOS

#define PEACH_ASSERT(x, ...) { if (!(x)) { PEACH_CORE_ERROR("Asserzione fallita: {}", __VA_ARGS__); } }
#define PEACH_RETURN_ASSERT(x, ...) { if (!(x)) { PEACH_CORE_ERROR("Asserzione fallita: {}", __VA_ARGS__); return false; } return true; }

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
