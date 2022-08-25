#pragma once

#include <string>
#include <ostream>
#include <functional>

namespace comet {

	enum EventType {
		window_closed, window_resized, window_minimized, window_maximized, 
		key_pressed, key_released, key_typed, 
		mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled
	};

	enum EventCategory : uint32_t {
		window_event =        1, 
		input_event =         2, 
		key_event =           4, 
		mouse_event =         8, 
		mouse_button_event = 16
	};


	class Event {
	public:
		
		virtual ~Event() = default;

		// EventType::getStaticType()
		virtual EventType getType() const = 0;
		virtual std::string getName() const = 0;
		virtual uint32_t getCategoryFlags() const = 0;
		virtual inline std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }
		inline void setHandled() { handled = true; }
		inline bool isHandled() const { return handled; }
	protected:
		inline Event() : handled(false) {}
	private:
		bool handled;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		os << e.toString();
		return os;
	}


	template<typename T> using EventFn = std::function<bool(T&)>;

	class EventDispatcher {
	public:
		inline EventDispatcher(Event& e) : e(e) {}

		template<typename T> inline bool dispatch(EventFn<T> func) const requires(std::is_base_of_v<Event, T>) {
			if((e.getType() == T::getStaticType()) && !e.isHandled())
				if(func(static_cast<T&>(e)))
					e.setHandled();
			return e.isHandled();
		}
	private:
		Event& e;
	};

}
