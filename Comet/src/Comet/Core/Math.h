#pragma once

#include <random>
#include <functional>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace comet {

	class Math {
	public:
		template<typename T> static inline const T& min(const T& lhs, const T& rhs) {
			return lhs < rhs ? lhs : rhs;
		}

		template<typename T> static inline const T& max(const T& lhs, const T& rhs) {
			return lhs > rhs ? lhs : rhs;
		}


		static inline float rand() {
			static std::mt19937_64 rng(std::random_device{}());
			static std::uniform_real_distribution<float> dist_float_0_1(0.0f, 1.0f);

			return dist_float_0_1(rng);
		}

		static inline bool randBool() { return rand() < 0.5f; }


		template<typename T> static inline T sin(const T& x) {
			return std::sin(x);
		}

		template<typename T> static inline T cos(const T& x) {
			return std::cos(x);
		}
	};

}
