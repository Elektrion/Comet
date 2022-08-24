#pragma once

#include <GLFW/glfw3.h>
#include "Comet/Core/Window.h"

namespace comet {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		~WindowsWindow();

		virtual inline uint32_t getWidth() const override { return data.width; }
		virtual inline uint32_t getHeight() const override { return data.height; }
		virtual bool isVsyncEnabled() const override { return data.vsync; };
		virtual void setVsync(bool vsync) override;
		virtual void onUpdate(Timestep dt) override;
	private:
		void init(const WindowProperties& props);
		void shutdown();
	private:
		struct WindowData {
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;

			WindowData() : title("Comet Engine"), width(1270), height(720), vsync(true) {}
		};

		GLFWwindow* window;
		WindowData data;
	};

}