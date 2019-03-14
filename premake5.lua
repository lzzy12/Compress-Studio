workspace "ComrpessStudio"
	architecture "x64"

	configurations{
		"Debug",
		"Release"
	}

outdir = "build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
objDir = "build/bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
project "utils"
	location "utils"
	kind "SharedLib"
	language "C++"
	targetdir(outdir .. "%{prj.name}")
	objdir(objDir .. "%{prj.name}")
	files{
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.h"
	}
	postbuildcommands {
		"{COPY} %{wks.location}" .. outdir .. "%{prj.name} %{wks.location}" .. outdir .. "cli"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines{
			"CS_BUILD_DLL",
			"CS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CS_RELEASE"
		optimize "On"

project "cli"
	location "cli"
	kind "consoleApp"
	language "C++"
	targetdir(outdir .. "%{prj.name}")
	objdir(objDir .. "%{prj.name}")
	files{
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.h"
	}
	includedirs{
		"utils/"
	}
	links {
		"utils"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines "CS_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		symbols "On"
		defines "CS_DEBUG"

	filter "configurations:Release"
		optimize "On"
		defines "CS_RELEASE"
