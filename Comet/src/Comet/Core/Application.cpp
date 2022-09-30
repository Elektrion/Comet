#include "cmt_pch.h"
#include "Application.h"

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

#include "Comet/Renderer/Renderer.h"

namespace comet {

	Application* Application::instance = nullptr;

	Application::Application() : running(false), enable_dockspace(false), window(nullptr), layerstack(), imgui_layer(createRef<ImGuiLayer>()) {
		CMT_PROFILE_FUNCTION();

		if(instance) {
			CMT_CORE_ERROR("Application has already been created!");
			return;
		}

		RenderAPI::init();

		instance = this;
		window = Window::create();
		window->setEventCallback(BIND_MEMBER_EVENT_FUNCTION(Application::onEvent));

		pushOverlay(imgui_layer);

		Renderer::init();
	}

	Application::~Application() {
		CMT_PROFILE_FUNCTION();

		instance = nullptr;
	}

	void Application::close() {
		running = false;
	}

	void Application::run() {
		CMT_PROFILE_FUNCTION();

		CMT_CORE_ASSERT(!running, "Application is already running!");

		running = true;
		Timestep dt = 0;

		while(running) {
			CMT_PROFILE_SCOPE("Application::run - gameloop");
			
			dt = Time::mark();
			window->beginImGui();
			viewport = imgui_layer->beginImGui();

			{
				CMT_PROFILE_SCOPE("Application::run - process event_queue");

				for(const auto& event : event_queue)
					onEvent(*event);
				event_queue.clear();
			}

			{
				CMT_PROFILE_SCOPE("Application::run - update layerstack");

				for(auto layer : layerstack)
					layer->onUpdate(dt);
			}

			{
				CMT_PROFILE_SCOPE("Application::run - imgui render");

				for(auto layer : layerstack)
					layer->onImGuiRender();
			}

			imgui_layer->endImGui();
			window->endImGui();
			window->onUpdate(dt);
		}

		running = false;
	}

	void Application::enableDockspace() {
		enable_dockspace = true;
		imgui_layer->enableDockspace();
	}

	void Application::postEvent(const Ref<Event>& e) {
		event_queue.push_back(e);
	}

	void Application::onEvent(Event& e) {
		CMT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClosedEvent>(BIND_MEMBER_EVENT_FUNCTION(Application::onWindowClosed));
		dispatcher.dispatch<WindowResizedEvent>(BIND_MEMBER_EVENT_FUNCTION(Application::onWindowResized));

		for(auto layer = layerstack.rbegin(); layer != layerstack.rend() && !e.isHandled(); layer++)
			(*layer)->onEvent(e);
	}

	bool Application::onWindowClosed(WindowClosedEvent& e) {
		running = false;
		return true;
	}

	bool Application::onWindowResized(WindowResizedEvent& e) {
		if(enable_dockspace) {
			e.width = viewport[2];
			e.height = viewport[3];
		}
		else window->getContext().setViewPort(0, 0, e.getWidth(), e.getHeight());
		return false;
	}

}
