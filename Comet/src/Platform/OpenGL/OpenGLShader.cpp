#include "cmt_pch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

namespace comet {

	OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string& fragment_source) : id(0) {
		CMT_PROFILE_FUNCTION();

		id = glCreateProgram();

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		const char* source = vertex_source.c_str();
		GLint size = static_cast<GLint>(vertex_source.size());
		glShaderSource(vertex_shader, 1, &source, &size);
		glCompileShader(vertex_shader);

		GLint success = 0;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			GLint length = 0;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
			std::string log;
			log.reserve(length + 1);
			glGetShaderInfoLog(vertex_shader, length, &length, log.data());
			CMT_CORE_ERROR("Vertex shader compilation failed: {0}", log.c_str());
		}

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragment_source.c_str();
		size = static_cast<GLint>(fragment_source.size());
		glShaderSource(fragment_shader, 1, &source, &size);
		glCompileShader(fragment_shader);

		success = 0;
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			GLint length = 0;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
			std::string log;
			log.reserve(length + 1);
			glGetShaderInfoLog(fragment_shader, length, &length, log.data());
			CMT_CORE_ERROR("Fragment shader compilation failed: {0}", log.c_str());
		}

		glAttachShader(id, vertex_shader);
		glAttachShader(id, fragment_shader);
		glLinkProgram(id);

		success = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if(!success) {
			GLint length = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
			std::string log;
			log.reserve(length + 1);
			glGetProgramInfoLog(id, length, &length, log.data());
			CMT_CORE_ERROR("Shader linking failed: {0}", log.c_str());
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	OpenGLShader::~OpenGLShader() {
		CMT_PROFILE_FUNCTION();

		glDeleteProgram(id);
	}

	void OpenGLShader::bind() {
		CMT_PROFILE_FUNCTION();

		glUseProgram(id);
	}

	void OpenGLShader::unBind() {
		CMT_PROFILE_FUNCTION();

		glUseProgram(id);
	}

	void OpenGLShader::setUniformFloat(const std::string& name, float value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1f(id, glGetUniformLocation(id, name.c_str()), value);
#else
		bind();
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
#endif
	}

	void OpenGLShader::setUniformFloat2(const std::string& name, const glm::vec2& value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform2fv(id, glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#else
		bind();
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformFloat3(const std::string& name, const glm::vec3& value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform3fv(id, glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#else
		bind();
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformFloat4(const std::string& name, const glm::vec4& value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform4fv(id, glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#else
		bind();
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformInt(const std::string& name, int value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1i(id, glGetUniformLocation(id, name.c_str()), value);
#else
		bind();
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
#endif
	}

	void OpenGLShader::setuniformIntArray(const std::string& name, uint32_t count, int* value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1iv(id, glGetUniformLocation(id, name.c_str()), count, value);
#else
		bind();
		glUniform1iv(glGetUniformLocation(id, name.c_str()), count, value);
#endif
	}

	void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& value) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
#else
		bind();
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
#endif
	}

}
