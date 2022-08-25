#pragma once

#include "Comet/Event/Event.h"

namespace comet {

	class WindowEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const override { return window_event; }
	protected:
		inline WindowEvent() = default;
	};


	class WindowClosedEvent : public WindowEvent {
	public:
		inline WindowClosedEvent() = default;

		static inline EventType getStaticType() { return window_closed; }
		virtual inline EventType getType() const override { return window_closed; }
		virtual inline std::string getName() const override { return "window_closed"; }
	};

	class WindowResizedEvent : public WindowEvent {
	public:
		inline WindowResizedEvent(uint32_t width, uint32_t height) : width(width), height(height) {}

		static inline EventType getStaticType() { return window_resized; }
		virtual inline EventType getType() const override { return window_resized; }
		virtual inline std::string getName() const override { return "window_resized"; }
		virtual inline std::string toString() const override { return getName() + "(width:" + std::to_string(width) + ",height:" + std::to_string(height) + ")"; }

		inline uint32_t getWidth() const { return width; }
		inline uint32_t getHeight() const { return height; }
	private:
		uint32_t width;
		uint32_t height;
	};

	class WindowMinimizedEvent : public WindowEvent {
	public:
		inline WindowMinimizedEvent(bool minimized) : minimized(minimized) {}

		static inline EventType getStaticType() { return window_minimized; }
		virtual inline EventType getType() const override { return window_minimized; }
		virtual inline std::string getName() const override { return "window_minimized"; }
		virtual inline std::string toString() const override { return getName() + "(minimized:" + (minimized ? "true" : "false") + ")"; }

		inline bool isMinimized() const { return minimized; }
	private:
		bool minimized;
	};

	class WindowMaximizedEvent : public WindowEvent {
	public:
		inline WindowMaximizedEvent(bool maximized) : maximized(maximized) {}

		static inline EventType getStaticType() { return window_maximized; }
		virtual inline EventType getType() const override { return window_maximized; }
		virtual inline std::string getName() const override { return "window_maximized"; }
		virtual inline std::string toString() const override { return getName() + "(maximized:" + (maximized ? "true" : "false") + ")"; }

		inline bool isMaximized() const { return maximized; }
	private:
		bool maximized;
	};

}
