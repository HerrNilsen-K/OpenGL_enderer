//
// Created by karl on 13.03.21.
//

#ifndef INC_3CARDRENDERER_CAMERA_HPP
#define INC_3CARDRENDERER_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera {
private:
    glm::mat4 m_view{};
    glm::mat4 m_projection{};

    float m_fov{};
    float m_aspectX{}, m_aspectY{};
    float m_zNear{}, m_zFar{};


public:
    camera();

    camera(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);

    void updateView(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    void updateProjection(float fov);


    void updateAspect(float x, float y);

    void updateAspect(uint16_t x, uint16_t y);

    glm::mat4 getView() const;

    glm::mat4 getProjection() const;

};

inline void camera::updateView(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    m_view = glm::lookAt(eye, center, up);
}

inline glm::mat4 camera::getView() const {
    return m_view;
}


inline camera::camera()
        : m_view(1.f), m_projection(1.f), m_fov(45.f), m_aspectX(400.f), m_aspectY(400.f), m_zNear(.1f),
          m_zFar(100.f) {}

inline void camera::updateProjection(float fov) {
    m_fov = fov;
    //m_projection = glm::perspective(glm::radians(m_fov), m_aspectX / m_aspectY, m_zNear, m_zFar);
    m_projection = glm::ortho(0.f, 1.f, 0.f, 1.f, -1.f, 1.f);
}


inline glm::mat4 camera::getProjection() const {
    return m_projection;
}

inline camera::camera(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection)
        : m_view(view), m_projection(projection), m_fov(45.f), m_aspectX(400.f), m_aspectY(400.f),
          m_zNear(.1f),
          m_zFar(100.f) {

}

inline void camera::updateAspect(float x, float y) {
    m_aspectX = x;
    m_aspectY = y;
}

inline void camera::updateAspect(uint16_t x, uint16_t y) {
    m_aspectX = x;
    m_aspectY = y;
}

#endif //INC_3CARDRENDERER_CAMERA_HPP
