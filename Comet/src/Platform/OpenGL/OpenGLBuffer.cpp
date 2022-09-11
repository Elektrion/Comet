#include "cmt_pch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace comet {

	static std::map<BufferLayout::Type, GLenum> getGLType = {
		{ BufferLayout::Type::FLOAT, GL_FLOAT }, 
		{ BufferLayout::Type::FLOAT2, GL_FLOAT }, 
		{ BufferLayout::Type::FLOAT3, GL_FLOAT }, 
		{ BufferLayout::Type::FLOAT4, GL_FLOAT }
	};

	OpenGLVertexBuffer::OpenGLVertexBuffer() : id(0) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glCreateBuffers(1, &id);
#else
		glGenBuffers(1, &id);
#endif
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		CMT_PROFILE_FUNCTION();

		glDeleteBuffers(1, &id);
	}

	void OpenGLVertexBuffer::bind() {
		CMT_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void OpenGLVertexBuffer::unBind() {
		CMT_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::setData(uint32_t size, void* data, BufferUsage usage) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		switch(usage) {
			default:
			case BufferUsage::STATIC:
				glNamedBufferData(id, size, data, GL_STATIC_DRAW);
				break;
			case BufferUsage::DYNAMIC:
				glNamedBufferData(id, size, data, GL_DYNAMIC_DRAW);
				break;
		}
#else
		bind();
		switch(usage) {
			default:
			case BufferUsage::STATIC:
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
				break;
			case BufferUsage::DYNAMIC:
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
				break;
		}
#endif
	}

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout) {
		CMT_PROFILE_FUNCTION();

		bind();
		GLuint index = 0;
		const char* offset = 0;
		for(const auto& element : layout) {
			glVertexAttribPointer(index, element.type.getComponentCount(), getGLType[element.type], GL_FALSE, layout.getByteCount(), static_cast<const void*>(offset));
			glEnableVertexAttribArray(index);
			index++;
			offset += element.type.getByteCount();
		}
	}


	OpenGLIndexBuffer::OpenGLIndexBuffer() : id(0), count(0) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glCreateBuffers(1, &id);
#else
		glGenBuffers(1, &id);
#endif
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		CMT_PROFILE_FUNCTION();

		glDeleteBuffers(1, &id);
	}

	void OpenGLIndexBuffer::bind() {
		CMT_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void OpenGLIndexBuffer::unBind() {
		CMT_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::getCount() const {
		return count;
	}

	void OpenGLIndexBuffer::setData(uint32_t count, void* data, BufferUsage usage) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		this->count = count;
		switch(usage) {
			default:
			case BufferUsage::STATIC:
				glNamedBufferData(id, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
				break;
			case BufferUsage::DYNAMIC:
				glNamedBufferData(id, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
				break;
		}
#else
		bind();
		this->count = count;
		switch(usage) {
			default:
			case BufferUsage::STATIC:
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
				break;
			case BufferUsage::DYNAMIC:
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
				break;
		}
#endif
	}

}
