#pragma once

#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"
#include "Comet/Event/MouseEvent.h"
#include "Comet/Event/WindowEvent.h"

#include "Comet/Renderer/OrthographicCamera.h"

namespace comet {

	class OrthographicCameraController {
	public:
		inline OrthographicCameraController(const Ref<OrthographicCamera>& camera, float camera_speed, float zoom_interval) 
			: camera(camera), camera_speed(camera_speed), zoom_interval(zoom_interval) {}

		void onUpdate(Timestep dt);
		void onEvent(Event& e);

		inline const Ref<OrthographicCamera>& getCamera() const { return camera; }
	private:
		bool onWindowResized(WindowResizedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
	private:
		Ref<OrthographicCamera> camera;
		float camera_speed;
		float zoom_interval;
	};

}
