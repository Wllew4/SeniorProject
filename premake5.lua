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

    files { "src/**.h", "src/**.cpp" }

    filter "configurations:Release"
        defines { "RELEASE" }
        symbols "On"