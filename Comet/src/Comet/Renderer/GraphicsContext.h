#pragma once

#include "Comet/Core/Core.h"

namespace comet {

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0;
		virtual void setViewPort(int32_t x, int32_t y, uint32_t width, uint32_t height) = 0;
	public:
		static Scope<GraphicsContext> create(void* window_handle);
	};

}
