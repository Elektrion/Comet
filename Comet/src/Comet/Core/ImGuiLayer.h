#pragma once

#include <array>

#include "Comet/Core/Layer.h"

#include "Comet/Renderer/FrameBuffer.h"

namespace comet {

	class ImGuiLayer : public Layer {
	public:
		virtual void onAttatch() override;
		virtual void onDetatch() override;

		virtual void onUpdate(Timestep dt) override;
		virtual void onEvent(Event& e) override;

		std::array<uint32_t, 4> beginImGui();
		void endImGui();

		void enableDockspace();
	private:
		Ref<FrameBuffer> viewport_framebuffer;
		bool enable_dockspace;
	};

}
