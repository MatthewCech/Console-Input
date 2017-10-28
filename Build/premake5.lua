-- Premake5 Wiki: https://github.com/premake/premake-core/wiki
-- Based on Premake GLFW demo courtesy of JohannesMP
-- https://github.com/JohannesMP


-- Variable definition: CHANGE THESE TO MODIFY PROJECT NAME
-- Brief reminder: This is actual lua, functions and whatnot are totally allowed.
local ROOT         = "../"          -- Path to project root


-- [ WORKSPACE CONFIGURATION ] --
workspace "Console Input"                    -- Solution Name
    configurations { "Debug", "Release"}     -- Optimization/General config mode in VS
    platforms { "x64", "x86"}                -- Dropdown platforms section in VS
    location (ROOT .. "project_" .. _ACTION) -- Note: _ACTION is the argument passed to premake.

    -- [ PROJECT CONFIGURATION ] --
    project "console-input"                -- Project name
        targetname "console-input-testing" -- Executable name
        kind "ConsoleApp"                  -- Style of app in project- WindowedApp, ConsoleApp, etc.
        language "C++"

    -- [ COMPILER/LINKER CONFIG] --
    flags "FatalWarnings"  -- Warnings to 11! (all warnings on)

    -- Generate filters with info provided for Visual Studio
    filter { "platforms:*86" }
        architecture "x86"
    filter { "platforms:*64" }
        architecture "x64"

    -- Generate configs dropdown info, VS
    filter { "configurations:Debug" }
        defines { "DEBUG" }  -- Actively defined in code, can be checked for.
        symbols "On"
    filter { "configurations:Release" }
        defines { "NDEBUG" } -- Actively defined in code, can be checked for.
        optimize "On"

    filter {} -- Reset filter.

    -- [ BUILD CONFIGURATIONS ] --
    local cur_toolset = "default" -- workaround for premake issue #257

    filter {"system:macosx" } -- Mac uses clang.
        toolset "clang"
   
    filter { "action:gmake" }
        buildoptions { "-std=c++14" }

    -- Set the rpath on the executable, to allow for relative path for dynamic lib
    filter { "system:macosx", "toolset:clang or gcc" }
        linkoptions { "-rpath @executable_path/lib" }
    
    filter {"system:windows", "action:vs*"}
        linkoptions   { "/ignore:4099" }      -- Ignore library pdb warnings when running in debug
        systemversion("10.0.15063.0")         -- windows 10 SDK


    filter {} -- clear filter   


    -- [ FILE PATH CONFIGURATIONS ] --
    local output_dir_root         = ROOT .. "bin_%{cfg.platform}_%{cfg.buildcfg}_" .. _ACTION
    targetdir(output_dir_root)    -- Where all output files are stored
    local source_dir_root         = ROOT .. "Source"

    -- Files to be compiled (cpp) or added to project (visual studio)
    files
    {
      source_dir_root .. "/**.c",
      source_dir_root .. "/**.h",
      source_dir_root .. "/**.cpp",
      source_dir_root .. "/**.hpp",
      source_dir_root .. "/**.tpp",
    }

    -- Omit templates from visual studio
    filter { "files:**.tpp" }
        flags {"ExcludeFromBuild"}
    filter {}

    -- Ignore files for other operating systems (not necessary in this project)
    filter { "system:macosx" } removefiles { source_dir_root .. "/**_windows.*" }
    filter { "system:windows" } removefiles { source_dir_root .. "/**_macosx.*"  }
    filter {} -- reset filter

    -- Organize VS filters
    vpaths {
      ["Headers"] = 
          { 
            source_dir_root .. "**.h", 
            source_dir_root .. "**.hpp"
          },
      ["Sources/*"] = 
        {
          source_dir_root .. "**.c", 
          source_dir_root .. "**.cpp", 
          source_dir_root .. "**.tpp"
        },
      ["Docs"] = "**.txt"
    }
