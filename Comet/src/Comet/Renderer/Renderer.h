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
			CMT_PROFILE_FUNCTION();

			RenderCommand::init();
			Renderer2D::init();
		}

		static inline void shutdown() {
			CMT_PROFILE_FUNCTION();

			Renderer2D::shutdown();
		}

		static inline RenderAPI::API getAPI() {
			return RenderAPI::getAPI();
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array, Ref<Shader> shader) {
			CMT_PROFILE_FUNCTION();

			vertex_array->bind();
			shader->bind();
			RenderCommand::drawIndexed(vertex_array);
		}

		static inline void drawIndexed(Ref<VertexArray> vertex_array, Ref<Shader> shader, uint32_t count) {
			CMT_PROFILE_FUNCTION();

			vertex_array->bind();
			shader->bind();
			RenderCommand::drawIndexed(vertex_array, count);
		}
	};

}
