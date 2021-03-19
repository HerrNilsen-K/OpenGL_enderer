//
// Created by karl on 13.03.21.
//

#include "mesh.hpp"

mesh::mesh(const bufferData &vbo, const elementBufferData &ebo, const vertexArrayData *vao, const shaderPath &sh,
           uint8_t vaoCount) {
    m_buffer.data(vbo);
    m_elementBuffer.data(ebo);
    m_vertexArray.data(vao, vaoCount);
    m_sh.attachShaderFile(sh);
}

void mesh::update(const camera &cam) {
    m_sh.uniform(cam);
}

void mesh::render() {
    m_buffer.bind();
    m_vertexArray.bind();
    m_elementBuffer.bind();
    m_sh.use();
    glDrawElements(GL_TRIANGLES, m_elementBuffer.getIndiciesSize(), GL_UNSIGNED_INT, 0);
}

void mesh::setModel(const glm::mat4 &model) {
    m_sh.uniform("model", model);
}
