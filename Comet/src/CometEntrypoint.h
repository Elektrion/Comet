#pragma once

#include "cmt_pch.h"
#include "Comet/Core/Core.h"
#include "Comet/Core/Application.h"

int main() {
	CMT_CORE_COLORED(text_faint_purple, "Welcome to Comet Engine!");

	comet::Application* app = comet::createApplication();
	app->run();
	delete app;

	CMT_CORE_INFO("Shutting down...");
}