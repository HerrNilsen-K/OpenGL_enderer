//
// Created by karl on 16.03.21.
//

#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <unordered_map>
#include "sprite.hpp"

//Helper function
constexpr auto getScaleFactor(uint64_t scale) { return std::make_tuple<float, float>(1.f / scale, 1.f / scale); }

sprite::sprite(const window &win)
        : m_winRef(const_cast<window &>(win)), m_posX(0.5f), m_posY(0.5f) {
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
    shaderPath sh = {R"(../shader.vert)", R"(../shader.frag)"};

    m_mesh = std::make_unique<mesh>(vbo, ebo, vao, sh, 2);

    m_winRef = win;
    int x, y;
    glfwGetWindowSize(m_winRef.getHNDL(), &x, &y);
    m_cam.updateAspect(static_cast<uint16_t>(x), static_cast<uint16_t>(y));

    auto[xScale, yScale] = getScaleFactor(10);
    m_cam.updateModel(glm::mat4(glm::scale(m_cam.getModel(), glm::vec3(xScale, yScale, 1))));
}


void sprite::render() {
    m_cam.updateProjection(45.f);
    m_mesh->update(m_cam);
    m_mesh->render();
}

camera &sprite::getCam() {
    return m_cam;
}

void sprite::stepX(float x) {
    m_posX += x;
}

void sprite::update() {
    //m_cam.updateModel(glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(.5, .5, 1))) *
    //                  glm::mat4(glm::translate(m_cam.getModel(), glm::vec3(x * 2 + 1, 0, 0))));


    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m_cam.getModel()[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //m_cam.updateModel(glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(0.1, 0.1, 0))) *
    //                  glm::mat4(glm::translate(m_cam.getModel(), glm::vec3(x * 2, 0, 0))));

    auto[xScale, yScale] = getScaleFactor(10);
    m_cam.updateModel(glm::translate(glm::mat4(1.f), glm::vec3(m_posX * xScale, m_posY * yScale, 0)) *
                      glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(xScale / 2, yScale / 2, 1))));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m_cam.getModel()[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}
