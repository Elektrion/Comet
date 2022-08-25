#include "cmt_pch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace comet {

	void OpenGLRenderAPI::setClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderAPI::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

}