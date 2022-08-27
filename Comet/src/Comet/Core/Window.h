#pragma once

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

namespace comet {

	class Window {
	public:
		struct WindowProperties {
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;

			WindowProperties() : title("Comet Engine"), width(1280), height(720), vsync(true) {}
		};
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual bool isVsyncEnabled() const = 0;
		virtual bool isMinimized() const = 0;
		virtual bool isMaximized() const = 0;

		virtual void setVsync(bool vsync) = 0;
		virtual void setMinimized(bool minimized) = 0;
		virtual void setMaximized(bool maximized) = 0;

		virtual void* getNativeWindow() const = 0;

		virtual void onUpdate(Timestep dt) = 0;
		virtual void setEventCallback(EventCallbackFn callback) = 0;
	public:
		static Scope<Window> create(const WindowProperties& props = {});
	};

}
