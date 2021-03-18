//
// Created by karl on 09.03.21.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <memory>
#include "src/GL/buffer.hpp"
#include "src/GL/vertexArray.hpp"
#include "src/GL/shader.hpp"
#include "src/GL/elementBuffer.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "src/GL/texture.hpp"
#include "src/mesh.hpp"
#include "src/window.hpp"
#include "sprite.hpp"

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

int main() {
    window::init();
    window win(600, 600);
    win.createWindow();
    glfwSetFramebufferSizeCallback(win.getHNDL(), [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
    });
    glfwSwapInterval(1);
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    sprite player(win);
    player.stepX(2);
    //player.stepX(-1);

    sprite dummy(win);
    dummy.getCam().updateModel(glm::mat4(glm::scale(glm::mat4(1.f), glm::vec3(.5, .5, 1))) *
                               glm::mat4(glm::translate(dummy.getCam().getModel(), glm::vec3(3, 3, 1))));


    while (!win.run()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(win.getHNDL());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        player.render();
        dummy.render();


        glfwPollEvents();
    }

    return 0;
}