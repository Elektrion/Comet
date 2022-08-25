#pragma once

#include "Comet/Renderer/RenderAPI.h"

namespace comet {

	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void setClearColor(float r, float g, float b, float a = 1.0f) override;
		virtual void clear() override;
	};

}
