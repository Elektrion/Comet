#include "cmt_pch.h"
#include "Renderer2D.h"

#include "Comet/Renderer/Buffer.h"
#include "Comet/Renderer/Renderer.h"
#include "Comet/Renderer/Texture.h"

namespace comet {

	uint32_t Renderer2D::max_vertices = 0;
	uint32_t Renderer2D::max_quads = 0;
	uint32_t Renderer2D::max_textures = 0;
	Ref<VertexArray> Renderer2D::quad_vertex_array = Ref<VertexArray>(nullptr);
	Ref<VertexBuffer> Renderer2D::quad_vertex_buffer = Ref<VertexBuffer>(nullptr);
	Renderer2D::Vertex* Renderer2D::quad_vertices = nullptr;
	uint32_t Renderer2D::quad_index = 0;
	Ref<Shader> Renderer2D::quad_shader = Ref<Shader>(nullptr);
	Ref<Texture2D> Renderer2D::white_texture = Ref<Texture2D>(nullptr);
	std::vector<Ref<Texture2D>> Renderer2D::textures = {};

	void Renderer2D::init() {
		CMT_PROFILE_FUNCTION();

		max_vertices = 20000;
		max_quads = max_vertices / 4;
		max_textures = 15;

		quad_vertex_array = VertexArray::create();
		quad_vertex_array->bind();

		quad_vertex_buffer = VertexBuffer::create();
		quad_vertex_buffer->bind();
		quad_vertex_buffer->setLayout({
			{ BufferLayout::Type::FLOAT3, "a_position" }, 
			{ BufferLayout::Type::FLOAT4, "a_color" }, 
			{ BufferLayout::Type::FLOAT2, "a_texture_coords" },
			{ BufferLayout::Type::FLOAT, "a_texture_index" }
		});
		quad_vertex_array->addVertexBuffer(quad_vertex_buffer);

		quad_vertices = new Vertex[max_vertices];

		std::vector<uint32_t> indices(max_quads * 6, 0);
		for(uint32_t i = 0; i < max_quads; i++) {
			indices[6 * i + 0] = 4 * i + 0;
			indices[6 * i + 1] = 4 * i + 1;
			indices[6 * i + 2] = 4 * i + 2;
			indices[6 * i + 3] = 4 * i + 0;
			indices[6 * i + 4] = 4 * i + 2;
			indices[6 * i + 5] = 4 * i + 3;
		}
		Ref<IndexBuffer> index_buffer = IndexBuffer::create();
		index_buffer->bind();
		index_buffer->setData(max_quads * 6, indices.data(), BufferUsage::STATIC);
		quad_vertex_array->setIndexBuffer(index_buffer);

		quad_shader = Shader::createFromFile("batched_textured.vert.glsl", "batched_textured.frag.glsl");
		std::array<int, 16> texture_slots = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		quad_shader->setuniformIntArray("samplers", 16, texture_slots.data());

		white_texture = Texture2D::create(1, 1, { 1.0f, 1.0f, 1.0f, 1.0f });

		textures.reserve(max_textures);
	}

	void Renderer2D::shutdown() {
		CMT_PROFILE_FUNCTION();

		max_vertices = 0;
		max_quads = 0;
		max_textures = 0;
		quad_vertex_array.reset();
		quad_vertex_buffer.reset();
		delete[] quad_vertices;
		quad_vertices = nullptr;
		quad_index = 0;
		quad_shader.reset();
		white_texture.reset();
		textures.clear();
	}

	void Renderer2D::beginScene(const Ref<Camera>& camera) {
		CMT_PROFILE_FUNCTION();

		quad_shader->setUniformMat4("u_view_projection", camera->getViewProjection());
	}

	void Renderer2D::endScene() {
		CMT_PROFILE_FUNCTION();

		flushQuads();
	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color) {
		putQuad(position, size, color);
	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, const Ref<Texture2D>& texture, glm::vec4 color) {
		drawQuad({ position.x, position.y, 0.0f }, size, texture, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, const Ref<Texture2D>& texture, glm::vec4 color) {
		auto iter = std::find(textures.begin(), textures.end(), texture);
		if(iter != textures.end()) {
			putQuad(position, size, color, texture->getTextureCoords(), float(iter - textures.begin()) + 1.0f);
			return;
		}

		if(textures.size() == max_textures)
			flushQuads();
		textures.push_back(texture);
		putQuad(position, size, color, texture->getTextureCoords(), float(textures.size())); // size - 1 gives index but adding 1 since the blank texture is always at slot 0
	}

	void Renderer2D::putQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color, std::array<glm::vec2, 4> texture_coords, float texture_index) {
		std::array<glm::vec3, 4> positions = {
			glm::vec3(position.x - size.x / 2.0f, position.y - size.y / 2.0f, position.z),
			glm::vec3(position.x + size.x / 2.0f, position.y - size.y / 2.0f, position.z),
			glm::vec3(position.x + size.x / 2.0f, position.y + size.y / 2.0f, position.z),
			glm::vec3(position.x - size.x / 2.0f, position.y + size.y / 2.0f, position.z)
		};

		quad_vertices[4 * quad_index + 0] = { positions[0], color, texture_coords[0], texture_index };
		quad_vertices[4 * quad_index + 1] = { positions[1], color, texture_coords[1], texture_index };
		quad_vertices[4 * quad_index + 2] = { positions[2], color, texture_coords[2], texture_index };
		quad_vertices[4 * quad_index + 3] = { positions[3], color, texture_coords[3], texture_index };

		quad_index++;
		if(quad_index == max_quads)
			flushQuads();
	}

	void Renderer2D::flushQuads() {
		CMT_PROFILE_FUNCTION();

		quad_vertex_buffer->setData(quad_index * 4 * sizeof(Vertex), quad_vertices, BufferUsage::DYNAMIC);
		white_texture->bind(0);
		for(uint32_t i = 0; i < uint32_t(textures.size()); i++)
			textures[i]->bind(i + 1);
		Renderer::drawIndexed(quad_vertex_array, quad_shader, quad_index * 6);
		quad_index = 0;
		textures.clear();
	}

}
