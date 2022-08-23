project "Comet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cmt_pch.h"
	pchsource "src/cmt_pch.cpp"

	files {
		"src/**.h", 
		"src/**.cpp"
	}

	includedirs {
		"src"
	}

	links {
		
	}


	filter "platforms:Windows"
		defines "CMT_PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines {
			"CMT_DEBUG", 
			"CMT_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines {
			"CMT_RELEASE", 
			"CMT_ENABLE_ASSERTS"
		}
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CMT_DIST"
		runtime "Release"
		optimize "On"