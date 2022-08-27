#pragma once

#include "Comet/Renderer/Buffer.h"

namespace comet {

	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unBind() const = 0;

		virtual void addVertexBuffer(Ref<VertexBuffer> vertex_buffer) = 0;
		virtual void setIndexBuffer(Ref<IndexBuffer> index_buffer) = 0;

		virtual Ref<IndexBuffer> getIndexBuffer() const = 0;
	public:
		static Ref<VertexArray> create();
	};

}
