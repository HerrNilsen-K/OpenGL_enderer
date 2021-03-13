//
// Created by karl on 09.03.21.
//

#include <GL/glew.h>
#include "buffer.hpp"

buffer::buffer() {
    glGenBuffers(1, &m_buffer);
}

void buffer::data(uint32_t size, std::any data) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, static_cast<void *>(std::any_cast<float *>(data)), GL_STATIC_DRAW);
}

void buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

buffer::~buffer() {
    glDeleteBuffers(1, &m_buffer);
}
