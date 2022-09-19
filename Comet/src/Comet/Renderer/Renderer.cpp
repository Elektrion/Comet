#include "cmt_pch.h"
#include "Renderer.h"

#include "Comet/Renderer/RenderCommand.h"
#include "Comet/Renderer/Renderer2D.h"

namespace comet {

	glm::mat4 Renderer::view_projection = glm::mat4(1.0f);

	void Renderer::init() {
		CMT_PROFILE_FUNCTION();

		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::shutdown() {
		CMT_PROFILE_FUNCTION();

		Renderer2D::shutdown();
	}

	void Renderer::beginScene(const Ref<Camera>& camera) {
		view_projection = camera->getViewProjection();
	}

	void Renderer::endScene() {
		view_projection = glm::mat4(1.0f);
	}

	void Renderer::drawIndexed(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader) {
		CMT_PROFILE_FUNCTION();

		vertex_array->bind();
		shader->bind();
		shader->setUniformMat4("u_view_projection", view_projection);
		RenderCommand::drawIndexed(vertex_array);
	}

	void Renderer::drawIndexed(const Ref<VertexArray>& vertex_array, const Ref<Shader>& shader, uint32_t count) {
		CMT_PROFILE_FUNCTION();

		vertex_array->bind();
		shader->bind();
		shader->setUniformMat4("u_view_projection", view_projection);
		RenderCommand::drawIndexed(vertex_array, count);
	}

}
