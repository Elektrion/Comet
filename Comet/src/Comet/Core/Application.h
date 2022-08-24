#pragma once

#include "Comet/Core/Window.h"

namespace comet {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void run();
	public:
		static inline Application* get() { return instance; }
	private:
		bool running;
		Scope<Window> window;
	private:
		static Application* instance;
	};

	Application* createApplication();
}