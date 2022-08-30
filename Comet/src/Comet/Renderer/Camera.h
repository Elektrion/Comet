#pragma once

#include "glm/glm.hpp"

#include "Comet/Core/Core.h"

namespace comet {

	class Camera {
	public:
		virtual ~Camera() = default;

		virtual glm::mat4 getViewProjection() const = 0;
	};

}
