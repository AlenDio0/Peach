project "Peach"
	kind "SharedLib"
	language "C++"
    cppdialect "C++17"
	staticruntime "Off"

	targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
	objdir ("../bin-int/" .. output_dir .. "/%{prj.name}")

	pchheader "peachpch.h"
	pchsource "src/peachpch.cpp"

	flags
	{
		"MultiProcessorCompile"
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
        "src",

        "../%{IncludeDir.SFML}",
        "../%{IncludeDir.spdlog}",
        "../%{IncludeDir.mINI}",
	}

	libdirs
	{
        "../%{LibraryDir.SFML}"
	}

	links
    {
        Library["SFML"]["Global"]
    }

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PEACH_PLATFORM_WINDOWS",
			"PEACH_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. output_dir .. "/Demo/\"")
		}

	filter "configurations:Debug"
		defines "PEACH_DEBUG"
		runtime "Debug"
		symbols "On"
		libdirs "../%{LibraryDir.SFML}/Debug"
		links { Library["SFML"]["Debug"] }

	filter "configurations:Release"
		defines "PEACH_RELEASE"
		runtime "Release"
		optimize "Off"
		libdirs "../%{LibraryDir.SFML}/Release"
		links { Library["SFML"]["Release"] }

	filter "configurations:Dist"
		defines "PEACH_DIST"
		runtime "Release"
		optimize "Off"
		libdirs "../%{LibraryDir.SFML}/Release"
		links { Library["SFML"]["Dist"] }
