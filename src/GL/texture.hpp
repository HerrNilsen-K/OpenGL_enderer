//
// Created by karl on 12.03.21.
//

#ifndef OPENGL_RENDERER_TEXTURE_HPP
#define OPENGL_RENDERER_TEXTURE_HPP


#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <cstdint>
#include <string_view>

class texture {
public:
    texture();

    void image(const std::string_view &path, uint8_t activeIndex = 0);

    void bind();

    void activate(uint8_t index) const;

    ~texture();

private:
    uint32_t m_texture;
};


inline texture::texture() {
    glGenTextures(1, &m_texture);
}

inline void texture::image(const std::string_view &path, uint8_t activeIndex) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.data(), &width, &height, &channels, 0);
    activate(activeIndex);
    bind();
    GLenum channel = channels == 4 ? GL_RGBA : GL_RGB;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

inline void texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

inline texture::~texture() {
    glDeleteTextures(1, &m_texture);
}

inline void texture::activate(uint8_t index) const {
    glActiveTexture(GL_TEXTURE0 + index);
}


#endif //OPENGL_RENDERER_TEXTURE_HPP
