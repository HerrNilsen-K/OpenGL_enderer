//
// Created by karl on 09.03.21.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/window.hpp"
#include "src/models/sprite.hpp"

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

static constexpr int WINDOW_DIM = 600;

int main() {
    window::init();
    window win(WINDOW_DIM, WINDOW_DIM);
    win.createWindow();
    glfwSetFramebufferSizeCallback(win.getHNDL(), [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
    });
    glfwSwapInterval(0);
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    glm::vec2 playerPos(4.5, 1);
    dynamicSprite player(win);
    player.setColor(color{122, 122, 50});

    dynamicSprite<1, 1> background(win);
    dynamicSprite<1, 5> floor(win);
    floor.setColor(color{0, 255, 20});


    const std::size_t DIMENSION = 10;
    dynamicSprite<DIMENSION> field[DIMENSION][DIMENSION];


    for (int i = 0; i < DIMENSION; ++i)
        for (int j = 0; j < DIMENSION; ++j) {
            field[i][j] = dynamicSprite<DIMENSION>(win);
            field[i][j].stepX(i);
            field[i][j].stepY(j);
            field[i][j].setColor(color{static_cast<uint8_t>(i * 20), 0, static_cast<uint8_t>(j * 20)});
        }
    double time = glfwGetTime();

    bool isJumping = false, isFalling = false;
    double fallSpeed = 0;
    const int MOVE_SPEED = 5;
    while (!win.run()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSwapBuffers(win.getHNDL());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /*for (int i = 0; i < DIMENSION; ++i)
            for (int j = 0; j < DIMENSION; ++j) {
                field[i][j].update();
                field[i][j].render();
            }
            */
        background.update();
        background.render();
        floor.update();
        floor.render();

        if (win.getKey(GLFW_KEY_W) == GLFW_PRESS && !isFalling) {
            //playerPos.y += deltaTime * MOVE_SPEED;
            isJumping = true;
        }
        if (win.getKey(GLFW_KEY_S) == GLFW_PRESS) {
            playerPos.y += -deltaTime * MOVE_SPEED;
        }
        if (win.getKey(GLFW_KEY_A) == GLFW_PRESS) {
            playerPos.x += -deltaTime * MOVE_SPEED;
        }
        if (win.getKey(GLFW_KEY_D) == GLFW_PRESS) {
            playerPos.x += deltaTime * MOVE_SPEED;
        }

        if (isJumping && !isFalling) {
            fallSpeed = 0;
            playerPos.y += deltaTime;
            if (playerPos.y >= 2) {
                isJumping = false;
                isFalling = true;
            }
        }

        if (isFalling && playerPos.y <= 1)
            isFalling = false;

        if (playerPos.y > 1 && isJumping == false) {
            if (time - currentFrame <= .1) {
                fallSpeed += deltaTime / 10;
                time += .1;
            }
            playerPos.y -= fallSpeed;
        }

        player.setPos(playerPos);
        player.update();
        player.render();

        std::cout << 1 / deltaTime << std::endl;

        glfwPollEvents();
    }

    return 0;
}