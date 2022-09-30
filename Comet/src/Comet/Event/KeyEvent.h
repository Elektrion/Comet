#pragma once

#include "Comet/Core/KeyCodes.h"

#include "Comet/Event/Event.h"

namespace comet {

	class KeyEvent : public Event {
	public:
		virtual inline uint32_t getCategoryFlags() const noexcept override { return input_event | key_event; }
		virtual inline std::string toString() const override { return std::string(getName()) + "(code:" + std::to_string(code) + ")"; }

		inline KeyCode getCode() const noexcept { return code; }
	protected:
		inline KeyEvent(KeyCode code) noexcept : code(code) {}
	private:
		KeyCode code;

		friend class Application;
	};


	class KeyPressedEvent : public KeyEvent {
	public:
		inline KeyPressedEvent(KeyCode code, bool repeated = false) noexcept : KeyEvent(code), repeated(repeated) {}

		static inline EventType getStaticType() noexcept { return key_pressed; }
		virtual inline EventType getType() const noexcept override { return key_pressed; }
		virtual inline std::string_view getName() const noexcept override { return "key_pressed"; }

		inline bool isRepeated() const noexcept { return repeated; }
	private:
		bool repeated;

		friend class Application;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		inline KeyReleasedEvent(KeyCode code) noexcept : KeyEvent(code) {}

		static inline EventType getStaticType() noexcept { return key_released; }
		virtual inline EventType getType() const noexcept override { return key_released; }
		virtual inline std::string_view getName() const noexcept override { return "key_released"; }
	private:
		friend class Application;
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		inline KeyTypedEvent(KeyCode code) noexcept : KeyEvent(code) {}

		static inline EventType getStaticType() noexcept { return key_typed; }
		virtual inline EventType getType() const noexcept override { return key_typed; }
		virtual inline std::string_view getName() const noexcept override { return "key_typed"; }

		inline uint32_t getUnicodeCharacter() const noexcept { return getCode(); }
	private:
		friend class Application;
	};

}
