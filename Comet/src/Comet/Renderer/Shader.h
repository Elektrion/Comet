#pragma once

#include <string>

#include "glm/glm.hpp"

#include "Comet/Core/Core.h"

namespace comet {

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void setUniformFloat(const std::string& name, float value) = 0;
		virtual void setUniformFloat2(const std::string& name, glm::vec2 value) = 0;
		virtual void setUniformFloat3(const std::string& name, glm::vec3 value) = 0;
		virtual void setUniformFloat4(const std::string& name, glm::vec4 value) = 0;

		virtual void setUniformInt(const std::string& name, int value) = 0;
	public:
		static Ref<Shader> create(const std::string& vertex_source, const std::string& fragment_source);
		static Ref<Shader> createFromFile(const std::string& vertex_filename, const std::string& fragment_filename);
	};

}
