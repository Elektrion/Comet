#pragma once

#include "Comet/Renderer/Buffer.h"

namespace comet {

	class VertexArray {
	public:
		virtual inline ~VertexArray() noexcept = default;

		inline VertexArray(const VertexArray&) noexcept = delete;
		inline VertexArray(const VertexArray&&) noexcept = delete;
		inline VertexArray& operator=(const VertexArray&) noexcept = delete;
		inline VertexArray& operator=(const VertexArray&&) noexcept = delete;

		virtual void bind() const = 0;
		virtual void unBind() const = 0;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) noexcept = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& index_buffer) noexcept = 0;

		virtual const Ref<IndexBuffer>& getIndexBuffer() const noexcept = 0;
	protected:
		inline VertexArray() noexcept = default;
	public:
		static Ref<VertexArray> create();
	};

}
