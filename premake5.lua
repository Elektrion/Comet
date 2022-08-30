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
	includedir["stb"] = "%{wks.location}/Comet/vendor/stb"

	dev_assets_dir = "\"%{!wks.location}/Comet/assets/comet\""
	dist_assets_dir = "\"assets/comet\""

	filter "system:windows"
		architecture "x86_64"
	
	group "Dependencies"
		include "Comet/vendor/glfw"
		include "Comet/vendor/glad"
		include "Comet/vendor/stb"
	group ""

include "Comet"
include "Sandbox"