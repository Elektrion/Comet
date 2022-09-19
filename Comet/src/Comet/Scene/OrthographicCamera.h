#pragma once

#include "Comet/Core/Core.h"

#include "Comet/Renderer/Camera.h"

namespace comet {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(glm::vec3 position, float base_width, float aspect_ratio, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f }, float near = -1.0f, float far = 1.0f);

		virtual inline glm::mat4 getViewProjection() const noexcept override { return view_projection; }

		void setPosition(glm::vec3 position) noexcept;
		void setAspectRatio(float aspect_ratio) noexcept;
		void setZoomLevel(float zoom_level) noexcept;
		void setRotation(glm::vec3 rotation) noexcept;

		void move(glm::vec2 delta_pos) noexcept;
		void move(glm::vec3 delta_pos) noexcept;
		void increaseZoom(float increment) noexcept;
		void decreaseZoom(float decrement) noexcept;

		inline glm::vec3 getPosition() const noexcept { return position; }
		inline float getBaseWidth() const noexcept { return base_width; }
		inline float getAspectRatio() const noexcept { return aspect_ratio; }
		inline float getZoomLevel() const noexcept { return zoom_level; }
		inline glm::vec3 getRotation() const noexcept { return rotation; }
	private:
		void recalculateViewProjection() noexcept;
	public:
		static Ref<OrthographicCamera> create(glm::vec3 position, float base_width, float aspect_ratio, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f }, float near = -1.0f, float far = 1.0f);
	private:
		glm::vec3 position;
		float base_width;
		float aspect_ratio;
		float zoom_level;
		glm::vec3 rotation;
		float near;
		float far;
		glm::mat4 view_projection;
	};

}
