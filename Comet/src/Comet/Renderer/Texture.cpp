#include "cmt_pch.h"
#include "Texture.h"

#include "Comet/Core/Assets.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLTexture.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "Platform/OpenGL/OpenGLTexture.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

	Ref<Texture2D> Texture2D::create(const std::string& filename, bool pixelate) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(Assets::getAssetPath("textures/" + filename), pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#elif defined(CMT_PLATFORM_MACOS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(Assets::getAssetPath("textures/" + filename), pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height, uint32_t channels, const unsigned char* const pixels, bool pixelate) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(width, height, channels, pixels, pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#elif defined(CMT_PLATFORM_MACOS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(width, height, channels, pixels, pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height, glm::vec4 color, bool pixelate) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(width, height, color, pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#elif defined(CMT_PLATFORM_MACOS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLTexture2D>(width, height, color, pixelate);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return nullptr;
	}

}
