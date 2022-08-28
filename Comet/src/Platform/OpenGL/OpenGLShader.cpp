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

}
