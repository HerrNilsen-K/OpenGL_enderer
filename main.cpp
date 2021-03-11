//
// Created by karl on 09.03.21.
//

#include <iostream>
#include <GL/glew.h>
#include <cmath>
#include <dialog.h>
#include "src/buffer.hpp"
#include "src/vertexArray.hpp"
#include "src/shader.hpp"
#include "src/elementBuffer.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

void APIENTRY openglCallbackFunction(GLenum source,
                                     GLenum type,
                                     GLuint id,
                                     GLenum severity,
                                     GLsizei length,
                                     const GLchar *message,
                                     const void *userParam) {

    cout << "---------------------opengl-callback-start------------" << endl;
    cout << "message: " << message << endl;
    cout << "type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            cout << "OTHER";
            break;
    }
    cout << endl;

    cout << "id: " << id << endl;
    cout << "severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
            break;
    }
    cout << endl;
    cout << "---------------------opengl-callback-end--------------" << endl;
}

int main() {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(400, 400, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
    });
    glfwSwapInterval(1);
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    float data[] = {
            -0.5, 0.5,
            0.5, 0.5,
            -0.5, -0.5,
            0.5, -0.5
    };

    unsigned int indicies[] = {
            0, 1, 2,
            1, 2, 3
    };

    buffer vbo;
    vbo.data(sizeof(data), data);
    vertexArray vao;
    vao.data(0, 2, GL_FLOAT, sizeof(float) * 2, 0);
    elementBuffer ebo;
    ebo.data(sizeof(indicies), indicies);


    shader sh;
    sh.attachShaderFile(R"(../shader.vert)", R"(../shader.frag)");
    system("pwd");
    //mat = glm::rotate(mat, glm::degrees(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //mat = glm::translate(mat, glm::vec3(0.5, 0, 0));
    //mat = glm::scale(mat, glm::vec3(1.5, 1.5, 0));

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT);
        vbo.bind();
        vao.bind();
        sh.use();
        glm::mat4x4 mat(1.0f);
        mat *= glm::translate(glm::mat4(1.0), glm::vec3(std::sin(glfwGetTime()), 0, 0));
        sh.uniform("pos", mat);
        ebo.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}