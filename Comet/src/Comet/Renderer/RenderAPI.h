#pragma once

#include "Comet/Core/Core.h"

#include "Comet/Renderer/VertexArray.h"

namespace comet {

	class RenderAPI {
	public:
		enum class API {
			NONE, OPENGL
		};
	public:
		virtual ~RenderAPI() = default;

		virtual void setClearColor(float r, float g, float b, float a = 1.0f) = 0;
		virtual void clear() = 0;
		virtual void drawIndexed(Ref<VertexArray> vertex_array) = 0;
	public:
		static void init();
		static inline API getAPI() { return api; }
		static Scope<RenderAPI> create();
	private:
		static API api;
	};

}
