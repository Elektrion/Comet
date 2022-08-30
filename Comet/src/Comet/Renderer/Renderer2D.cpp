#include "cmt_pch.h"
#include "Renderer2D.h"

#include "Comet/Renderer/Buffer.h"
#include "Comet/Renderer/Renderer.h"
#include "Comet/Renderer/Texture.h"

namespace comet {

	Ref<VertexArray> Renderer2D::quad_vertex_array = Ref<VertexArray>(nullptr);
	Ref<Shader> Renderer2D::quad_shader = Ref<Shader>(nullptr);

	void Renderer2D::init() {
		quad_vertex_array = VertexArray::create();
		quad_vertex_array->bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f
		};
		Ref<VertexBuffer> vertex_buffer = VertexBuffer::create();
		vertex_buffer->bind();
		vertex_buffer->setData(sizeof(vertices), vertices, BufferUsage::STATIC);
		vertex_buffer->setLayout({
			{ BufferLayout::Type::FLOAT3, "a_position" }
		});
		quad_vertex_array->addVertexBuffer(vertex_buffer);

		uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
		Ref<IndexBuffer> index_buffer = IndexBuffer::create();
		index_buffer->bind();
		index_buffer->setData(6, indices, BufferUsage::STATIC);
		quad_vertex_array->setIndexBuffer(index_buffer);

		quad_shader = Shader::createFromFile("basic_colored.vert.glsl", "basic_colored.frag.glsl");
		quad_shader->bind();
	}

	void Renderer2D::shutdown() {

	}

	void Renderer2D::beginScene(const Ref<Camera>& camera) {
		quad_shader->setUniformMat4("u_view_projection", camera->getViewProjection());
	}

	void Renderer2D::endScene() {
		
	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color) {
		quad_shader->bind();
		glm::mat4 model_transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		quad_shader->setUniformMat4("u_model_transform", model_transform);
		quad_shader->setUniformFloat4("u_color", color);
		Renderer::drawIndexed(quad_vertex_array, quad_shader);
	}

}
