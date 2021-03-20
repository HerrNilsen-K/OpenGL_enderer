//
// Created by karl on 11.03.21.
//

#ifndef INC_3CARDRENDERER_ELEMENTBUFFER_HPP
#define INC_3CARDRENDERER_ELEMENTBUFFER_HPP


#include <GL/glew.h>
#include <cstdint>
#include <any>

struct elementBufferData {
    uint32_t size;
    std::any data;
};

class elementBuffer {
public:
    elementBuffer();
    void data(uint32_t size, const std::any &data);
    void data(const elementBufferData &data);

    void bind();

    uint32_t getIndiciesSize() const;

    ~elementBuffer();


private:
    uint32_t m_elementBuffer;
    uint32_t m_indiciesSize;
};


inline elementBuffer::elementBuffer() : m_indiciesSize(0) {
    glGenBuffers(1, &m_elementBuffer);
}

inline void elementBuffer::data(uint32_t size, const std::any &data) {
    m_indiciesSize = size;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, std::any_cast<uint32_t *>(data), GL_STATIC_DRAW);
}

inline elementBuffer::~elementBuffer() {
    glDeleteBuffers(1, &m_elementBuffer);
}

inline void elementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
}

inline uint32_t elementBuffer::getIndiciesSize() const {
    return m_indiciesSize;
}

inline void elementBuffer::data(const elementBufferData &data) {
    this->data(data.size, data.data);
}


#endif //INC_3CARDRENDERER_ELEMENTBUFFER_HPP
