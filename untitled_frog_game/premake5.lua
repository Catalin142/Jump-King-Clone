project "untitled_frog_game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"%{wks.location}/untitled_frog_game/src",
		"%{wks.location}/untitled_frog_game/external",
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
		"external/stb_image/**.h",
		"external/stb_image/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLEW_STATIC",
	}

	includedirs
	{
		"external;",
		"src;",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.stb_image}",
	}

	links 
	{
		"GLFW",
		"GLEW",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG=1"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE=1"
		runtime "Release"
		optimize "on"