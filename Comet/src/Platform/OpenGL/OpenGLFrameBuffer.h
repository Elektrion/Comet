#pragma once

#include "Comet/Renderer/FrameBuffer.h"

namespace comet {

	class OpenGLFrameBufferColorAttatchment : public Texture2D {
	public:
		inline OpenGLFrameBufferColorAttatchment(uint32_t id, uint32_t width, uint32_t height) noexcept : id(id), width(width), height(height) {}

		virtual void bind(uint32_t slot = 0);
		virtual void unBind(uint32_t slot = 0);

		virtual inline uint32_t getNativeId() const noexcept { return id; }

		virtual inline uint32_t getWidth() const noexcept { return width; };
		virtual inline uint32_t getHeight() const noexcept { return height; };

		virtual inline glm::vec2 getTextureCoordsBottomLeft() const noexcept override { return { 0.0f, 0.0f }; }
		virtual inline glm::vec2 getTextureCoordsTopRight() const noexcept override { return { 1.0f, 1.0f }; }
		virtual inline std::array<glm::vec2, 4> getTextureCoords() const noexcept override { return { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }; }
	private:
		uint32_t id;
		uint32_t width;
		uint32_t height;
		
		friend class OpenGLFrameBuffer;
	};

	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height);
		virtual ~OpenGLFrameBuffer();

		virtual void bind() override;
		virtual void unBind() override;

		virtual void resize(uint32_t width, uint32_t height) override;

		virtual Ref<Texture2D> getColorAttatchment() const noexcept;
	private:
		void initAttatchments(uint32_t width, uint32_t height);
		void destroyAttatchments();
	private:
		uint32_t id;
		uint32_t depth_buffer_id;
		Ref<OpenGLFrameBufferColorAttatchment> color_attatchment;
	};

}
