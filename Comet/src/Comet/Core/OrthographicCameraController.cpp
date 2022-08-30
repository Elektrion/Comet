#include "cmt_pch.h"
#include "OrthographicCameraController.h"

namespace comet {

	void OrthographicCameraController::onUpdate(Timestep dt) {
		
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
