#pragma once

#include "Comet/Core/MouseCodes.h"

#include "Comet/Event/Event.h"

namespace comet {

	class MouseEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const override { return input_event | mouse_event; }
	protected:
		inline MouseEvent() = default;
	};


	class MouseMovedEvent : public MouseEvent {
	public:
		inline MouseMovedEvent(int32_t x, int32_t y) : x(x), y(y) {}

		static inline EventType getStaticType() { return mouse_moved; }
		virtual inline EventType getType() const override { return mouse_moved; }
		virtual inline std::string getName() const override { return "mouse_moved"; }
		virtual inline std::string toString() const override { return getName() + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		inline int32_t getX() const { return x; }
		inline int32_t getY() const { return y; }
	private:
		int32_t x;
		int32_t y;
	};

	class MouseScrolledEvent : public MouseEvent {
	public:
		inline MouseScrolledEvent(int32_t x, int32_t y) : x(x), y(y) {}

		static inline EventType getStaticType() { return mouse_scrolled; }
		virtual inline EventType getType() const override { return mouse_scrolled; }
		virtual inline std::string getName() const override { return "mouse_scrolled"; }
		virtual inline std::string toString() const override { return getName() + "(x:" + std::to_string(x) + ",y:" + std::to_string(y) + ")"; }

		inline int32_t getX() const { return x; }
		inline int32_t getY() const { return y; }
	private:
		int32_t x;
		int32_t y;
	};


	class MouseButtonEvent : public MouseEvent {
	public:
		virtual inline uint32_t getCategoryFlags() const override { return input_event | mouse_event | mouse_button_event; }
		virtual inline std::string toString() const override { return getName() + "(code:" + std::to_string(code) + ")"; }

		inline MouseCode getCode() const { return code; }
	protected:
		inline MouseButtonEvent(MouseCode code) : code(code) {}
	private:
		MouseCode code;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		inline MouseButtonPressedEvent(MouseCode code, bool repeated = false) : MouseButtonEvent(code), repeated(repeated) {}

		static inline EventType getStaticType() { return mouse_button_pressed; }
		virtual inline EventType getType() const override { return mouse_button_pressed; }
		virtual inline std::string getName() const override { return "mouse_button_pressed"; }

		inline bool isRepeated() const { return repeated; }
	private:
		bool repeated;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		inline MouseButtonReleasedEvent(MouseCode code) : MouseButtonEvent(code) {}

		static inline EventType getStaticType() { return mouse_button_released; }
		virtual inline EventType getType() const override { return mouse_button_released; }
		virtual inline std::string getName() const override { return "mouse_button_released"; }
	};

}
