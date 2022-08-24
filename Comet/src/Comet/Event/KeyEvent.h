#pragma once

#include "Comet/Event/Event.h"
#include "Comet/Core/KeyCodes.h"

namespace comet {

	class KeyEvent : public Event {
	public:
		virtual constexpr inline uint32_t getCategoryFlags() const override { return input_event | key_event; }
		virtual constexpr inline std::string toString() const override { return getName() + "(code:" + std::to_string(code) + ")"; }

		constexpr inline KeyCode getCode() const { return code; }
	protected:
		constexpr inline KeyEvent(KeyCode code) : code(code) {}
	private:
		KeyCode code;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		constexpr inline KeyPressedEvent(KeyCode code, bool repeated = false) : KeyEvent(code), repeated(repeated) {}

		static constexpr inline EventType getStaticType() { return key_pressed; }
		virtual constexpr inline EventType getType() const override { return key_pressed; }
		virtual constexpr inline std::string getName() const override { return "key_pressed"; }

		constexpr inline bool isRepeated() const { return repeated; }
	private:
		bool repeated;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		constexpr inline KeyReleasedEvent(KeyCode code) : KeyEvent(code) {}

		static constexpr inline EventType getStaticType() { return key_released; }
		virtual constexpr inline EventType getType() const override { return key_released; }
		virtual constexpr inline std::string getName() const override { return "key_released"; }
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		constexpr inline KeyTypedEvent(KeyCode code) : KeyEvent(code) {}

		static constexpr inline EventType getStaticType() { return key_typed; }
		virtual constexpr inline EventType getType() const override { return key_typed; }
		virtual constexpr inline std::string getName() const override { return "key_typed"; }

		constexpr inline uint32_t getUnicodeCharacter() const { return getCode(); }
	};

}
