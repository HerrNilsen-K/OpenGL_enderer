//
// Created by karl on 11.03.21.
//

#ifndef INC_3CARDRENDERER_ELEMENTBUFFER_HPP
#define INC_3CARDRENDERER_ELEMENTBUFFER_HPP


#include <cstdint>
#include <any>

class elementBuffer {
public:
    elementBuffer();
    void data(uint32_t size, const std::any &data);

    void bind();

    ~elementBuffer();


private:
    uint32_t m_elementBuffer;
};


#endif //INC_3CARDRENDERER_ELEMENTBUFFER_HPP
