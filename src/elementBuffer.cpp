//
// Created by karl on 11.03.21.
//

#include <GL/glew.h>
#include "elementBuffer.hpp"

elementBuffer::elementBuffer() {
    glGenBuffers(1, &m_elementBuffer);
}

void elementBuffer::data(uint32_t size, const std::any &data) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, std::any_cast<uint32_t *>(data), GL_STATIC_DRAW);
}

elementBuffer::~elementBuffer() {
    glDeleteBuffers(1, &m_elementBuffer);
}

void elementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}
