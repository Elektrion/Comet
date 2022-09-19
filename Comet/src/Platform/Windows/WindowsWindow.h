#pragma once

#include "GLFW/glfw3.h"

#include "Comet/Core/Window.h"

#include "Comet/Event/Event.h"

#include "Comet/Renderer/GraphicsContext.h"

namespace comet {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		virtual inline uint32_t getWidth() const noexcept override { return data.width; }
		virtual inline uint32_t getHeight() const noexcept override { return data.height; }
		virtual inline float getAspectRatio() const noexcept override { return float(data.width) / float(data.height); }
		virtual inline bool isVsyncEnabled() const noexcept override { return data.vsync; };
		virtual inline bool isMinimized() const noexcept override { return data.minimized; }
		virtual inline bool isMaximized() const noexcept override { return data.maximized; }

		virtual void setVsync(bool vsync) override;
		virtual void setMinimized(bool minimized) override;
		virtual void setMaximized(bool maximized) override;

		virtual inline void* getNativeWindow() const noexcept override { return window; }
		virtual inline GraphicsContext& getContext() noexcept override { return *context; }

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
		Scope<GraphicsContext> context;
		WindowData data;
	};

}
