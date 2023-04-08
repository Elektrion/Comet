#include "cmt_pch.h"
#include "EditorLayer.h"
#include "Comet/Scene/Components.h"

namespace comet {

	void EditorLayer::onAttatch() {}

	void EditorLayer::onDetatch() {}

	void EditorLayer::onUpdate(Timestep dt) {
		if(!active_scene) return;

		active_scene->onUpdate(dt);
	}

	void EditorLayer::onImGuiRender() {
		if(!active_scene) return;

		ImGui::Begin("Entity Panel");
		for(auto entity : active_scene->getEntities()) {
			if(auto namecomp = entity.getComponent<components::Name>())
				ImGui::Text(namecomp->name.c_str());
			else
				ImGui::Text("unnamed");

			if(auto transform = entity.getComponent<components::Transform>()) {
				if(ImGui::TreeNode((std::to_string(entity.getHandle()) + "_Transform").c_str(), "Transform")) {
					components::renderImGuiComponent<components::Transform>(entity, *transform);
					ImGui::TreePop();
				}
			}

			if(auto sprite = entity.getComponent<components::Sprite>()) {
				if(ImGui::TreeNode((std::to_string(entity.getHandle()) + "_Sprite").c_str(), "Sprite")) {
					components::renderImGuiComponent<components::Sprite>(entity, *sprite);
					ImGui::TreePop();
				}
			}
		}
		ImGui::End();
	}

	void EditorLayer::onEvent(Event& e) {
		if(!active_scene) return;

		active_scene->onEvent(e);
	}


	void EditorLayer::addScene(const std::string& name, Ref<Scene> scene) {
		scenes.emplace(name, scene);
	}

	void EditorLayer::removeScene(const std::string& name) {
		scenes.erase(name);
	}

	void EditorLayer::setActiveScene(const std::string& name) {
		if(scenes.contains(name))
			active_scene = scenes[name];
	}

}
