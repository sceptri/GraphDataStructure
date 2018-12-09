workspace "GraphDataStructure"
    architecture "x64"

    configurations
    {
        "Debug"
    }

    files
    {
        "premake5.lua"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GraphStructure"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
    {
        "src/headers"
    }

    filter "system:linux"
        buildoptions {"-std=c++17"}
