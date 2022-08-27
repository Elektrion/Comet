#pragma once

#include "Comet/Core/Core.h"

#include "Comet/Renderer/RenderAPI.h"

namespace comet {

	class RenderCommand {
	public:
		static void init();

		static inline void setClearColor(float r, float g, float b, float a = 1.0f) {
			render_api->setClearColor(r, g, b, a);
		}

		static inline void clear() {
			render_api->clear();
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array) {
			render_api->drawIndexed(vertex_array);
		}
	private:
		static Scope<RenderAPI> render_api;
	};

}
