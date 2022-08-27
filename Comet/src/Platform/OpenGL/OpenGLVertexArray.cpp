#include "cmt_pch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace comet {

	OpenGLVertexArray::OpenGLVertexArray() : id(0), vertex_buffers{}, index_buffer(nullptr) {
#if defined(CMT_USE_OPENGL_4_5)
		glCreateVertexArrays(1, &id);
#else
		glGenVertexArrays(1, &id);
#endif
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &id);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(id);
	}

	void OpenGLVertexArray::unBind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer> vertex_buffer) {
		vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer> index_buffer) {
		this->index_buffer = index_buffer;
	}

	Ref<IndexBuffer> OpenGLVertexArray::getIndexBuffer() const {
		return index_buffer;
	}

}
