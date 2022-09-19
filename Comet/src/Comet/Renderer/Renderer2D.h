#pragma once

#include <array>

#include "Comet/Renderer/Buffer.h"
#include "Comet/Renderer/Camera.h"
#include "Comet/Renderer/Shader.h"
#include "Comet/Renderer/Texture.h"
#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void beginScene(const Ref<Camera>& camera);
		static void endScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

		static void drawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	private:
		struct Vertex {
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texture_coords;
			float texture_index;
		};

		static std::array<glm::vec3, 4> getPositions(const glm::vec3& position, const glm::vec2& size);
		static std::array<glm::vec3, 4> getPositions(const glm::vec3& position, const glm::vec2& size, float rotation);

		static float getTextureIndex(const Ref<Texture2D>& texture);
		static float getTextureIndex(const Ref<SubTexture2D>& texture);

		static void putQuad(const std::array<glm::vec3, 4>& positions, const glm::vec4& color,
			const std::array<glm::vec2, 4>& texture_coords = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }, float texture_index = 0.0f);
		static void flushQuads();
	private:
		static uint32_t max_vertices;
		static uint32_t max_quads;
		static uint32_t max_textures;

		static Ref<VertexArray> quad_vertex_array;
		static Ref<VertexBuffer> quad_vertex_buffer;
		static Vertex* quad_vertices;
		static uint32_t quad_index;
		static Ref<Shader> quad_shader;
		static Ref<Texture2D> white_texture;
		static std::vector<Ref<Texture2D>> textures;
	};

}
