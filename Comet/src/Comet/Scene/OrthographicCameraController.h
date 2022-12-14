#pragma once

#include "Comet/Core/Time.h"

#include "Comet/Event/Event.h"
#include "Comet/Event/MouseEvent.h"
#include "Comet/Event/WindowEvent.h"

#include "Comet/Scene/OrthographicCamera.h"

namespace comet {

	class OrthographicCameraController {
	public:
		inline OrthographicCameraController(const Ref<OrthographicCamera>& camera, float base_camera_speed, float zoom_interval) noexcept
			: camera(camera), base_camera_speed(base_camera_speed), zoom_interval(zoom_interval) {}

		void onUpdate(Timestep dt);
		void onEvent(Event& e);

		inline const Ref<OrthographicCamera>& getCamera() const noexcept { return camera; }
	private:
		bool onWindowResized(WindowResizedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
	private:
		Ref<OrthographicCamera> camera;
		float base_camera_speed;
		float zoom_interval;
	};

}
