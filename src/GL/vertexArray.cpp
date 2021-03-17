//
// Created by karl on 10.03.21.
//

#include <any>
#include "vertexArray.hpp"

vertexArray::vertexArray() {
    glCreateVertexArrays(1, &m_vertexArray);
}

void vertexArray::data(uint8_t index, uint32_t size, GLenum type, uint32_t stride, void *offset) const {
    bind();
    glVertexAttribPointer(index, size, type, 0, stride, offset);
    glEnableVertexAttribArray(index);
}

void vertexArray::bind() const {
    glBindVertexArray(m_vertexArray);
}

vertexArray::~vertexArray() {
    glDeleteVertexArrays(1, &m_vertexArray);
}

void vertexArray::data(const vertexArrayData *data, uint8_t count) const {
    for (int i = 0; i < count; ++i)
        this->data(data[i].index, data[i].size, data[i].type, data[i].stride, data[i].poffset);
}

