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
IncludeDir["glm"] = "FoxEngine/vendor/glm"
IncludeDir["stb_image"] = "FoxEngine/vendor/stb_image"
include("FoxEngine/vendor/GLFW")
include("FoxEngine/vendor/GLAD")
include("FoxEngine/vendor/imgui")


project "FoxEngine"
	location "FoxEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin/int/"..outputdir.."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	pchheader "fepch.h"
	pchsource "FoxEngine/src/fepch.cpp"
	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}
	
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib",
	}
	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}
	
	filter "system:windows"
		systemversion "latest"

		defines {
			"FOX_PLATFORM_WINDOWS",
			"FOX_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "FOX_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "FOX_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Distribution"
		defines "FOX_DISTRIBUTION"
		buildoptions "/MD"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin/int/"..outputdir.."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"FoxEngine/vendor/spdlog/include",
		"FoxEngine/src",
		"FoxEngine/vendor",
		"%{IncludeDir.glm}",
	}

	filter "system:windows"
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
		symbols "on"

	filter "configurations:Release"
		defines "FOX_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Distribution"
		defines "FOX_DISTRIBUTION"
		buildoptions "/MD"
		optimize "on"