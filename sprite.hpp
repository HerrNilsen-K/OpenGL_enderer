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
    window& m_winRef;


public:
    explicit sprite(const window &win);

    void render();

    void stepX(float x);

    [[nodiscard]] camera &getCam();
};


#endif //INC_3CARDRENDERER_SPRITE_HPP
