#pragma once

#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual void addVertexBuffer(Ref<VertexBuffer> vertex_buffer) override;
		virtual void setIndexBuffer(Ref<IndexBuffer> index_buffer) override;

		virtual Ref<IndexBuffer> getIndexBuffer() const override;
	private:
		uint32_t id;
		std::vector<Ref<VertexBuffer>> vertex_buffers;
		Ref<IndexBuffer> index_buffer;
	};

}
