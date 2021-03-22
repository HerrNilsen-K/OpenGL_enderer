//
// Created by karl on 09.03.21.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <random>
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

double randomDouble(double from, double to){
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution urd(from, to);
    return urd(mt);
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

    double lastTime = glfwGetTime();

    std::vector<dynamicSprite<10, 11>> bricks;

    const int MOVE_SPEED = 5, FALL_SPEED = 2 / 1000;
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

        if (win.getKey(GLFW_KEY_A) == GLFW_PRESS && playerPos.x >= .5) {
            playerPos.x += -deltaTime * MOVE_SPEED;
        }
        if (win.getKey(GLFW_KEY_D) == GLFW_PRESS && playerPos.x <= 9.5) {
            playerPos.x += deltaTime * MOVE_SPEED;
        }

        if (lastTime - currentFrame <= 1) {
            lastTime += 1;
            bricks.emplace_back(win);
            bricks.back().setPos(glm::vec2(randomDouble(0, 10), 2));
            bricks.back().setColor(color{247, 47, 7});
        }

        for (auto &&i : bricks) {
            i.stepY(FALL_SPEED * deltaTime);
            i.update();
            i.render();
        }

        player.setPos(playerPos);
        player.update();
        player.render();

        std::cout << 1 / deltaTime << std::endl;

        glfwPollEvents();
    }

    return 0;
}