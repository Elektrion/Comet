#pragma once

#include "Comet/Renderer/Shader.h"

namespace comet {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertex_source, const std::string& fragment_source);
		virtual ~OpenGLShader();

		virtual void bind() override;
		virtual void unBind() override;

		virtual void setUniformFloat(const std::string& name, float value) override;
		virtual void setUniformFloat2(const std::string& name, glm::vec2 value) override;
		virtual void setUniformFloat3(const std::string& name, glm::vec3 value) override;
		virtual void setUniformFloat4(const std::string& name, glm::vec4 value) override;

		virtual void setUniformInt(const std::string& name, int value) override;

		virtual void setUniformMat4(const std::string& name, glm::mat4 value) override;
	private:
		uint32_t id;
	};

}
