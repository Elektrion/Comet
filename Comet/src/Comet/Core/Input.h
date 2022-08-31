#pragma once

#include "glm/glm.hpp"

#include "Comet/Core/KeyCodes.h"
#include "Comet/Core/MouseCodes.h"

namespace comet {

	class Input {
	public:
		static bool isKeyPressed(KeyCode key);

		static bool isMouseButtonPressed(MouseCode button);

		static glm::vec2 getMousePosition();
	};

}
