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

double randomDouble(double from, double to) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution urd(from, to);
    return urd(mt);
}


class collisionBox {
    double m_x, m_y, m_w, m_h;
public:
    collisionBox(double x, double y, double w, double h)
            : m_x(x), m_y(y), m_w(w), m_h(h) {}

    [[nodiscard]] bool checkCollision(const collisionBox &box) const {
        // bool result =
        //         this->m_x + this->m_w >= box.m_x &&
        //         this->m_x <= box.m_x + box.m_w ||
        //         this->m_y + this->m_h >= box.m_y &&
        //         this->m_y <= box.m_y + box.m_h;

        bool result =
                m_x + m_w > box.m_x &&
                m_x < box.m_x + box.m_w &&
                m_y > box.m_y + box.m_h &&
                m_y + m_h < box.m_y;
        return result;
    }
};

static constexpr int WINDOW_DIM = 600;

int main() {
    window::init();
    window win(WINDOW_DIM, WINDOW_DIM);
    win.createWindow();
    glfwSetFramebufferSizeCallback(win.getHNDL(), [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
    });
    glfwSwapInterval(1);
    glewInit();

    //glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(openglCallbackFunction, nullptr);

    glm::vec2 playerPos(4.5, 1);
    std::pair<dynamicSprite<10>, collisionBox> player = std::pair<dynamicSprite<10>, collisionBox>(win, collisionBox(
            playerPos.x, playerPos.y, 1. / 10, 1. / 10));
    player.first.setColor(color{122, 122, 50});

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

    double oldTimeSinceStart = 0;
    double stopWatch = glfwGetTime();

    std::vector<std::pair<dynamicSprite<10, 11>, collisionBox>> bricks;
    std::pair<dynamicSprite<10, 10>, collisionBox> dummy =
            std::pair<dynamicSprite<10, 10>, collisionBox>(win, collisionBox(5 , 5 , 1. / 10, 1. / 10));
    dummy.first.setColor(color{1, 1, 0});

    dummy.first.setPos(glm::vec2(5, 5));

    const int MOVE_SPEED = 5, FALL_SPEED = -2;
    const double TIME_TILL_BRICK_SPAWN = 1.5;
    while (!win.run()) {
        double timeSinceStart = glfwGetTime();
        double deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;

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

        if (stopWatch - timeSinceStart <= TIME_TILL_BRICK_SPAWN) {
            //stopWatch += TIME_TILL_BRICK_SPAWN;
            //bricks.emplace_back(std::make_pair(dynamicSprite<10, 11>(win), collisionBox(0, 0, 0, 0)));
            //double position = randomDouble(0, 10);
            //bricks.back().first.setPos(glm::vec2(position, 12));
            //bricks.back().second = collisionBox(position, 12, 1. / 10, 1. / 11);
            //bricks.back().first.setColor(color{247, 47, 7});
        }

        for (auto &&i : bricks) {
            i.first.stepY(FALL_SPEED * deltaTime);
            i.second = collisionBox(i.first.getX(), i.first.getY() + FALL_SPEED * deltaTime, 1. / 10, 1. / 11);
            i.first.update();
            i.first.render();
            if (i.second.checkCollision(player.second)) {

            }
        }

        dummy.first.update();
        dummy.first.render();

        if(win.getKey(GLFW_KEY_F))
            std::cout << "F";

        double x, y;
        glfwGetCursorPos(win.getHNDL(), &x, &y);
        playerPos = glm::vec2(map(x, 0, 600, 0, 10), 10 + -map(y, 0, 600, 0, 10));
        std::cout << playerPos.x << ' ' << playerPos.y << std::endl;

        player.first.setPos(playerPos);
        player.second = collisionBox(playerPos.x + -.5, playerPos.y + -.5, 1. / 10, 1. / 10);
        player.first.update();
        player.first.render();

        if (player.second.checkCollision(dummy.second))
            std::cout << "Yes" << std::endl;

        //std::cout << 1 / deltaTime << std::endl;

        glfwPollEvents();
    }

    return 0;
}