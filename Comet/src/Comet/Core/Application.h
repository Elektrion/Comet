#pragma once

namespace comet {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void run();
	private:
		bool running;
	};

	comet::Application* createApplication();
}