//
// Created by karl on 13.03.21.
//

#ifndef INC_3CARDRENDERER_CAMERA_HPP
#define INC_3CARDRENDERER_CAMERA_HPP

#include <glm/glm.hpp>

class camera {
private:
    glm::mat4 m_view;

public:
    camera();
    camera(const glm::mat4 &view);
    void update(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    glm::mat4 getView() const;

};


#endif //INC_3CARDRENDERER_CAMERA_HPP
