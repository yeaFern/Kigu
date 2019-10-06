workspace "Kigu"
    configurations { "Debug", "Release" }


project "Kigu"
    location "Kigu"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

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

project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

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
