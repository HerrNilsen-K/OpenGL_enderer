//
// Created by karl on 10.03.21.
//

#ifndef INC_3CARDRENDERER_VERTEXARRAY_HPP
#define INC_3CARDRENDERER_VERTEXARRAY_HPP


#include <GL/glew.h>
#include <cstdint>

class vertexArray {
public:
    vertexArray();

    void data(uint8_t index, uint32_t size, GLenum type, uint32_t stride, void *offset) const;

    void bind() const;

    ~vertexArray();

private:
    uint32_t m_vertexArray;
};


#endif //INC_3CARDRENDERER_VERTEXARRAY_HPP
