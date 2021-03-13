//
// Created by karl on 09.03.21.
//

#ifndef INC_3CARDRENDERER_BUFFER_HPP
#define INC_3CARDRENDERER_BUFFER_HPP

#include <any>

class buffer {
public:
    buffer();

    void data(uint32_t size, std::any data) const;

    ~buffer();

    void bind() const;

private:
    uint32_t m_buffer;
};


#endif //INC_3CARDRENDERER_BUFFER_HPP
