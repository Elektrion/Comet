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
		"%{includedir.glad}", 
		"%{includedir.glm}", 
		"%{includedir.stb}", 
		"%{includedir.imgui}"
	}

	links {
		"glfw", 
		"glad", 
		"stb", 
		"imgui"
	}


	filter "system:windows"
		systemversion "latest"
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
			"CMT_ENABLE_ASSERTS", 
			"CMT_ENABLE_PROFILING", 
			"CMT_ASSETS_DIR=%{dev_assets_dir}"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines {
			"CMT_RELEASE", 
			"CMT_ENABLE_ASSERTS", 
			"CMT_ENABLE_PROFILING", 
			"CMT_ASSETS_DIR=%{dev_assets_dir}"
		}
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines {
			"CMT_DIST", 
			"CMT_ASSETS_DIR=%{dist_assets_dir}"
		}
		runtime "Release"
		optimize "On"
