//
// Created by karl on 16.03.21.
//

#ifndef INC_3CARDRENDERER_SPRITE_HPP
#define INC_3CARDRENDERER_SPRITE_HPP

#include <memory>
#include "mesh.hpp"
#include "../window.hpp"
#include "../util.hpp"
#include "sprite.hpp"
#include "../GL/texture.hpp"

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

template<uint32_t X = 10, uint32_t Y = X>
class sprite {
private:
    std::unique_ptr<mesh> m_mesh;
    texture m_tex;
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

    void image(const std::string_view &path);
};

//Helper function
inline constexpr auto getScaleFactor(uint64_t x, uint64_t y) { return std::make_tuple<float, float>(1.f / x, 1.f / y); }

template<uint32_t X, uint32_t Y>
inline sprite<X, Y>::sprite(const window &win)
        : m_cam(), m_posX(0.5f), m_posY(0.5f), m_model(1.f) {
    float vertecies[] = {

            -1, 1, 0, 1,
            1, 1, 1, 1,
            -1, -1, 0, 0,
            1, -1, 1, 0
    };
    unsigned indicies[] = {
            0, 1, 2,
            1, 2, 3
    };

    bufferData vbo{sizeof(vertecies), vertecies};
    vertexArrayData vao[] = {{0, 2, GL_FLOAT, sizeof(float) * 4, 0},
                             {1, 2, GL_FLOAT, sizeof(float) * 4, (void *) (sizeof(float) * 2)}};
    elementBufferData ebo = {sizeof(indicies), indicies};
    shaderPath sh = {R"(../src/shader/shader.vert)", R"(../src/shader/shader.frag)"};

    m_mesh = std::make_unique<mesh>(vbo, ebo, vao, sh, 2);

    int x, y;
    glfwGetWindowSize(win.getHNDL(), &x, &y);
    m_cam.updateAspect(static_cast<uint16_t>(x), static_cast<uint16_t>(y));

    auto[xScale, yScale] = getScaleFactor(X, Y);
    m_model = glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(xScale, yScale, 1)));

    setColor(color{255, 255, 255, 0});

}


template<uint32_t X, uint32_t Y>
inline void sprite<X, Y>::render() {
    m_cam.updateProjection(45.f);
    m_mesh->update(m_cam);
    m_mesh->render();
}

template<uint32_t X, uint32_t Y>
inline void sprite<X, Y>::stepX(float x) {
    m_posX += x;
}

template<uint32_t X, uint32_t Y>
inline void sprite<X, Y>::update() {
    auto[xScale, yScale] = getScaleFactor(X, Y);
    m_model = glm::translate(glm::mat4(1.f), glm::vec3(m_posX * xScale, m_posY * yScale, 0)) *
              glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(xScale / 2, yScale / 2, 1)));

    m_mesh->setModel(m_model);
}

template<uint32_t X, uint32_t Y>
inline void sprite<X, Y>::stepY(float y) {
    m_posY += y;
}

template<uint32_t X, uint32_t Y>
inline sprite<X, Y>::sprite()
        : m_posX(0.5f), m_posY(0.5f), m_model(1.f) {

}

template<uint32_t X, uint32_t Y>
inline void sprite<X, Y>::setColor(color col) {
    m_mesh->getShader().uniform("col",
                                map(static_cast<float>(col.r), 0, 255, 0, 1),
                                map(static_cast<float>(col.g), 0, 255, 0, 1),
                                map(static_cast<float>(col.b), 0, 255, 0, 1),
                                map(static_cast<float>(col.a), 0, 255, 0, 1));
}

template<uint32_t X, uint32_t Y>
void sprite<X, Y>::image(const std::string_view &path) {
}


#endif //INC_3CARDRENDERER_SPRITE_HPP
