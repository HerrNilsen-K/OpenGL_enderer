//
// Created by karl on 16.03.21.
//

#ifndef INC_3CARDRENDERER_SPRITE_HPP
#define INC_3CARDRENDERER_SPRITE_HPP

#include <memory>
#include "src/mesh.hpp"
#include "src/window.hpp"


class sprite {
private:
    std::unique_ptr<mesh> m_mesh;
    camera m_cam;
    glm::mat4 m_model;
    window& m_winRef;
    float m_posX, m_posY;


public:
    explicit sprite(const window &win);

    void render();

    void update();

    void stepX(float x);

    void stepY(float y);

};


#endif //INC_3CARDRENDERER_SPRITE_HPP
