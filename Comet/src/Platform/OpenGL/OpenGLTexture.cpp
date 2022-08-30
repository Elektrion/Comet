#include "cmt_pch.h"
#include "OpenGLTexture.h"

#include "glad/glad.h"

#include "stb/stb_image.h"

namespace comet {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filename, bool pixelate) : id(0), width(0), height(0) {
		int width = 0;
		int height = 0;
		int channels = 0;
		unsigned char* pixels = stbi_load(filename.c_str(), &width, &height, &channels, 0);

		if(!pixels) {
			CMT_CORE_ERROR("Failed to lead image file \"{0}\"", filename);
			this->width = 1;
			this->height = 1;
			unsigned char pixel[4] = { 255, 255, 255, 255 };
			initOpenGLTexture(4, pixel, true);
			return;
		}
		if(channels < 3) {
			CMT_CORE_ERROR("Too few channels specified for texture creation: {0}. Has to be at least 3.", channels);
			channels = 3;
		}
		if(channels > 4) {
			CMT_CORE_ERROR("Too many channels specified for texture creation: {0}. Has to be at most 4.", channels);
			channels = 4;
		}
		this->width = uint32_t(width);
		this->height = uint32_t(height);
		initOpenGLTexture(channels, pixels, pixelate);
		stbi_image_free(pixels);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t channels, const unsigned char* const pixels, bool pixelate) : id(0), width(width), height(width) {
		if(channels < 3) {
			CMT_CORE_ERROR("Too few channels specified for texture creation: {0}. Has to be at least 3.", channels);
			channels = 3;
		}
		if(channels > 4) {
			CMT_CORE_ERROR("Too many channels specified for texture creation: {0}. Has to be at most 4.", channels);
			channels = 4;
		}
		initOpenGLTexture(channels, pixels, pixelate);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color, bool pixelate) : id(0), width(width), height(height) {
		unsigned char pixels[4] = {
			static_cast<unsigned char>(glm::clamp(color.r, 0.0f, 1.0f) * 255), 
			static_cast<unsigned char>(glm::clamp(color.g, 0.0f, 1.0f) * 255),
			static_cast<unsigned char>(glm::clamp(color.b, 0.0f, 1.0f) * 255), 
			static_cast<unsigned char>(glm::clamp(color.a, 0.0f, 1.0f) * 255)
		};
		initOpenGLTexture(4, pixels, pixelate);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture2D::bind(uint32_t slot) {
#if defined(CMT_USE_OPENGL_4_5)
		glBindTextureUnit(slot, id);
#else
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
#endif
	}

	void OpenGLTexture2D::unBind(uint32_t slot) {
#if defined(CMT_USE_OPENGL_4_5)
		glBindTextureUnit(slot, 0);
#else
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
#endif
	}

	void OpenGLTexture2D::initOpenGLTexture(uint32_t channels, const unsigned char* const pixels, bool pixelate) {
#if defined(CMT_USE_OPENGL_4_5)
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, pixelate ? GL_NEAREST : GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, pixelate ? GL_NEAREST : GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureStorage2D(id, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(id, 0, 0, 0, width, height, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
#else
		glGenTextures(1, &id);
		bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelate ? GL_NEAREST : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelate ? GL_NEAREST : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
#endif
	}

}
