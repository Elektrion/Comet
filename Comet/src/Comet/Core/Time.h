#pragma once

namespace comet {

	class Timestep {
	public:
		inline Timestep(float dt) : dt(dt) {}
		inline operator float() const { return dt; }
	private:
		float dt;
	};

}
