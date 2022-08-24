#include "cmt_pch.h"
#include "Application.h"

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

namespace comet {

	Application* Application::instance = nullptr;

	Application::Application() : running(false) {
		if(instance) {
			CMT_CORE_ERROR("Application has already been created!");
			return;
		}

		instance = this;
		window = Window::createWindow();
	}

	void Application::run() {
		CMT_CORE_ASSERT(!running, "Application is already running!");

		running = true;
		auto last_timepoint = std::chrono::high_resolution_clock::now();

		while(running) {
			auto timepoint = std::chrono::high_resolution_clock::now();
			Timestep dt = std::chrono::duration_cast<std::chrono::duration<float, std::chrono::milliseconds::period>>(timepoint - last_timepoint).count();
			last_timepoint = timepoint;
			CMT_CORE_TRACE("Delta time: {0}", dt);

			window->onUpdate(dt);
		}

		running = false;
	}

}
