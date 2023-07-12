workspace "untitled_frog_game"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "untitled_frog_game"
	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLEW"] 	= "%{wks.location}/untitled_frog_game/external/GLEW/include"
	IncludeDir["GLFW"] 	= "%{wks.location}/untitled_frog_game/external/GLFW/include"
	IncludeDir["stb_image"] = "%{wks.location}/untitled_frog_game/external/stb_image"

	group "Dependencies"
	include "untitled_frog_game/external/GLEW"
	include "untitled_frog_game/external/GLFW"
	group ""

	include "untitled_frog_game"