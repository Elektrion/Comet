#pragma once

#include "Comet/Core/Window.h"

#include "Comet/Event/Event.h"
#include "Comet/Event/WindowEvent.h"

namespace comet {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void run();
	public:
		static inline Application* get() { return instance; }
	private:
		void onEvent(Event& e);
		bool onWindowClosed(WindowClosedEvent& e);
	private:
		bool running;
		Scope<Window> window;
	private:
		static Application* instance;
	};

	Application* createApplication();
}