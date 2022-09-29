#include "cmt_pch.h"
#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"

namespace comet {

	void OpenGLFrameBufferColorAttatchment::bind(uint32_t slot) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glBindTextureUnit(slot, id);
#else
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
#endif
	}

	void OpenGLFrameBufferColorAttatchment::unBind(uint32_t slot) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glBindTextureUnit(slot, 0);
#else
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
#endif
	}


	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height) : id(0), depth_buffer_id(0), color_attatchment(createRef<OpenGLFrameBufferColorAttatchment>(0, width, height)) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		glCreateFramebuffers(1, &id);
#else
		glGenFramebuffers(1, &id);
#endif
		initAttatchments(width, height);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		CMT_PROFILE_FUNCTION();

		destroyAttatchments();
		glDeleteFramebuffers(1, &id);
	}

	void OpenGLFrameBuffer::bind() {
		CMT_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void OpenGLFrameBuffer::unBind() {
		CMT_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::resize(uint32_t width, uint32_t height) {
		destroyAttatchments();
		initAttatchments(width, height);
	}

	Ref<Texture2D> OpenGLFrameBuffer::getColorAttatchment() const noexcept {
		return color_attatchment;
	}

	void OpenGLFrameBuffer::initAttatchments(uint32_t width, uint32_t height) {
		CMT_PROFILE_FUNCTION();

#if defined(CMT_USE_OPENGL_4_5)
		color_attatchment->width = width;
		color_attatchment->height = height;
		glCreateTextures(GL_TEXTURE_2D, 1, &(color_attatchment->id));

		glTextureParameteri(color_attatchment->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(color_attatchment->id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(color_attatchment->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(color_attatchment->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureStorage2D(color_attatchment->id, 1, GL_RGBA8, width, height);

		glNamedFramebufferTexture(id, GL_COLOR_ATTACHMENT0, color_attatchment->id, 0);


		glCreateTextures(GL_TEXTURE_2D, 1, &depth_buffer_id);

		glTextureParameteri(depth_buffer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(depth_buffer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(depth_buffer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(depth_buffer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureStorage2D(depth_buffer_id, 1, GL_DEPTH_COMPONENT, width, height);

		glNamedFramebufferTexture(id, GL_DEPTH_ATTACHMENT, depth_buffer_id, 0);
#else
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		color_attatchment->width = width;
		color_attatchment->height = height;
		glGenTextures(1, &(color_attatchment->id));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, color_attatchment->id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attatchment->id, 0);


		glGenTextures(1, &depth_buffer_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depth_buffer_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_buffer_id, 0);

		CMT_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Incomplete framebuffer");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
	}

	void OpenGLFrameBuffer::destroyAttatchments() {
		CMT_PROFILE_FUNCTION();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		glDeleteTextures(1, &(color_attatchment->id));
		color_attatchment->id = 0;
		color_attatchment->width = 0;
		color_attatchment->height = 0;

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
		glDeleteTextures(1, &depth_buffer_id);
		depth_buffer_id = 0;
	}

}
