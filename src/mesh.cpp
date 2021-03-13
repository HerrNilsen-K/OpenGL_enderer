//
// Created by karl on 13.03.21.
//

#include "mesh.hpp"

mesh::mesh(const buffer &vbo, const elementBuffer &ebo, const vertexArray &vao, const shader &sh)
        : m_buffer(vbo), m_elementBuffer(ebo),
          m_vertexArray(vao), m_sh(sh) {}

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
