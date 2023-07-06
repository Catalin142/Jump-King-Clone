workspace "FrogTutorial"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "FrogTutorial"
	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLEW"] 	= "%{wks.location}/FrogTutorial/external/GLEW/include"
	IncludeDir["GLFW"] 	= "%{wks.location}/FrogTutorial/external/GLFW/include"
	IncludeDir["stb_image"] = "%{wks.location}/FrogTutorial/external/stb_image"

	group "Dependencies"
	include "FrogTutorial/external/GLEW"
	include "FrogTutorial/external/GLFW"
	group ""

	include "FrogTutorial"