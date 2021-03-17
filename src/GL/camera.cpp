//
// Created by karl on 13.03.21.
//

#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

void camera::updateView(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    m_view = glm::lookAt(eye, center, up);
}

glm::mat4 camera::getView() const {
    return m_view;
}


camera::camera()
        : m_model(1.f), m_view(1.f), m_projection(1.f), m_fov(45.f), m_aspectX(400.f), m_aspectY(400.f), m_zNear(.1f),
          m_zFar(100.f) {}

void camera::updateModel(const glm::mat4 &model) {
    m_model = model;
}

void camera::updateProjection(float fov) {
    m_fov = fov;
    //m_projection = glm::perspective(glm::radians(m_fov), m_aspectX / m_aspectY, m_zNear, m_zFar);
    m_projection = glm::ortho(0.f,1.f, 0.f,1.f, -1.f, 1.f);
}

glm::mat4 camera::getModel() const {
    return m_model;
}

glm::mat4 camera::getProjection() const {
    return m_projection;
}

camera::camera(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection)
        : m_model(model), m_view(view), m_projection(projection), m_fov(45.f), m_aspectX(400.f), m_aspectY(400.f),
          m_zNear(.1f),
          m_zFar(100.f) {

}

void camera::updateAspect(float x, float y) {
    m_aspectX = x;
    m_aspectY = y;
}

void camera::updateAspect(uint16_t x, uint16_t y) {
    m_aspectX = x;
    m_aspectY = y;
}
