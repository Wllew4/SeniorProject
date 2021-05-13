workspace "JanelleLang"
    configurations { "Release" }

project "JanelleInterpreter"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin"
    targetname "janelle"
    includedirs
    {
        "src"
    }

    files { "**.h", "**.cpp" }

    filter "configurations:Release"
        defines { "DEBUG" }
        symbols "On"