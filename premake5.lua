workspace "Peach"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Demo"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "PeachExternal.lua"
include "Demo"
