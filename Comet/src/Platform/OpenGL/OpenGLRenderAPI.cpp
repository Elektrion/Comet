#include "cmt_pch.h"
#include "OpenGLRenderAPI.h"

#include "glad/glad.h"

namespace comet {

	void OpenGLRenderAPI::setClearColor(float r, float g, float b, float a) {
		CMT_PROFILE_FUNCTION();

		glClearColor(r, g, b, a);
	}

	void OpenGLRenderAPI::clear() {
		CMT_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertex_array) {
		CMT_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, vertex_array->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertex_array, uint32_t count) {
		CMT_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

}
