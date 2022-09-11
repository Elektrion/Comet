#pragma once

#include "cmt_pch.h"
#include "Comet/Core/Application.h"
#include "Comet/Core/Core.h"
#include "Comet/Core/Instrumentation.h"

int main(int argc, char* argv[]) {

	comet::Instrumentation::begin("profile_startup.json");
	comet::Application* app = comet::createApplication();
	comet::Instrumentation::end();

	comet::Instrumentation::begin("profile_gameloop.json");
	app->run();
	comet::Instrumentation::end();

	comet::Instrumentation::begin("profile_shutdown.json");
	delete app;
	comet::Instrumentation::end();

}
