project "Comet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h", 
		"src/**.cpp"
	}

	removefiles {
		"src/Platform/**"
	}

	includedirs {
		"src", 
		"%{includedir.glfw}", 
		"%{includedir.glad}"
	}

	links {
		"glfw", 
		"glad"
	}


	filter "system:windows"
		systemversion "latest"	
		pchheader "cmt_pch.h"
		pchsource "src/cmt_pch.cpp"
		defines {
			"CMT_PLATFORM_WINDOWS", 
			"GLFW_INCLUDE_NONE"
		}
		files {
			"src/Platform/OpenGL/**.h", 
			"src/Platform/OpenGL/**.cpp", 
			"src/Platform/Windows/**.h", 
			"src/Platform/Windows/**.cpp"
		}

	filter "system:macosx"
		pchheader "src/cmt_pch.h"
		defines {
			"CMT_PLATFORM_MACOS", 
			"GLFW_INCLUDE_NONE"
		}
		files {
			"src/Platform/MacOS/**.h", 
			"src/Platform/MacOS/**.cpp", 
			"src/Platform/OpenGL/**.h", 
			"src/Platform/OpenGL/**.cpp"
		}
		links {
			"Cocoa.framework", 
			"IOKit.framework", 
			"CoreFoundation.framework"
		}

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
