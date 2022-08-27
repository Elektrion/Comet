#pragma once

#include "Comet/Renderer/RenderAPI.h"
#include "Comet/Renderer/RenderCommand.h"
#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class Renderer {
	public:
		static inline RenderAPI::API getAPI() {
			return RenderAPI::getAPI();
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array) {
			RenderCommand::drawIndexed(vertex_array);
		}
	};

}
