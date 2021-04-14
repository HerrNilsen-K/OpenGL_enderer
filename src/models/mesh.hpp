//
// Created by karl on 13.03.21.
//

#ifndef INC_3CARDRENDERER_MESH_HPP
#define INC_3CARDRENDERER_MESH_HPP


#include "../GL/elementBuffer.hpp"
#include "../GL/buffer.hpp"
#include "../GL/vertexArray.hpp"
#include "../GL/shader.hpp"
#include "../GL/camera.hpp"

class mesh {
public:
    mesh(const bufferData &vbo, const elementBufferData &ebo, const vertexArrayData *vao, const shaderData &sh,
         uint8_t vaoCount = 1);

    void update(const camera &cam);

    void setModel(const glm::mat4 &model);

    void render();

    shader &getShader();

private:
    buffer m_buffer;
    elementBuffer m_elementBuffer;
    vertexArray m_vertexArray;
    shader m_sh;

};

inline mesh::mesh(const bufferData &vbo, const elementBufferData &ebo, const vertexArrayData *vao, const shaderData &sh,
           uint8_t vaoCount) {
    m_buffer.data(vbo);
    m_elementBuffer.data(ebo);
    m_vertexArray.data(vao, vaoCount);
    m_sh.attachShaderFile(sh);
}

inline void mesh::update(const camera &cam) {
    m_sh.uniform(cam);
}

inline void mesh::render() {
    m_buffer.bind();
    m_vertexArray.bind();
    m_elementBuffer.bind();
    m_sh.use();
    glDrawElements(GL_TRIANGLES, m_elementBuffer.getIndiciesSize(), GL_UNSIGNED_INT, 0);
}

inline void mesh::setModel(const glm::mat4 &model) {
    m_sh.uniform("model", model);
}

inline shader &mesh::getShader(){
    return m_sh;
}

#endif //INC_3CARDRENDERER_MESH_HPP
