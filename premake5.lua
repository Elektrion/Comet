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
	includedir["glm"] = "%{wks.location}/Comet/vendor/glm"

	filter "system:windows"
		architecture "x86_64"

	dev_assets_dir = "\"%{wks.location}/Comet/assets\""
	dist_assets_dir = "\"assets\""
	
	group "Dependencies"
		include "Comet/vendor/glfw"
		include "Comet/vendor/glad"
	group ""

include "Comet"
include "Sandbox"