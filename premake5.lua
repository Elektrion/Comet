workspace "Comet"
	startproject "Sandbox"
	
	configurations {
		"Debug", 
		"Release", 
		"Dist"
	}

	platforms {
		"Windows"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	includedir = {}
	includedir["glfw"] = "%{wks.location}/Comet/vendor/glfw/include"
	includedir["glad"] = "%{wks.location}/Comet/vendor/glad/include"

	filter "platforms:Windows"
		system "Windows"
		architecture "x86_64"
	
	group "Dependencies"
		include "Comet/vendor/glfw"
		include "Comet/vendor/glad"
	group ""

include "Comet"
include "Sandbox"