//
// Created by karl on 11.03.21.
//

#include <GL/glew.h>
#include "elementBuffer.hpp"

elementBuffer::elementBuffer() : m_indiciesSize(0) {
    glGenBuffers(1, &m_elementBuffer);
}

void elementBuffer::data(uint32_t size, const std::any &data) {
    m_indiciesSize = size;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, std::any_cast<uint32_t *>(data), GL_STATIC_DRAW);
}

elementBuffer::~elementBuffer() {
    glDeleteBuffers(1, &m_elementBuffer);
}

void elementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

uint32_t elementBuffer::getIndiciesSize() const {
    return m_indiciesSize;
}

void elementBuffer::data(const elementBufferData &data) {
    this->data(data.size, data.data);
}
