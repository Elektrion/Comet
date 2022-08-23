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

	filter "platforms:Windows"
		system "Windows"
		architecture "x86_64"

include "Comet"
include "Sandbox"