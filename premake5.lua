workspace "Kigu"
    configurations { "Debug", "Release" }
    
	targetdir "Build/Bin/%{prj.name}/%{cfg.longname}"
	objdir "Build/Obj/%{prj.name}/%{cfg.longname}"

function includeGLFW()
    includedirs "Dependencies/GLFW/Include"
end

function linkGLFW()
    libdirs "Dependencies/GLFW/Lib"

    links "glfw3"
end

project "Kigu"
    location "Kigu"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    includedirs
    {
        "Kigu/include"
    }

    files
    {
        "Kigu/src/**.cpp",
        "Kigu/src/**.h",
        "Kigu/include/**.h"
    }

    includeGLFW()

project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    includedirs
    {
        "Kigu/include"
    }

    files
    {
        "Example/src/**.cpp",
        "Example/src/**.h"
    }

    links
    {
        "Kigu"
    }

    includeGLFW()
    linkGLFW()
