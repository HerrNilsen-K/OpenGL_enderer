//
// Created by karl on 16.03.21.
//

#ifndef INC_3CARDRENDERER_SPRITE_HPP
#define INC_3CARDRENDERER_SPRITE_HPP

#include <memory>
#include "mesh.hpp"
#include "../window.hpp"

struct color;

class sprite {
private:
    std::unique_ptr<mesh> m_mesh;
    camera m_cam;
    glm::mat4 m_model;
    float m_posX, m_posY;


public:
    sprite();

    explicit sprite(const window &win);

    void render();

    void update();

    void stepX(float x);

    void stepY(float y);

    void setColor(color col);

};


struct color{
    uint8_t r : 8;
    uint8_t g : 8;
    uint8_t b : 8;
    uint8_t a : 8;
};


#endif //INC_3CARDRENDERER_SPRITE_HPP
