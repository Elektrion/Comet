#pragma once

#include "cmt_pch.h"
#include "Comet/Core/Core.h"
#include "Comet/Core/Application.h"

int main(int argc, char* argv[]) {

	comet::Application* app = comet::createApplication();
	app->run();
	delete app;

}
