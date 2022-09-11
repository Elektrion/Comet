#include "cmt_pch.h"
#include "Application.h"

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

#include "Comet/Renderer/Renderer.h"

namespace comet {

	Application* Application::instance = nullptr;

	Application::Application() : running(false), window(nullptr), layerstack() {
		CMT_PROFILE_FUNCTION();

		if(instance) {
			CMT_CORE_ERROR("Application has already been created!");
			return;
		}

		RenderAPI::init();

		instance = this;
		window = Window::create();
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		Renderer::init();
	}

	Application::~Application() {
		CMT_PROFILE_FUNCTION();

		instance = nullptr;
	}

	void Application::run() {
		CMT_PROFILE_FUNCTION();

		CMT_CORE_ASSERT(!running, "Application is already running!");

		running = true;
		auto last_timepoint = std::chrono::high_resolution_clock::now();
		Timestep dt = 0;

		while(running) {
			CMT_PROFILE_SCOPE("Application::run - gameloop");
			
			{
				CMT_PROFILE_SCOPE("Application::run - calculate time");

				auto timepoint = std::chrono::high_resolution_clock::now();
				dt = std::chrono::duration_cast<std::chrono::duration<float, std::chrono::seconds::period>>(timepoint - last_timepoint).count();
				last_timepoint = timepoint;
			}

			{
				CMT_PROFILE_SCOPE("Application::run - update layerstack");

				for(auto layer : layerstack)
					layer->onUpdate(dt);
			}

			window->onUpdate(dt);
		}

		running = false;
	}

	void Application::onEvent(Event& e) {
		CMT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClosedEvent>(std::bind(&Application::onWindowClosed, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizedEvent>(std::bind(&Application::onWindowResized, this, std::placeholders::_1));

		for(auto layer = layerstack.rbegin(); layer != layerstack.rend(); layer++) {
			if(!e.isHandled())
				(*layer)->onEvent(e);
		}
	}

	bool Application::onWindowClosed(WindowClosedEvent& e) {
		running = false;
		return true;
	}

	bool Application::onWindowResized(WindowResizedEvent& e) {
		window->getContext().setViewPort(0, 0, e.getWidth(), e.getHeight());
		return false;
	}

}
