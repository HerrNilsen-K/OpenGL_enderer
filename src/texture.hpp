//
// Created by karl on 12.03.21.
//

#ifndef OPENGL_RENDERER_TEXTURE_HPP
#define OPENGL_RENDERER_TEXTURE_HPP


#include <cstdint>
#include <string_view>

class texture {
public:
    texture();

    void image(const std::string_view &path);

    void bind();

    ~texture();

private:
    uint32_t m_texture;
};


#endif //OPENGL_RENDERER_TEXTURE_HPP
