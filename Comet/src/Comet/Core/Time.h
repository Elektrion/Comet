#pragma once

class Timestep {
public:
	constexpr inline Timestep(float dt) : dt(dt) {}
	constexpr inline operator float() const { return dt; }
private:
	float dt;
};