#pragma once

#include <string>
#include <unordered_map>

#include "Comet/Core/Core.h"
#include "Comet/Core/Layer.h"

#include "Comet/Scene/Scene.h"

namespace comet {

	class EditorLayer : public Layer {
	public:
		virtual void onAttatch() override;
		virtual void onDetatch() override;

		virtual void onUpdate(Timestep dt) override;
		virtual void onImGuiRender() override;
		virtual void onEvent(Event& e) override;

		void addScene(const std::string& name, Ref<Scene> scene = Scene::createScene());
		void removeScene(const std::string& name);
		void setActiveScene(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Scene>> scenes = {};
		Ref<Scene> active_scene = nullptr;
	};

}
