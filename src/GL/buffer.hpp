//
// Created by karl on 09.03.21.
//

#ifndef INC_3CARDRENDERER_BUFFER_HPP
#define INC_3CARDRENDERER_BUFFER_HPP

#include <GL/glew.h>
#include <any>

struct bufferData {
    uint32_t size;
    std::any data;
};


class buffer {
public:
    buffer();

    void data(uint32_t size, std::any data) const;
    void data(const bufferData &data) const;

    ~buffer();

    void bind() const;

private:
    uint32_t m_buffer;
};

inline buffer::buffer() {
    glGenBuffers(1, &m_buffer);
}

inline void buffer::data(uint32_t size, std::any data) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, static_cast<void *>(std::any_cast<float *>(data)), GL_STATIC_DRAW);
}

inline void buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

inline buffer::~buffer() {
    glDeleteBuffers(1, &m_buffer);
}

inline void buffer::data(const bufferData &data) const {
    this->data(data.size, data.data);
}

#endif //INC_3CARDRENDERER_BUFFER_HPP
