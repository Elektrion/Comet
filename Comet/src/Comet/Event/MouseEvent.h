#pragma once

#include "Comet/Core/MouseCodes.h"

#include "Comet/Event/Event.h"

namespace comet {

	class MouseEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const noexcept override { return input_event | mouse_event; }
	protected:
		inline MouseEvent() noexcept = default;
	private:
		friend class Application;
	};


	class MouseMovedEvent : public MouseEvent {
	public:
		inline MouseMovedEvent(int32_t x, int32_t y) noexcept : x(x), y(y) {}

		static inline EventType getStaticType() noexcept { return mouse_moved; }
		virtual inline EventType getType() const noexcept override { return mouse_moved; }
		virtual inline std::string_view getName() const noexcept override { return "mouse_moved"; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		inline int32_t getX() const noexcept { return x; }
		inline int32_t getY() const noexcept { return y; }
	private:
		int32_t x;
		int32_t y;

		friend class Application;
	};

	class MouseScrolledEvent : public MouseEvent {
	public:
		inline MouseScrolledEvent(int32_t x, int32_t y) noexcept : x(x), y(y) {}

		static inline EventType getStaticType() noexcept { return mouse_scrolled; }
		virtual inline EventType getType() const noexcept override { return mouse_scrolled; }
		virtual inline std::string_view getName() const noexcept override { return "mouse_scrolled"; }
		virtual inline std::string toString() const noexcept override { return std::string(getName()) + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		inline int32_t getX() const noexcept { return x; }
		inline int32_t getY() const noexcept { return y; }
	private:
		int32_t x;
		int32_t y;

		friend class Application;
	};


	class MouseButtonEvent : public MouseEvent {
	public:
		virtual inline uint32_t getCategoryFlags() const noexcept override { return input_event | mouse_event | mouse_button_event; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(code:" + std::to_string(code) + ")"; }

		inline MouseCode getCode() const noexcept { return code; }
	protected:
		inline MouseButtonEvent(MouseCode code) noexcept : code(code) {}
	private:
		MouseCode code;

		friend class Application;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		inline MouseButtonPressedEvent(MouseCode code, bool repeated = false) noexcept : MouseButtonEvent(code), repeated(repeated) {}

		static inline EventType getStaticType() noexcept { return mouse_button_pressed; }
		virtual inline EventType getType() const noexcept override { return mouse_button_pressed; }
		virtual inline std::string_view getName() const noexcept override { return "mouse_button_pressed"; }

		inline bool isRepeated() const noexcept { return repeated; }
	private:
		bool repeated;

		friend class Application;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		inline MouseButtonReleasedEvent(MouseCode code) noexcept : MouseButtonEvent(code) {}

		static inline EventType getStaticType() noexcept { return mouse_button_released; }
		virtual inline EventType getType() const noexcept override { return mouse_button_released; }
		virtual inline std::string_view getName() const noexcept override { return "mouse_button_released"; }
	private:
		friend class Application;
	};

}
