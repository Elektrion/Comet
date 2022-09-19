#pragma once

#include "Comet/Core/Core.h"
#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"

#include "Comet/Renderer/GraphicsContext.h"

namespace comet {

	class Window {
	public:
		struct WindowProperties {
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;

			inline WindowProperties() noexcept : title("Comet Engine"), width(1280), height(720), vsync(true) {}
		};
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		inline Window() noexcept = default;
		virtual inline ~Window() noexcept = default;

		inline Window(const Window&) noexcept = delete;
		inline Window(const Window&&) noexcept = delete;
		inline Window& operator=(const Window&) noexcept = delete;
		inline Window& operator=(const Window&&) noexcept = delete;

		virtual uint32_t getWidth() const noexcept = 0;
		virtual uint32_t getHeight() const noexcept = 0;
		virtual float getAspectRatio() const noexcept = 0;
		virtual bool isVsyncEnabled() const noexcept = 0;
		virtual bool isMinimized() const noexcept = 0;
		virtual bool isMaximized() const noexcept = 0;

		virtual void setVsync(bool vsync) = 0;
		virtual void setMinimized(bool minimized) = 0;
		virtual void setMaximized(bool maximized) = 0;

		virtual void* getNativeWindow() const noexcept = 0;
		virtual GraphicsContext& getContext() noexcept = 0;

		virtual void onUpdate(Timestep dt) = 0;
		virtual void setEventCallback(EventCallbackFn callback) = 0;
	public:
		static Scope<Window> create(const WindowProperties& props = {});
	};

}
