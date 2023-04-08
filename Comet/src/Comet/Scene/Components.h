#pragma once

#include "imgui.h"

#include "Comet/Core/Core.h"
#include "Comet/Core/Math.h"

#include "Comet/Renderer/Texture.h"

#include "Comet/Scene/Scene.h"


namespace comet::components {

	void renderImGuiComponent(Entity entity, auto& component) = delete;

	struct Transform {
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
	};

	struct Sprite {
		Ref<Texture2D> texture = nullptr;
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct Name {
		std::string name = "unnamed";
	};

	template<>
	inline void renderImGuiComponent(Entity entity, Transform& component) {
		ImGui::PushItemWidth(200.0f);

		ImGui::Text("Position:");
		ImGui::SameLine(100.0f);
		ImGui::DragFloat3("##Position", glm::value_ptr(component.position));
		
		ImGui::Text("Rotation:");
		ImGui::SameLine(100.0f);
		ImGui::DragFloat3("##Rotation", glm::value_ptr(component.rotation));

		ImGui::Text("Scale:");
		ImGui::SameLine(100.0f);
		ImGui::DragFloat3("##Scale", glm::value_ptr(component.scale));

		ImGui::PopItemWidth();
	}

	template<>
	inline void renderImGuiComponent(Entity entity, Sprite& component) {
		ImGui::PushItemWidth(200.0f);

		ImGui::Text("Color:");
		ImGui::SameLine(100.0f);
		ImGui::ColorEdit4("##Color", glm::value_ptr(component.color));

		ImGui::Text("Texture:");
		ImGui::SameLine(100.0f);
		ImTextureID texture_id{ 0 };
		ImVec2 size = { 100.0f, 100.0f };
		ImVec2 uv0 = { 0.0f, 0.0f };
		ImVec2 uv1 = { 1.0f, 1.0f };
		if(component.texture) {
			uint64_t temp_id = component.texture->getNativeId();
			texture_id = reinterpret_cast<void*>(temp_id);

			float aspect_ratio = float(component.texture->getWidth()) / float(component.texture->getHeight());
			if(aspect_ratio >= 2) {
				size.x = 200.0f;
				size.y = 200.0f / aspect_ratio;
			}
			else {
				size.x = 100.0f * aspect_ratio;
				size.y = 100.0f;
			}

			glm::vec2 temp_uv0 = component.texture->getTextureCoordsBottomLeft();
			glm::vec2 temp_uv1 = component.texture->getTextureCoordsTopRight();
			uv0 = { temp_uv0.x, temp_uv0.y };
			uv1 = { temp_uv1.x, temp_uv1.y };
		}
		ImGui::Image(texture_id, size, uv0, uv1);

		ImGui::PopItemWidth();
	}
	
	template<>
	inline void renderImGuiComponent(Entity entity, Name& component) {

	}

}
