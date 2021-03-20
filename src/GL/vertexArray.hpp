//
// Created by karl on 10.03.21.
//

#ifndef INC_3CARDRENDERER_VERTEXARRAY_HPP
#define INC_3CARDRENDERER_VERTEXARRAY_HPP


#include <GL/glew.h>
#include <cstdint>

struct vertexArrayData {
    uint8_t index;
    uint32_t size;
    GLenum type;
    uint32_t stride;
    void *poffset;
};

class vertexArray {
public:
    vertexArray();

    void data(uint8_t index, uint32_t size, GLenum type, uint32_t stride, void *offset) const;
    void data(const vertexArrayData *data, uint8_t count = 1) const;

    void bind() const;

    ~vertexArray();

private:
    uint32_t m_vertexArray;
};


inline vertexArray::vertexArray() {
    glCreateVertexArrays(1, &m_vertexArray);
}

inline void vertexArray::data(uint8_t index, uint32_t size, GLenum type, uint32_t stride, void *offset) const {
    bind();
    glVertexAttribPointer(index, size, type, 0, stride, offset);
    glEnableVertexAttribArray(index);
}

inline void vertexArray::bind() const {
    glBindVertexArray(m_vertexArray);
}

inline vertexArray::~vertexArray() {
    glDeleteVertexArrays(1, &m_vertexArray);
}

inline void vertexArray::data(const vertexArrayData *data, uint8_t count) const {
    for (int i = 0; i < count; ++i)
        this->data(data[i].index, data[i].size, data[i].type, data[i].stride, data[i].poffset);
}


#endif //INC_3CARDRENDERER_VERTEXARRAY_HPP
