#include "cmt_pch.h"
#include "OrthographicCameraController.h"

#include "Comet/Core/Input.h"

namespace comet {

	void OrthographicCameraController::onUpdate(Timestep dt) {
		if(Input::isKeyPressed(key::A))
			camera->move(glm::vec2(-1.0f, 0.0f) * base_camera_speed * glm::pow(2.0f, camera->getZoomLevel()) * float(dt));
		else if(Input::isKeyPressed(key::D))
			camera->move(glm::vec2(1.0f, 0.0f) * base_camera_speed * glm::pow(2.0f, camera->getZoomLevel()) * float(dt));

		if(Input::isKeyPressed(key::W))
			camera->move(glm::vec2(0.0f, 1.0f) * base_camera_speed * glm::pow(2.0f, camera->getZoomLevel()) * float(dt));
		else if(Input::isKeyPressed(key::S))
			camera->move(glm::vec2(0.0f, -1.0f) * base_camera_speed * glm::pow(2.0f, camera->getZoomLevel()) * float(dt));
	}

	void OrthographicCameraController::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowResizedEvent>(std::bind(&OrthographicCameraController::onWindowResized, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::onMouseScrolled, this, std::placeholders::_1));
	}

	bool OrthographicCameraController::onWindowResized(WindowResizedEvent& e) {
		if(e.getWidth() == 0 || e.getHeight() == 0)
			return false;
		camera->setAspectRatio(float(e.getWidth()) / float(e.getHeight()));
		return false;
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
		camera->increaseZoom(- float(e.getY()) * zoom_interval);
		return true;
	}

}
