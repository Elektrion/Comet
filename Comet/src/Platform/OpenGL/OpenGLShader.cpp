#include "cmt_pch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

namespace comet {

	OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string& fragment_source) : id(0) {
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
		glDeleteProgram(id);
	}

	void OpenGLShader::bind() {
		glUseProgram(id);
	}

	void OpenGLShader::unBind() {
		glUseProgram(id);
	}

	void OpenGLShader::setUniformFloat(const std::string& name, float value) {
#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1f(id, glGetUniformLocation(id, name.c_str()), value);
#else
		bind();
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
#endif
	}

	void OpenGLShader::setUniformFloat2(const std::string& name, glm::vec2 value) {
#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1fv(id, glGetUniformLocation(id, name.c_str()), 2, glm::value_ptr(value));
#else
		bind();
		glUniform1fv(glGetUniformLocation(id, name.c_str()), 2, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformFloat3(const std::string& name, glm::vec3 value) {
#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1fv(id, glGetUniformLocation(id, name.c_str()), 3, glm::value_ptr(value));
#else
		bind();
		glUniform1fv(glGetUniformLocation(id, name.c_str()), 3, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformFloat4(const std::string& name, glm::vec4 value) {
#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1fv(id, glGetUniformLocation(id, name.c_str()), 4, glm::value_ptr(value));
#else
		bind();
		glUniform1fv(glGetUniformLocation(id, name.c_str()), 4, glm::value_ptr(value));
#endif
	}

	void OpenGLShader::setUniformInt(const std::string& name, int value) {
#if defined(CMT_USE_OPENGL_4_5)
		glProgramUniform1i(id, glGetUniformLocation(id, name.c_str()), value);
#else
		bind();
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
#endif
	}

}
