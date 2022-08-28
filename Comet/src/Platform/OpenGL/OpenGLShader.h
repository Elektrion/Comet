#pragma once

#include "Comet/Renderer/Shader.h"

namespace comet {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertex_source, const std::string& fragment_source);
		virtual ~OpenGLShader();

		virtual void bind() override;
		virtual void unBind() override;
	private:
		uint32_t id;
	};

}
