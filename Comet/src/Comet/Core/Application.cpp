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
		window->setEventCallback(BIND_MEMBER_EVENT_FUNCTION(Application::onEvent));

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
		Timestep dt = 0;

		while(running) {
			CMT_PROFILE_SCOPE("Application::run - gameloop");
			
			dt = Time::mark();

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
		dispatcher.dispatch<WindowClosedEvent>(BIND_MEMBER_EVENT_FUNCTION(Application::onWindowClosed));
		dispatcher.dispatch<WindowResizedEvent>(BIND_MEMBER_EVENT_FUNCTION(Application::onWindowResized));

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
