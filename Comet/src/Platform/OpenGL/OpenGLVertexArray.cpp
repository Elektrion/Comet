#include "cmt_pch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace comet {

	OpenGLVertexArray::OpenGLVertexArray() : id(0), vertex_buffers{}, index_buffer(nullptr) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glCreateVertexArrays(1, &id);
#else
		glGenVertexArrays(1, &id);
#endif
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		CMT_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &id);
	}

	void OpenGLVertexArray::bind() const {
		CMT_PROFILE_FUNCTION();

		glBindVertexArray(id);
	}

	void OpenGLVertexArray::unBind() const {
		CMT_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) noexcept {
		vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& index_buffer) noexcept {
		this->index_buffer = index_buffer;
	}

}
