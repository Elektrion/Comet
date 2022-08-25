#pragma once

#include "Comet/Core/Core.h"

namespace comet {

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	public:
		static Scope<GraphicsContext> createContext(void* window_handle);
	};

}
