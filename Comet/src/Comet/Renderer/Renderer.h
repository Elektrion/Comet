#pragma once

#include "Comet/Renderer/RenderAPI.h"
#include "Comet/Renderer/RenderCommand.h"
#include "Comet/Renderer/Renderer2D.h"
#include "Comet/Renderer/Shader.h"
#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class Renderer {
	public:
		static inline void init() {
			RenderCommand::init();
			Renderer2D::init();
		}

		static inline void shutdown() {
			Renderer2D::shutdown();
		}

		static inline RenderAPI::API getAPI() {
			return RenderAPI::getAPI();
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array, Ref<Shader> shader) {
			vertex_array->bind();
			shader->bind();
			RenderCommand::drawIndexed(vertex_array);
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array, Ref<Shader> shader, uint32_t count) {
			vertex_array->bind();
			shader->bind();
			RenderCommand::drawIndexed(vertex_array, count);
		}
	};

}
