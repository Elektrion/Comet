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
		return nullptr;
	}

	Ref<Shader> Shader::createFromFile(const std::string& vertex_filename, const std::string& fragment_filename) {
		auto vertex_source = Assets::loadFile("shaders/" + vertex_filename);
		auto fragment_source = Assets::loadFile("shaders/" + fragment_filename);
		return create(
			vertex_source.value_or("#version 410 core\n\nlayout(location = 0) in vec3 a_position;\n\nvoid main() { gl_Position = a_position; }\n"),
			fragment_source.value_or("#version 410 core\n\nout vec4 color;\n\nvoid main() { color = vec4(1.0f, 1.0f, 1.0f, 1.0f); }\n"));
	}

}
