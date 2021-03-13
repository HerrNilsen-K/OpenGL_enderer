//
// Created by karl on 10.03.21.
//

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include <glm/gtc/type_ptr.hpp>

shader::shader() {
    m_program = glCreateProgram();
}

void shader::use() {
    glUseProgram(m_program);
}

void shader::attachShader(const std::string_view &vertexShaderSource, const std::string_view &fragmentShaderSource) {
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER), fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int success;
    char infoLog[512];

    const char *tempVert = vertexShaderSource.data();
    glShaderSource(vertexShader, 1, &tempVert, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
        std::cerr<< "Vertex F" << std::endl;

    const char *tempFrag = fragmentShaderSource.data();
    glShaderSource(fragmentShader, 1, &tempFrag, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
        std::cerr<< "Fragment F" << std::endl;

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    glLinkProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

shader::~shader() {
    glDeleteProgram(m_program);
}

void shader::uniform(const std::string_view &location, float p1) {
    use();
    glUniform1f(glGetUniformLocation(m_program, location.data()), p1);
}

void shader::uniform(const std::string_view &location, float p1, float p2, float p3) {
    use();
    glUniform3f(glGetUniformLocation(m_program, location.data()), p1, p2, p3);
}

void shader::uniform(const std::string_view &location, const glm::mat4 &mat) {
    use();
    glUniformMatrix4fv(glGetUniformLocation(m_program, location.data()), 1, false, glm::value_ptr(mat));
}

void shader::attachShaderFile(const std::string_view &vertexFilePath, const std::string_view &fragmentFilePath) {
    std::ifstream getShader(vertexFilePath.data(), std::ios::in);
    if(!getShader)
        throw std::ifstream::failure("Couldn't open vertex source file");
    std::stringstream vertexSource;
    vertexSource << getShader.rdbuf();
    getShader.close();
    getShader.open(fragmentFilePath.data(), std::ios::in);
    if(!getShader)
        throw std::ifstream::failure("Couldn't open fragment source file");
    std::stringstream fragmentSource;
    fragmentSource << getShader.rdbuf();

    attachShader(vertexSource.str(), fragmentSource.str());
}

void shader::uniform(const camera &cam) {
    uniform("model", cam.getModel());
    uniform("view", cam.getView());
    uniform("projection", cam.getProjection());
}
