#pragma once

#include "Comet/Renderer/Camera.h"

namespace comet {

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(glm::vec3 position, float base_width, float aspect_ratio, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f }, float near = -1.0f, float far = 1.0f);

		virtual inline glm::mat4 getViewProjection() const override { return view_projection; }

		void setPosition(glm::vec3 position);
		void setAspectRatio(float aspect_ratio);
		void setZoomLevel(float zoom_level);
		void setRotation(glm::vec3 rotation);

		void move(glm::vec2 delta_pos);
		void move(glm::vec3 delta_pos);
		void increaseZoom(float increment);
		void decreaseZoom(float decrement);

		inline glm::vec3 getPosition() const { return position; }
		inline float getBaseWidth() const { return base_width; }
		inline float getAspectRatio() const { return aspect_ratio; }
		inline float getZoomLevel() const { return zoom_level; }
		inline glm::vec3 getRotation() const { return rotation; }
	private:
		void recalculateViewProjection();
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
