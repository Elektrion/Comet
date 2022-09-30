#pragma once

#include "Comet/Core/Core.h"

#include "Comet/Renderer/Texture.h"

namespace comet {

	class FrameBuffer {
	public:
		virtual inline ~FrameBuffer() noexcept = default;

		inline FrameBuffer(const FrameBuffer&) noexcept = delete;
		inline FrameBuffer(const FrameBuffer&&) noexcept = delete;
		inline FrameBuffer& operator=(const FrameBuffer&) noexcept = delete;
		inline FrameBuffer& operator=(const FrameBuffer&&) noexcept = delete;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual uint32_t getWidth() const noexcept = 0;
		virtual uint32_t getHeight() const noexcept = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;

		virtual Ref<Texture2D> getColorAttatchment() const noexcept = 0;
	protected:
		inline FrameBuffer() noexcept = default;
	public:
		static Ref<FrameBuffer> create(uint32_t width, uint32_t height);
	};

}
