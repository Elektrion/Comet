workspace "Comet"
	startproject "Sandbox"
	
	configurations {
		"Debug", 
		"Release", 
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}"

	includedir = {}
	includedir["glfw"] = "%{wks.location}/Comet/vendor/glfw/include"
	includedir["glad"] = "%{wks.location}/Comet/vendor/glad/include"

	filter "system:windows"
		architecture "x86_64"
	
	group "Dependencies"
		include "Comet/vendor/glfw"
		include "Comet/vendor/glad"
	group ""

include "Comet"
include "Sandbox"