#pragma once

#include "Comet/Core/KeyCodes.h"

#include "Comet/Event/Event.h"

namespace comet {

	class KeyEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const override { return input_event | key_event; }
		virtual inline std::string toString() const override { return getName() + "(code:" + std::to_string(code) + ")"; }

		inline KeyCode getCode() const { return code; }
	protected:
		inline KeyEvent(KeyCode code) : code(code) {}
	private:
		KeyCode code;
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		inline KeyPressedEvent(KeyCode code, bool repeated = false) : KeyEvent(code), repeated(repeated) {}

		static inline EventType getStaticType() { return key_pressed; }
		virtual inline EventType getType() const override { return key_pressed; }
		virtual inline std::string getName() const override { return "key_pressed"; }

		inline bool isRepeated() const { return repeated; }
	private:
		bool repeated;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		inline KeyReleasedEvent(KeyCode code) : KeyEvent(code) {}

		static inline EventType getStaticType() { return key_released; }
		virtual inline EventType getType() const override { return key_released; }
		virtual inline std::string getName() const override { return "key_released"; }
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		inline KeyTypedEvent(KeyCode code) : KeyEvent(code) {}

		static inline EventType getStaticType() { return key_typed; }
		virtual inline EventType getType() const override { return key_typed; }
		virtual inline std::string getName() const override { return "key_typed"; }

		inline uint32_t getUnicodeCharacter() const { return getCode(); }
	};

}
