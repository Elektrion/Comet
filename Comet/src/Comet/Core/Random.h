#pragma once

#include <random>

namespace comet {

	class Random {
	public:
		static inline float rand() { return dist_float_0_1(rng); }
		static inline bool randBool() { return dist_float_0_1(rng) < 0.5f; }
	private:
		static std::mt19937_64 rng;
		static std::uniform_real_distribution<float> dist_float_0_1;
	};

}
