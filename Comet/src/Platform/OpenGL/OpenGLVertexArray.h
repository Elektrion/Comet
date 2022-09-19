#pragma once

#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unBind() const override;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) noexcept override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& index_buffer) noexcept override;

		virtual inline const Ref<IndexBuffer>& getIndexBuffer() const noexcept override { return index_buffer; }
	private:
		uint32_t id;
		std::vector<Ref<VertexBuffer>> vertex_buffers;
		Ref<IndexBuffer> index_buffer;
	};

}
