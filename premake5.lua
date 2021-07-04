workspace "FoxEngine"
	architecture "x64"
	startproject "Game"

	configurations{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "FoxEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "FoxEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "FoxEngine/vendor/imgui"
include("FoxEngine/vendor/GLFW")
include("FoxEngine/vendor/GLAD")
include("FoxEngine/vendor/imgui")


project "FoxEngine"
	location "FoxEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin/int/"..outputdir.."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	pchheader "fepch.h"
	pchsource "FoxEngine/src/fepch.cpp"
	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
	}
	
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib",
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"FOX_PLATFORM_WINDOWS",
			"FOX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir .. "/Game")
		}



	filter "configurations:Debug"
		defines "FOX_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "FOX_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "FOX_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin/int/"..outputdir.."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"FoxEngine/vendor/spdlog/include",
		"FoxEngine/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	
	links{
		"FoxEngine"
	}

	defines {
		"FOX_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "FOX_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "FOX_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "FOX_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"