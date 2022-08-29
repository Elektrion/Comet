project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h", 
		"src/**.cpp"
	}

	includedirs {
		"src", 
		"%{wks.location}/Comet/src", 
		"%{includedir.glm}"
	}

	links {
		"Comet"
	}


	filter "system:windows"
		systemversion "latest"
		defines "CMT_PLATFORM_WINDOWS"

	filter "system:macosx"
		defines "CMT_PLATFORM_MACOS"
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
