workspace "Peach"
	architecture "x64"
	startproject "Demo"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

local output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = 
{
	"Peach/src",
	"Peach/vendor/spdlog/include",
	"Peach/vendor/SFML/include",
	"Peach/vendor/mINI/include"
}

SFML_Links = {}
SFML_Links["Global"] =
{
	"opengl32.lib",
	"freetype.lib",
	"winmm.lib",
	"gdi32.lib",
	"openal32.lib",
	"flac.lib",
	"vorbisenc.lib",
	"vorbisfile.lib",
	"vorbis.lib",
	"ogg.lib",
	"ws2_32.lib"
}
SFML_Links["Debug"] =
{
	"sfml-audio-d.lib",
	"sfml-graphics-d.lib",
	"sfml-network-d.lib",
	"sfml-system-d.lib",
	"sfml-window-d.lib"
}
SFML_Links["Release"] =
{
	"sfml-audio.lib",
	"sfml-graphics.lib",
	"sfml-network.lib",
	"sfml-system.lib",
	"sfml-window.lib"
}
SFML_Links["Dist"] =
{
	"sfml-main.lib",
	SFML_Links["Release"]
}

project "Peach"
	location "Peach"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin-int/" .. output_dir .. "/%{prj.name}")

	pchheader "peachpch.h"
	pchsource "Peach/src/peachpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		IncludeDirs
	}

	libdirs
	{
		"%{prj.name}/vendor/SFML/lib"
	}

	links { SFML_Links["Global"] }

	filter "system:windows"
		cppdialect "C++17"
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
		libdirs "Peach/vendor/SFML/lib/Debug"
		links { SFML_Links["Debug"] }

	filter "configurations:Release"
		defines "PEACH_RELEASE"
		runtime "Release"
		optimize "Off"
		libdirs "Peach/vendor/SFML/lib/Release"
		links { SFML_Links["Release"] }

	filter "configurations:Dist"
		defines "PEACH_DIST"
		runtime "Release"
		optimize "Off"
		libdirs "Peach/vendor/SFML/lib/Release"
		links { SFML_Links["Dist"] }

project "Demo"
	location "Demo"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin-int/" .. output_dir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		IncludeDirs
	}
	
	libdirs
	{
		"Peach/vendor/SFML/lib"
	}

	links
	{
		"Peach",
		SFML_Links["Global"]
	}

	local sfml_bin_dir = "../Peach/vendor/SFML/bin/"

	SFML_BinCopy = {}
	SFML_BinCopy["Debug"] =
	{
		("{COPY} " .. sfml_bin_dir .. "openal32.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-audio-d-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-graphics-d-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-network-d-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-system-d-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-window-d-2.dll \"../bin/" .. output_dir .. "/Demo/\"")
	}
	SFML_BinCopy["Release"] =
	{
		("{COPY} " .. sfml_bin_dir .. "openal32.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-audio-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-graphics-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-network-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-system-2.dll \"../bin/" .. output_dir .. "/Demo/\""),
		("{COPY} " .. sfml_bin_dir .. "sfml-window-2.dll \"../bin/" .. output_dir .. "/Demo/\"")
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PEACH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PEACH_DEBUG"
		runtime "Debug"
		symbols "On"
		libdirs "Peach/vendor/SFML/lib/Debug"
		links { SFML_Links["Debug"] }
		postbuildcommands { SFML_BinCopy["Debug"] }

	filter "configurations:Release"
		defines "PEACH_RELEASE"
		runtime "Release"
		optimize "Off"
		libdirs "Peach/vendor/SFML/lib/Release"
		links { SFML_Links["Release"] }
		postbuildcommands { SFML_BinCopy["Release"] }

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "PEACH_DIST"
		runtime "Release"
		optimize "Off"
		libdirs "Peach/vendor/SFML/lib/Release"
		links { SFML_Links["Dist"] }
		postbuildcommands { SFML_BinCopy["Release"] }
