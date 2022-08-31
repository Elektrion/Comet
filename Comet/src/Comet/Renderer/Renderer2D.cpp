#include "cmt_pch.h"
#include "Renderer2D.h"

#include "Comet/Renderer/Buffer.h"
#include "Comet/Renderer/Renderer.h"
#include "Comet/Renderer/Texture.h"

namespace comet {

	Ref<VertexArray> Renderer2D::quad_vertex_array = Ref<VertexArray>(nullptr);
	Ref<VertexBuffer> Renderer2D::quad_vertex_buffer = Ref<VertexBuffer>(nullptr);
	Ref<Shader> Renderer2D::quad_shader = Ref<Shader>(nullptr);
	Ref<Texture2D> Renderer2D::white_texture = Ref<Texture2D>(nullptr);
	std::array<Renderer2D::Vertex, 4> Renderer2D::quad_vertices = {};

	void Renderer2D::init() {
		quad_vertex_array = VertexArray::create();
		quad_vertex_array->bind();

		quad_vertices[0] = { { -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } };
		quad_vertices[1] = { {  0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } };
		quad_vertices[2] = { {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } };
		quad_vertices[3] = { { -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } };
		quad_vertex_buffer = VertexBuffer::create();
		quad_vertex_buffer->bind();
		quad_vertex_buffer->setData(4 * sizeof(Vertex), quad_vertices.data(), BufferUsage::DYNAMIC);
		quad_vertex_buffer->setLayout({
			{ BufferLayout::Type::FLOAT3, "a_position" }, 
			{ BufferLayout::Type::FLOAT4, "a_color" }, 
			{ BufferLayout::Type::FLOAT2, "a_texture_coords" }
		});
		quad_vertex_array->addVertexBuffer(quad_vertex_buffer);

		uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
		Ref<IndexBuffer> index_buffer = IndexBuffer::create();
		index_buffer->bind();
		index_buffer->setData(6, indices, BufferUsage::STATIC);
		quad_vertex_array->setIndexBuffer(index_buffer);

		quad_shader = Shader::createFromFile("basic_textured.vert.glsl", "basic_textured.frag.glsl");

		white_texture = Texture2D::create(1, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer2D::shutdown() {

	}

	void Renderer2D::beginScene(const Ref<Camera>& camera) {
		quad_shader->setUniformMat4("u_view_projection", camera->getViewProjection());
	}

	void Renderer2D::endScene() {
		
	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
		drawQuad({ position.x, position.y, 0.0f }, size, white_texture, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color) {
		drawQuad(position, size, white_texture, color);
	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, const Ref<Texture2D>& texture, glm::vec4 color) {
		drawQuad({ position.x, position.y, 0.0f }, size, texture, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, const Ref<Texture2D>& texture, glm::vec4 color) {
		quad_vertices[0].color = color;
		quad_vertices[1].color = color;
		quad_vertices[2].color = color;
		quad_vertices[3].color = color;
		quad_vertex_buffer->setData(4 * sizeof(Vertex), quad_vertices.data(), BufferUsage::DYNAMIC);
		glm::mat4 model_transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		quad_shader->setUniformMat4("u_model_transform", model_transform);
		texture->bind(0);
		quad_shader->setUniformInt("sampler", 0);
		Renderer::drawIndexed(quad_vertex_array, quad_shader);
	}

}
