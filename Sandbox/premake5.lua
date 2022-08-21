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
		"%{wks.location}/Comet/src"
	}

	links {
		"Comet"
	}


	filter "system:windows"
		defines "CMT_SYSTEM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CMT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CMT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CMT_DIST"
		runtime "Release"
		optimize "On"