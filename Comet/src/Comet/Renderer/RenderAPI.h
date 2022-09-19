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
		virtual inline ~RenderAPI() noexcept = default;

		inline RenderAPI(const RenderAPI&) noexcept = delete;
		inline RenderAPI(const RenderAPI&&) noexcept = delete;
		inline RenderAPI& operator=(const RenderAPI&) noexcept = delete;
		inline RenderAPI& operator=(const RenderAPI&&) noexcept = delete;

		virtual void setClearColor(float r, float g, float b, float a = 1.0f) = 0;
		virtual void clear() = 0;
		virtual void drawIndexed(const Ref<VertexArray>& vertex_array) = 0;
		virtual void drawIndexed(const Ref<VertexArray>& vertex_array, uint32_t count) = 0;
	protected:
		inline RenderAPI() noexcept = default;
	public:
		static void init();
		static inline API getAPI() noexcept { return api; }
		static Scope<RenderAPI> create();
	private:
		static API api;
	};

}
