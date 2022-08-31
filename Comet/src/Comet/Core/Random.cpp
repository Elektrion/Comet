#include "cmt_pch.h"
#include "Random.h"

namespace comet {

	std::mt19937_64 Random::rng(std::random_device{}());
	std::uniform_real_distribution<float> Random::dist_float_0_1(0.0f, 1.0f);

}
