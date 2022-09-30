#pragma once

#include "Comet/Core/Core.h"
#include "Comet/Core/ImGuiLayer.h"
#include "Comet/Core/LayerStack.h"
#include "Comet/Core/Window.h"

#include "Comet/Event/Event.h"
#include "Comet/Event/WindowEvent.h"

namespace comet {

	class Application {
	public:
		Application();
		virtual ~Application();

		inline Application(const Application&) noexcept = delete;
		inline Application(const Application&&) noexcept = delete;
		inline Application& operator=(const Application&) noexcept = delete;
		inline Application& operator=(const Application&&) noexcept = delete;

		inline const Scope<Window>& getWindow() const noexcept { return window; }

		inline void pushLayer(const Ref<Layer>& layer) noexcept { layerstack.push(layer); }
		inline void pushOverlay(const Ref<Layer>& layer) noexcept { layerstack.pushOverlay(layer); }
		inline void popLayer(const Ref<Layer>& layer) noexcept { layerstack.pop(layer); }
		inline void popOverlay(const Ref<Layer>& layer) noexcept { layerstack.popOverlay(layer); }

		void close();
		void run();

		void enableDockspace();
		void postEvent(const Ref<Event>& e);
	public:
		static inline Application* get() noexcept { return instance; }
	private:
		void onEvent(Event& e);
		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
	private:
		bool running;
		Scope<Window> window;
		LayerStack layerstack;
		Ref<ImGuiLayer> imgui_layer;
		bool enable_dockspace;
		std::array<uint32_t, 4> viewport;
		std::vector<Ref<Event>> event_queue;
	private:
		static Application* instance;
	};

	Application* createApplication();

}
