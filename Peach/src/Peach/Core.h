#pragma once

#ifdef PEACH_PLATFORM_WINDOWS
#ifdef PEACH_BUILD_DLL
#define PEACH_API __declspec(dllexport)
#else
#define PEACH_API __declspec(dllimport)
#endif
#else
#error Peach only supports Windows
#endif

#define PEACH_ASSERT(x, ...) { if (!(x)) { PEACH_CORE_ERROR("Asserzione fallita: {}", __VA_ARGS__); } }
#define PEACH_RETURN_ASSERT(x, ...) { if (!(x)) { PEACH_CORE_ERROR("Asserzione fallita: {}", __VA_ARGS__); return false; } return true; }

template<typename T>
using Ref<T> = std::shared_ptr<T>;

template<typename T>
Ref<T> MakeRef()
{
    return std::make_shared<T>();}
