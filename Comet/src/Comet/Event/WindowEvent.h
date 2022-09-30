#pragma once

#include "Comet/Event/Event.h"

namespace comet {

	class WindowEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const noexcept override { return window_event; }
	protected:
		inline WindowEvent() noexcept = default;
	private:
		friend class Application;
	};


	class WindowClosedEvent : public WindowEvent {
	public:
		inline WindowClosedEvent() noexcept = default;

		static inline EventType getStaticType() noexcept { return window_closed; }
		virtual inline EventType getType() const noexcept override { return window_closed; }
		virtual inline std::string_view getName() const noexcept override { return "window_closed"; }
	private:
		friend class Application;
	};

	class WindowResizedEvent : public WindowEvent {
	public:
		inline WindowResizedEvent(uint32_t width, uint32_t height) noexcept : width(width), height(height) {}

		static inline EventType getStaticType() noexcept { return window_resized; }
		virtual inline EventType getType() const noexcept override { return window_resized; }
		virtual inline std::string_view getName() const noexcept override { return "window_resized"; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(width:" + std::to_string(width) + ",height:" + std::to_string(height) + ")"; }

		inline uint32_t getWidth() const noexcept { return width; }
		inline uint32_t getHeight() const noexcept { return height; }
	private:
		uint32_t width;
		uint32_t height;

		friend class Application;
	};

	class WindowMinimizedEvent : public WindowEvent {
	public:
		inline WindowMinimizedEvent(bool minimized) noexcept : minimized(minimized) {}

		static inline EventType getStaticType() noexcept { return window_minimized; }
		virtual inline EventType getType() const noexcept override { return window_minimized; }
		virtual inline std::string_view getName() const noexcept override { return "window_minimized"; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(minimized:" + (minimized ? "true" : "false") + ")"; }

		inline bool isMinimized() const noexcept { return minimized; }
	private:
		bool minimized;

		friend class Application;
	};

	class WindowMaximizedEvent : public WindowEvent {
	public:
		inline WindowMaximizedEvent(bool maximized) noexcept : maximized(maximized) {}

		static inline EventType getStaticType() noexcept { return window_maximized; }
		virtual inline EventType getType() const noexcept override { return window_maximized; }
		virtual inline std::string_view getName() const noexcept override { return "window_maximized"; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(maximized:" + (maximized ? "true" : "false") + ")"; }

		inline bool isMaximized() const noexcept { return maximized; }
	private:
		bool maximized;

		friend class Application;
	};

}
