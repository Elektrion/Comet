#include "cmt_pch.h"
#include "OrthographicCamera.h"

namespace comet {

    OrthographicCamera::OrthographicCamera(glm::vec3 position, float base_width, float aspect_ratio, glm::vec3 rotation, float near, float far) 
        : position(position), base_width(base_width), aspect_ratio(aspect_ratio), zoom_level(0.0f), rotation(rotation), near(near), far(far), view_projection(1.0f) {
        recalculateViewProjection();
    }

    void OrthographicCamera::setPosition(glm::vec3 position) {
        this->position = position;
        recalculateViewProjection();
    }

    void OrthographicCamera::setAspectRatio(float aspect_ratio) {
        this->aspect_ratio = aspect_ratio;
        recalculateViewProjection();
    }

    void OrthographicCamera::setZoomLevel(float zoom_level) {
        this->zoom_level = zoom_level;
        recalculateViewProjection();
    }

    void OrthographicCamera::setRotation(glm::vec3 rotation) {
        this->rotation = rotation;
        recalculateViewProjection();
    }

    void OrthographicCamera::increaseZoom(float increment) {
        this->zoom_level += increment;
        recalculateViewProjection();
    }

    void OrthographicCamera::decreaseZoom(float decrement) {
        this->zoom_level -= decrement;
        recalculateViewProjection();
    }

    void OrthographicCamera::recalculateViewProjection() {
        float width = base_width * glm::pow(2.0f, zoom_level);
        float height = width / aspect_ratio;
        glm::mat4 projection = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, near, far);
        glm::mat4 view = (rotation == glm::vec3(0.0f, 0.0f, 0.0f)) ? glm::mat4(1.0f) : 
            glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) * 
            glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) * 
            glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f });
        view = glm::translate(view, -position);
        view_projection = projection * view;
    }


    Ref<OrthographicCamera> OrthographicCamera::create(glm::vec3 position, float base_width, float aspect_ratio, glm::vec3 rotation, float near, float far) {
        return createRef<OrthographicCamera>(position, base_width, aspect_ratio, rotation, near, far);
    }

}
