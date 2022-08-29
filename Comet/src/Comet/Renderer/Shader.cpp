#include "cmt_pch.h"
#include "Shader.h"

#include "Comet/Core/Assets.h"

#include "Comet/Renderer/RenderAPI.h"

#if defined(CMT_PLATFORM_WINDOWS)
#include "Platform/OpenGL/OpenGLShader.h"
#elif defined(CMT_PLATFORM_MACOS)
#include "Platform/OpenGL/OpenGLShader.h"
#else
#error "Platform not supported!"
#endif

namespace comet {

	Ref<Shader> Shader::create(const std::string& vertex_source, const std::string& fragment_source) {
#if defined(CMT_PLATFORM_WINDOWS)
		switch(RenderAPI::getAPI()) {
			case RenderAPI::API::NONE:
				CMT_CORE_ASSERT(false, "No render api was set!");
				break;
			case RenderAPI::API::OPENGL:
				return createRef<OpenGLShader>(vertex_source, fragment_source);
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
				return createRef<OpenGLShader>(vertex_source, fragment_source);
			default:
				CMT_CORE_ASSERT(false, "Render api was set to an invalid value!");
				break;
		}
#endif
		return Ref<OpenGLShader>(nullptr);
	}

	Ref<Shader> Shader::createFromFile(const std::string& vertex_filename, const std::string& fragment_filename) {
		return create(Assets::loadFile("shaders/" + vertex_filename), Assets::loadFile("shaders/" + fragment_filename));
	}

}
