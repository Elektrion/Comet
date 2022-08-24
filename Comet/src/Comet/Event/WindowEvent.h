#pragma once

#include "Comet/Event/Event.h"

namespace comet {

	class WindowEvent : public Event {
	public:
		virtual constexpr inline uint32_t getCategoryFlags() const override { return window_event; }
	protected:
		constexpr inline WindowEvent() = default;
	};

	class WindowClosedEvent : public WindowEvent {
	public:
		constexpr inline WindowClosedEvent() = default;

		static constexpr inline EventType getStaticType() { return window_closed; }
		virtual constexpr inline EventType getType() const override { return window_closed; }
		virtual constexpr inline std::string getName() const override { return "window_closed"; }
	};

	class WindowResizedEvent : public WindowEvent {
	public:
		constexpr inline WindowResizedEvent(uint32_t width, uint32_t height) : width(width), height(height) {}

		static constexpr inline EventType getStaticType() { return window_resized; }
		virtual constexpr inline EventType getType() const override { return window_resized; }
		virtual constexpr inline std::string getName() const override { return "window_resized"; }
		virtual constexpr inline std::string toString() const override { return getName() + "(width:" + std::to_string(width) + ",height:" + std::to_string(height) + ")"; }

		constexpr inline uint32_t getWidth() const { return width; }
		constexpr inline uint32_t getHeight() const { return height; }
	private:
		uint32_t width;
		uint32_t height;
	};

	class WindowMinimizedEvent : public WindowEvent {
	public:
		constexpr inline WindowMinimizedEvent(bool minimized) : minimized(minimized) {}

		static constexpr inline EventType getStaticType() { return window_minimized; }
		virtual constexpr inline EventType getType() const override { return window_minimized; }
		virtual constexpr inline std::string getName() const override { return "window_minimized"; }
		virtual constexpr inline std::string toString() const override { return getName() + "(minimized:" + (minimized ? "true" : "false") + ")"; }

		constexpr inline bool isMinimized() const { return minimized; }
	private:
		bool minimized;
	};

	class WindowMaximizedEvent : public WindowEvent {
	public:
		constexpr inline WindowMaximizedEvent(bool maximized) : maximized(maximized) {}

		static constexpr inline EventType getStaticType() { return window_maximized; }
		virtual constexpr inline EventType getType() const override { return window_maximized; }
		virtual constexpr inline std::string getName() const override { return "window_maximized"; }
		virtual constexpr inline std::string toString() const override { return getName() + "(maximized:" + (maximized ? "true" : "false") + ")"; }

		constexpr inline bool isMaximized() const { return maximized; }
	private:
		bool maximized;
	};
}
