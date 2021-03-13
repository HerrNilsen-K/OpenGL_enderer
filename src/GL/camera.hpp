//
// Created by karl on 13.03.21.
//

#ifndef INC_3CARDRENDERER_CAMERA_HPP
#define INC_3CARDRENDERER_CAMERA_HPP

#include <glm/glm.hpp>

class camera {
private:
    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_projection;

public:
    camera();
    camera(const glm::mat4 &view);

    void updateModel(const glm::mat4 &model);
    void updateView(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
    void updateProjection(const glm::mat4 &projection);

    glm::mat4 getModel() const;
    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

};


#endif //INC_3CARDRENDERER_CAMERA_HPP
