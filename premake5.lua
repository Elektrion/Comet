workspace "Comet"
	architecture "x86_64"
	startproject "Sandbox"
	
	configurations {
		"Debug", 
		"Release", 
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	includedir = {}

include "Comet"
include "Sandbox"