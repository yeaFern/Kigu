workspace "Kigu"
    configurations { "Debug", "Release" }


project "Kigu"
    location "Kigu"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    files
    {
        "Kigu/src/**.cpp",
        "Kigu/src/**.h"
    }
