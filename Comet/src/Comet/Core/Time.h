#pragma once

#include <chrono>

namespace comet {

	class Timestep {
	public:
		inline Timestep(float dt) noexcept : dt(dt) {}
		inline operator float() const noexcept { return dt; }
	private:
		float dt;
	};

	class Time {
	public:
		template<typename T = std::ratio<1i64, 1i64>> static inline Timestep mark(bool peek = false)
			noexcept(noexcept(std::chrono::duration_cast<std::chrono::duration<float, T>>(std::declval<const std::chrono::high_resolution_clock::time_point::duration&>()))) 
			requires(std::_Is_ratio_v<T>) {

			static std::chrono::high_resolution_clock::time_point last;

			auto temp = std::chrono::high_resolution_clock::now();
			Timestep dt = std::chrono::duration_cast<std::chrono::duration<float, T>>(temp - last).count();
			if(!peek) last = temp;
			return dt;
		}

		template<typename T = std::ratio<1i64, 1i64>> static inline Timestep peek() noexcept(noexcept(Time::mark<T>)) requires(std::_Is_ratio_v<T>) {
			return mark<T>(true);
		}

		template<typename T = std::ratio<1i64, 1i64>> static inline float currentTime() 
			noexcept(noexcept(std::chrono::duration_cast<std::chrono::duration<float, T>>(std::declval<const std::chrono::high_resolution_clock::time_point::duration&>()))) 
			requires(std::_Is_ratio_v<T>) {
			return std::chrono::duration_cast<std::chrono::duration<float, T>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	};

}
