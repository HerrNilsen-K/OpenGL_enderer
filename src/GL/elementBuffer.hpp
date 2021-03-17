//
// Created by karl on 11.03.21.
//

#ifndef INC_3CARDRENDERER_ELEMENTBUFFER_HPP
#define INC_3CARDRENDERER_ELEMENTBUFFER_HPP


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


#endif //INC_3CARDRENDERER_ELEMENTBUFFER_HPP
