//
// Created by karl on 16.03.21.
//

#ifndef INC_3CARDRENDERER_SPRITE_HPP
#define INC_3CARDRENDERER_SPRITE_HPP

#include <memory>
#include "mesh.hpp"
#include "../window.hpp"
#include "../util.hpp"

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


struct color {
    uint8_t r: 8;
    uint8_t g: 8;
    uint8_t b: 8;
    uint8_t a: 8;
};

//Helper function
inline constexpr auto getScaleFactor(uint64_t scale) { return std::make_tuple<float, float>(1.f / scale, 1.f / scale); }

inline sprite::sprite(const window &win)
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
    shaderData sh = {false,
                     "#version 330 core\n"
                     "\n"
                     "layout(location = 0) in vec2 position;\n"
                     "layout(location = 1) in vec2 aTexPos;\n"
                     "\n"
                     "uniform mat4 model;\n"
                     "uniform mat4 view;\n"
                     "uniform mat4 projection;\n"
                     "\n"
                     "out vec2 texPos;\n"
                     "\n"
                     "void main(){\n"
                     "    gl_Position = projection * view * model * vec4(position, 0, 1);\n"
                     "    texPos = aTexPos;\n"
                     "}\n",

                     "#version 330 core\n"
                     "\n"
                     "layout(location = 0) out vec4 color;\n"
                     "in vec2 texPos;\n"
                     "uniform sampler2D tex;\n"
                     "\n"
                     "uniform vec4 col;\n"
                     "\n"
                     "void main(){\n"
                     "	color = vec4(col);\n"
                     "    //color = texture(tex, texPos);\n"
                     "}\n"
    };

    m_mesh = std::make_unique<mesh>(vbo, ebo, vao, sh, 2);

    int x, y;
    glfwGetWindowSize(win.getHNDL(), &x, &y);
    m_cam.updateAspect(static_cast<uint16_t>(x), static_cast<uint16_t>(y));

    auto[xScale, yScale] = getScaleFactor(10);
    m_model = glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(xScale, yScale, 1)));
}


inline void sprite::render() {
    m_cam.updateProjection(45.f);
    m_mesh->update(m_cam);
    m_mesh->render();
}

inline void sprite::stepX(float x) {
    m_posX += x;
}

inline void sprite::update() {
    auto[xScale, yScale] = getScaleFactor(10);
    m_model = glm::translate(glm::mat4(1.f), glm::vec3(m_posX * xScale, m_posY * yScale, 0)) *
              glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(xScale / 2, yScale / 2, 1)));

    m_mesh->setModel(m_model);
}

inline void sprite::stepY(float y) {
    m_posY += y;
}

inline sprite::sprite()
        : m_posX(0.5f), m_posY(0.5f), m_model(1.f) {

}

inline void sprite::setColor(color col) {
    m_mesh->getShader().uniform("col",
                                map(static_cast<float>(col.r), 0, 255, 0, 1),
                                map(static_cast<float>(col.g), 0, 255, 0, 1),
                                map(static_cast<float>(col.b), 0, 255, 0, 1),
                                map(static_cast<float>(col.a), 0, 255, 0, 1));
}


#endif //INC_3CARDRENDERER_SPRITE_HPP
