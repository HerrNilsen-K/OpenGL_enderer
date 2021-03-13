//
// Created by karl on 09.03.21.
//

#include <iostream>
#include <GL/glew.h>
#include <cmath>
#include <dialog.h>
#include <array>
#include "src/GL/buffer.hpp"
#include "src/GL/vertexArray.hpp"
#include "src/GL/shader.hpp"
#include "src/GL/elementBuffer.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "src/GL/texture.hpp"

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


float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float fov = 45;

std::array<glm::vec3, 3> getCam(GLFWwindow *window) {
    static std::array<glm::vec3, 3> result{glm::vec3{0, 0, -1}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0}};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        result[0].y += 2.5 * deltaTime;
        result[1].y += 2.5 * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        result[0].y -= 2.5 * deltaTime;
        result[1].y -= 2.5 * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        result[0].x += 2.5 * deltaTime;
        result[1].x += 2.5 * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        result[0].x -= 2.5 * deltaTime;
        result[1].x -= 2.5 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        fov = 45;

    return result;
}


int main() {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(400, 400, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
    });
    glfwSwapInterval(1);
    glfwSetScrollCallback(window, [](GLFWwindow *win, double x, double y) {
        if (y > 0)
            fov--;
        else if (y < 0)
            fov++;
    });
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    float data[] = {
            -0.5, 0.5, 0, 1,
            0.5, 0.5, 1, 1,
            -0.5, -0.5, 0, 0,
            0.5, -0.5, 1, 0
    };

    unsigned int indicies[] = {
            0, 1, 2,
            1, 2, 3
    };

    buffer vbo;
    vbo.data(sizeof(data), data);
    vertexArray vao;
    vao.data(0, 2, GL_FLOAT, sizeof(float) * 4, 0);
    vao.data(1, 2, GL_FLOAT, sizeof(float) * 4, (void *) (sizeof(float) * 2));
    elementBuffer ebo;
    ebo.data(sizeof(indicies), indicies);
    texture tex;
    tex.image(R"(../test.png)");


    shader sh;
    sh.attachShaderFile(R"(../shader.vert)", R"(../shader.frag)");
    //mat = glm::rotate(mat, glm::degrees(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //mat = glm::translate(mat, glm::vec3(0.5, 0, 0));
    //mat = glm::scale(mat, glm::vec3(1.5, 1.5, 0));
    glm::mat4x4 model(1.0f), projection(1.0f);
    camera cam;


    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vbo.bind();
        vao.bind();
        tex.bind();
        sh.use();
        //model = glm::ortho(-1, 1, -1, 1, -1, 1);
        projection = glm::perspective(glm::radians(fov), 400.0f / 400.0f, 0.1f, 100.0f);

        sh.uniform("model", model);
        std::array<glm::vec3, 3> camV = getCam(window);
        cam.update(camV[0], camV[1], camV[2]);

        sh.uniform("view", cam);
        sh.uniform("projection", projection);
        ebo.bind();

        glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(*indicies), GL_UNSIGNED_INT, 0);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}