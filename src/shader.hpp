//
// Created by karl on 10.03.21.
//

#ifndef INC_3CARDRENDERER_SHADER_HPP
#define INC_3CARDRENDERER_SHADER_HPP


#include <cstdint>
#include <string>
#include "glm/glm.hpp"

class shader {
public:
    shader();
    void use();
    void attachShader(const std::string_view &vertexShaderSource, const std::string_view &fragmentShaderSource);
    void attachShaderFile(const std::string_view &vertexFilePath, const std::string_view &fragmentFilePath);

    void uniform(const std::string_view &location, float p1);
    void uniform(const std::string_view &location, float p1, float p2, float p3);
    void uniform(const std::string_view &location, const glm::mat4 &mat);

    ~shader();

private:
    uint32_t m_program;
};


#endif //INC_3CARDRENDERER_SHADER_HPP
