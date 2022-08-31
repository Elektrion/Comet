#pragma once

#include "Comet/Core/LayerStack.h"
#include "Comet/Core/Window.h"

#include "Comet/Event/Event.h"
#include "Comet/Event/WindowEvent.h"

namespace comet {

	class Application {
	public:
		Application();
		virtual ~Application();

		inline const Scope<Window>& getWindow() const { return window; }

		inline void pushLayer(Ref<Layer> layer) { layerstack.push(layer); }
		inline void pushOverlay(Ref<Layer> layer) { layerstack.pushOverlay(layer); }
		inline void popLayer(Ref<Layer> layer) { layerstack.pop(layer); }
		inline void popOverlay(Ref<Layer> layer) { layerstack.popOverlay(layer); }

		void run();
	public:
		static inline Application* get() { return instance; }
	private:
		void onEvent(Event& e);
		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
	private:
		bool running;
		Scope<Window> window;
		LayerStack layerstack;
	private:
		static Application* instance;
	};

	Application* createApplication();

}
