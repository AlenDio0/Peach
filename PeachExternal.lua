IncludeDir = {}
IncludeDir["SFML"] = "Peach/vendor/SFML/include"
IncludeDir["spdlog"] = "Peach/vendor/spdlog/include"
IncludeDir["mINI"] = "Peach/vendor/mINI/src"

LibraryDir = {}
LibraryDir["SFML"] = "Peach/vendor/SFML/lib"

Library = {}
Library["SFML"] = {}
Library["SFML"]["Global"] =
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
Library["SFML"]["Debug"] =
{
	"sfml-audio-d.lib",
	"sfml-graphics-d.lib",
	"sfml-network-d.lib",
	"sfml-system-d.lib",
	"sfml-window-d.lib"
}
Library["SFML"]["Release"] =
{
	"sfml-audio.lib",
	"sfml-graphics.lib",
	"sfml-network.lib",
	"sfml-system.lib",
	"sfml-window.lib"
}
Library["SFML"]["Dist"] =
{
	"sfml-main.lib",
	Library["SFML"]["Release"]
}


group "Core"
include "Peach"
group ""
