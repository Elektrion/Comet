#include "cmt_pch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "Comet/Core/Application.h"
#include "Comet/Core/Core.h"

namespace comet {

	void ImGuiLayer::onAttatch() {
		viewport_framebuffer = FrameBuffer::create(1280, 720);
	}

	void ImGuiLayer::onDetatch() {
		viewport_framebuffer = nullptr;
		enable_dockspace = false;
	}

	void ImGuiLayer::onUpdate(Timestep dt) {}

	void ImGuiLayer::onEvent(Event& e) {}

	std::array<uint32_t, 4> ImGuiLayer::beginImGui() {
		CMT_PROFILE_FUNCTION();

		if(enable_dockspace) {
			// setup dockspace
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Comet DockSpace Container", nullptr, window_flags);
			ImGui::PopStyleVar();
			ImGui::PopStyleVar(2);

			ImGuiID dockspace_id = ImGui::GetID("Comet");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

			if(ImGui::BeginMenuBar()) {
				if(ImGui::BeginMenu("File")) {
					if(ImGui::MenuItem("Close", nullptr))
						Application::get()->close();

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			// begin main viewport
			ImGui::SetNextWindowDockID(ImGui::GetID("Comet"), ImGuiCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
			ImGui::Begin("Main Viewport");
			ImGui::PopStyleVar();

			auto [width, height] = ImGui::GetContentRegionAvail();
			if(uint32_t(width) != viewport_framebuffer->getWidth() || uint32_t(height) != viewport_framebuffer->getHeight()) {
				Application::get()->postEvent(createRef<WindowResizedEvent>(uint32_t(width), uint32_t(height)));
				viewport_framebuffer->resize(uint32_t(width), uint32_t(height));
			}
			viewport_framebuffer->bind();

			auto [x, y] = ImGui::GetWindowPos();
			return { uint32_t(x), uint32_t(y), uint32_t(width), uint32_t(height) };
		}

		return { 0, 0, 0, 0 };
	}

	void ImGuiLayer::endImGui() {
		CMT_PROFILE_FUNCTION();

		if(enable_dockspace) {
			// end main viewport
			viewport_framebuffer->unBind();
			ImGui::Image(reinterpret_cast<void*>(uint64_t(viewport_framebuffer->getColorAttatchment()->getNativeId())),
				{ float(viewport_framebuffer->getWidth()), float(viewport_framebuffer->getHeight()) }, { 0.0f, 1.0f }, { 1.0f, 0.0f });
			ImGui::End();

			// end dockspace
			ImGui::End();
		}
	}

	void ImGuiLayer::enableDockspace() {
		enable_dockspace = true;
	}

}
