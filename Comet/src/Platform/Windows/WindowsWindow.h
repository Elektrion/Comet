#pragma once

#include <GLFW/glfw3.h>

#include "Comet/Core/Window.h"

#include "Comet/Event/Event.h"

namespace comet {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		~WindowsWindow();

		virtual inline uint32_t getWidth() const override { return data.width; }
		virtual inline uint32_t getHeight() const override { return data.height; }
		virtual bool isVsyncEnabled() const override { return data.vsync; };
		virtual bool isMinimized() const override { return data.minimized; }
		virtual bool isMaximized() const override { return data.maximized; }

		virtual void setVsync(bool vsync) override;
		virtual void setMinimized(bool minimized) override;
		virtual void setMaximized(bool maximized) override;

		virtual void onUpdate(Timestep dt) override;
		virtual void setEventCallback(EventCallbackFn callback) override;
	private:
		void init(const WindowProperties& props);
		void shutdown();
	private:
		struct WindowData {
			std::string title = "Comet Engine";
			uint32_t width = 1270;
			uint32_t height = 720;
			bool vsync = true;
			bool minimized = false;
			bool maximized = false;
			EventCallbackFn event_callback = [](Event&) {};
		};

		GLFWwindow* window;
		WindowData data;
	};

}
