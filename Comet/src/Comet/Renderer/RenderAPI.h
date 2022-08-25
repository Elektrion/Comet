#pragma once

#include "Comet/Core/Core.h"

namespace comet {

	class RenderAPI {
	public:
		enum class API {
			NONE, OPENGL
		};
	public:
		virtual void setClearColor(float r, float g, float b, float a = 1.0f) = 0;
		virtual void clear() = 0;
	public:
		static void init();
		static constexpr inline API getAPI() { return api; }
		static Scope<RenderAPI> createRenderAPI();
	private:
		static API api;
	};

}