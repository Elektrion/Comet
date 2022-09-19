#pragma once

#include "Comet/Core/Math.h"

namespace comet {

	class Camera {
	public:
		virtual inline ~Camera() noexcept = default;

		inline Camera(const Camera&) noexcept = delete;
		inline Camera(const Camera&&) noexcept = delete;
		inline Camera& operator=(const Camera&) noexcept = delete;
		inline Camera& operator=(const Camera&&) noexcept = delete;

		virtual glm::mat4 getViewProjection() const noexcept = 0;
	protected:
		inline Camera() noexcept = default;
	};

}
