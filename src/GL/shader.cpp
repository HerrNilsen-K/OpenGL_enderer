//
// Created by karl on 10.03.21.
//

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "../util.hpp"
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
    if(!getShader) {
        throw std::ifstream::failure("Couldn't open vertex source file");
    }
    std::stringstream vertexSource;
    vertexSource << getShader.rdbuf();
    getShader.close();
    getShader.open(fragmentFilePath.data(), std::ios::in);
    if(!getShader) {
        throw std::ifstream::failure("Couldn't open fragment source file");
    }
    std::stringstream fragmentSource;
    fragmentSource << getShader.rdbuf();

    attachShader(vertexSource.str(), fragmentSource.str());
}

void shader::uniform(const camera &cam) {
    uniform("view", cam.getView());
    uniform("projection", cam.getProjection());
}

void shader::uniform(const std::string_view &location, int p1) {
    use();
    glUniform1i(glGetUniformLocation(m_program, location.data()), p1);
}

void shader::attachShaderFile(const shaderPath &shaderPath) {
    attachShaderFile(shaderPath.svertex, shaderPath.sfragment);
}

void shader::uniform(const std::string_view &location, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4) {
    use();
    double rResult = map(p1, 0, 255, 0, 1);
    double gResult = map(p2, 0, 255, 0, 1);
    double bResult = map(p3, 0, 255, 0, 1);
    double aResult = map(p4, 0, 255, 0, 1);
    std::cout << "r: " << rResult << std::endl;
    glUniform4f(glGetUniformLocation(m_program, location.data()), rResult, gResult, bResult, aResult);
}
