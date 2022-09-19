#pragma once

#include "Comet/Renderer/Buffer.h"

namespace comet {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer();
		virtual ~OpenGLVertexBuffer();

		virtual void bind() override;
		virtual void unBind() override;

		virtual void setData(uint32_t size, void* data, BufferUsage usage) override;

		virtual void setLayout(const BufferLayout& layout) override;
	private:
		uint32_t id;
	};


	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer();

		virtual void bind() override;
		virtual void unBind() override;

		virtual uint32_t getCount() const noexcept override;

		virtual void setData(uint32_t count, void* data, BufferUsage usage) override;
	private:
		uint32_t id;
		uint32_t count;
	};

}
