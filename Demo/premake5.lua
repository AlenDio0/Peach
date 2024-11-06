project "Demo"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"
	staticruntime "Off"

	targetdir ("../bin/" .. output_dir .. "/%{prj.name}")
	objdir ("../bin-int/" .. output_dir .. "/%{prj.name}")

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
		"../Peach/src",
        
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
		"Peach",
		Library["SFML"]["Global"]
	}

	local sfml_copyinput = "{COPY} ../Peach/vendor/SFML/bin/"
	local sfml_output = " \"../bin/" .. output_dir .. "/%{prj.name}/\""

	PostBuildSFML = {}
	PostBuildSFML["Debug"] =
	{
		(sfml_copyinput .. "openal32.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-audio-d-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-graphics-d-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-network-d-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-system-d-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-window-d-2.dll" .. sfml_output)
	}
	PostBuildSFML["Release"] =
	{
		(sfml_copyinput .. "openal32.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-audio-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-graphics-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-network-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-system-2.dll" .. sfml_output),
		(sfml_copyinput .. "sfml-window-2.dll" .. sfml_output)
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PEACH_DEBUG"
		runtime "Debug"
		symbols "On"
		libdirs "../%{LibraryDir.SFML}/Debug"
		links { Library["SFML"]["Debug"] }
		postbuildcommands { PostBuildSFML["Debug"] }

	filter "configurations:Release"
		defines "PEACH_RELEASE"
		runtime "Release"
		optimize "Off"
		libdirs "../%{LibraryDir.SFML}/Release"
		links { Library["SFML"]["Release"] }
		postbuildcommands { PostBuildSFML["Release"] }

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "PEACH_DIST"
		runtime "Release"
		optimize "Off"
		libdirs "../%{LibraryDir.SFML}/Release"
		links { Library["SFML"]["Dist"] }
		postbuildcommands { PostBuildSFML["Release"] }
