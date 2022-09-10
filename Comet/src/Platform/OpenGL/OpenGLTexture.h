#pragma once

#include "Comet/Renderer/Texture.h"

namespace comet {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& filename, bool pixelate = false);
		OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t channels, const unsigned char* const pixels, bool pixelate = false);
		OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color, bool pixelate = false);
		virtual ~OpenGLTexture2D();

		virtual void bind(uint32_t slot = 0) override;
		virtual void unBind(uint32_t slot = 0) override;

		virtual inline uint32_t getWidth() const override { return width; }
		virtual inline uint32_t getHeight() const override { return height; }

		virtual inline glm::vec2 getTextureCoordsBottomLeft() const override { return { 0.0f, 0.0f }; }
		virtual inline glm::vec2 getTextureCoordsTopRight() const override { return { 1.0f, 1.0f }; }
		virtual inline std::array<glm::vec2, 4> getTextureCoords() const override { return { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }; }
	private:
		void initOpenGLTexture(uint32_t channels, const unsigned char* const pixels, bool pixelate);
	private:
		uint32_t id;
		uint32_t width;
		uint32_t height;
	};

}
