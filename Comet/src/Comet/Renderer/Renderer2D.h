#pragma once

#include "Comet/Renderer/Camera.h"
#include "Comet/Renderer/Shader.h"
#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void beginScene(const Ref<Camera>& camera);
		static void endScene();

		static void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);
		static void drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color);
	public:
		static Ref<VertexArray> quad_vertex_array;
		static Ref<Shader> quad_shader;
	};

}
