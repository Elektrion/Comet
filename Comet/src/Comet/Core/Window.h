#pragma once

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

namespace comet {

	class Window {
	public:
		struct WindowProperties {
			std::string title = "Comet Engine";
			uint32_t width = 1280;
			uint32_t height = 720;
		};
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual bool isVsyncEnabled() const = 0;
		virtual void setVsync(bool vsync) = 0;
		virtual void onUpdate(Timestep dt) = 0;
		virtual void setEventCallback(EventCallbackFn callback) = 0;
	public:
		static Scope<Window> createWindow(const WindowProperties& props = {});
	};

}