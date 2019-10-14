workspace "Kigu"
    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

    filter { }

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
        "Kigu/include",
        "Dependencies/glad/Include",
        "Dependencies/entt/Include"
    }

    files
    {
        "Kigu/src/**.cpp",
        "Kigu/src/**.h",
        "Kigu/include/**.h",
		"Kigu/include/entt/entt.hpp",

        "Dependencies/glad/Src/**.c"
    }

    includeGLFW()
    linkGLFW()

project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    includedirs
    {
        "Kigu/include",
        "Dependencies/glad/Include" -- TODO: Temporary.
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
