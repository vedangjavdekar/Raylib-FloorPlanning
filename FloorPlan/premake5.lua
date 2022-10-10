project "FloorPlan"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   targetdir "%{_MAIN_SCRIPT_DIR}/bin/%{prj.name}/%{cfg.buildcfg}"
   debugdir "%{_MAIN_SCRIPT_DIR}/bin/%{prj.name}/%{cfg.buildcfg}"
   objdir "%{_MAIN_SCRIPT_DIR}/bin-int/%{prj.name}/%{cfg.buildcfg}"
   location "%{_MAIN_SCRIPT_DIR}/build/%{prj.name}"

   dependson {"raylib"}
   links{"raylib"}

   libdirs{
      "%{_MAIN_SCRIPT_DIR}/bin/raylib/%{cfg.buildcfg}"
   }
   files { 
      "%{_MAIN_SCRIPT_DIR}/%{prj.name}/include/**.h", 
      "%{_MAIN_SCRIPT_DIR}/%{prj.name}/include/**.hpp", 
      "%{_MAIN_SCRIPT_DIR}/%{prj.name}/src/**.cpp" 
   }

   includedirs {
      "%{_MAIN_SCRIPT_DIR}/%{prj.name}/include/",
      "%{_MAIN_SCRIPT_DIR}/raylib/src/"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
   
   filter "action:vs*"
      links{"raylib.lib"}

