#pragma once

#include "Comet/Renderer/Camera.h"
#include "Comet/Renderer/RenderAPI.h"
#include "Comet/Renderer/Shader.h"
#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class Renderer {
	public:
		static void init();
		static void shutdown();

		static inline RenderAPI::API getAPI() {
			return RenderAPI::getAPI();
		}

		static void beginScene(const Ref<Camera>& camera);
		static void endScene();

		static void drawIndexed(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader);
		static void drawIndexed(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader, uint32_t count);
	private:
		static glm::mat4 view_projection;
	};

}
