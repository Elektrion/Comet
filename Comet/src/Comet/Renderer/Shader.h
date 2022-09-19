#pragma once

#include <string>

#include "Comet/Core/Core.h"
#include "Comet/Core/Math.h"

namespace comet {

	class Shader {
	public:
		virtual inline ~Shader() noexcept = default;

		inline Shader(const Shader&) noexcept = delete;
		inline Shader(const Shader&&) noexcept = delete;
		inline Shader& operator=(const Shader&) noexcept = delete;
		inline Shader& operator=(const Shader&&) noexcept = delete;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual void setUniformFloat(const std::string& name, float value) = 0;
		virtual void setUniformFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void setUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setUniformFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void setUniformInt(const std::string& name, int value) = 0;
		virtual void setuniformIntArray(const std::string& name, uint32_t count, int* value) = 0;

		virtual void setUniformMat4(const std::string& name, const glm::mat4& value) = 0;
	protected:
		inline Shader() noexcept = default;
	public:
		static Ref<Shader> create(const std::string& vertex_source, const std::string& fragment_source);
		static Ref<Shader> createFromFile(const std::string& vertex_filename, const std::string& fragment_filename);
	};

}
