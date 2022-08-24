#pragma once

#include "Comet/Event/Event.h"
#include "Comet/Core/MouseCodes.h"

namespace comet {

	class MouseEvent : public Event {
	public:
		virtual constexpr inline uint32_t getCategoryFlags() const override { return input_event | mouse_event; }
	protected:
		constexpr inline MouseEvent() = default;
	};

	class MouseMovedEvent : public MouseEvent {
	public:
		constexpr inline MouseMovedEvent(int32_t x, int32_t y) : x(x), y(y) {}

		static constexpr inline EventType getStaticType() { return mouse_moved; }
		virtual constexpr inline EventType getType() const override { return mouse_moved; }
		virtual constexpr inline std::string getName() const override { return "mouse_moved"; }
		virtual constexpr inline std::string toString() const override { return getName() + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		constexpr inline int32_t getX() const { return x; }
		constexpr inline int32_t getY() const { return y; }
	private:
		int32_t x;
		int32_t y;
	};

	class MouseScrolledEvent : public MouseEvent {
	public:
		constexpr inline MouseScrolledEvent(int32_t x, int32_t y) : x(x), y(y) {}

		static constexpr inline EventType getStaticType() { return mouse_scrolled; }
		virtual constexpr inline EventType getType() const override { return mouse_scrolled; }
		virtual constexpr inline std::string getName() const override { return "mouse_scrolled"; }
		virtual constexpr inline std::string toString() const override { return getName() + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		constexpr inline int32_t getX() const { return x; }
		constexpr inline int32_t getY() const { return y; }
	private:
		int32_t x;
		int32_t y;
	};

	class MouseButtonEvent : public MouseEvent {
	public:
		virtual constexpr inline uint32_t getCategoryFlags() const override { return input_event | mouse_event | mouse_button_event; }
		virtual constexpr inline std::string toString() const override { return getName() + "(code:" + std::to_string(code) + ")"; }

		constexpr inline MouseCode getCode() const { return code; }
	protected:
		constexpr inline MouseButtonEvent(MouseCode code) : code(code) {}
	private:
		MouseCode code;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		constexpr inline MouseButtonPressedEvent(MouseCode code, bool repeated = false) : MouseButtonEvent(code), repeated(repeated) {}

		static constexpr inline EventType getStaticType() { return mouse_button_pressed; }
		virtual constexpr inline EventType getType() const override { return mouse_button_pressed; }
		virtual constexpr inline std::string getName() const override { return "mouse_button_pressed"; }

		constexpr inline bool isRepeated() const { return repeated; }
	private:
		bool repeated;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		constexpr inline MouseButtonReleasedEvent(MouseCode code) : MouseButtonEvent(code) {}

		static constexpr inline EventType getStaticType() { return mouse_button_released; }
		virtual constexpr inline EventType getType() const override { return mouse_button_released; }
		virtual constexpr inline std::string getName() const override { return "mouse_button_released"; }
	};

}
