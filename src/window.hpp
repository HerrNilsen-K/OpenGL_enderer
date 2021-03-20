//
// Created by karl on 15.03.21.
//

#ifndef INC_3CARDRENDERER_WINDOW_HPP
#define INC_3CARDRENDERER_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

class window {
public:
    typedef GLFWwindow *windowHNDL;

    static void init();

    explicit window(uint32_t width = 640, uint32_t height = 480, std::string title = "Hello Window");

    void createWindow();

    void destroyWindow();

    [[nodiscard]] bool run() const;

    [[nodiscard]] windowHNDL getHNDL() const;

    [[nodiscard]] int getKey(int key) const;

    ~window();

private:
    windowHNDL m_win;

    uint32_t m_width, m_height;
    std::string m_title;
};

inline void window::init() {
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("GLFW cannot be initilized!");
}

inline window::window(uint32_t width, uint32_t height, std::string title)
        : m_win(nullptr), m_width(width),
          m_height(height),
          m_title(std::move(title)) {}

inline void window::createWindow() {
    m_win = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_win)
        throw std::runtime_error("GLFW window could not be created!");
    glfwMakeContextCurrent(m_win);
}

inline window::~window() {
    if (m_win)
        destroyWindow();
    glfwTerminate();
}

inline void window::destroyWindow() {
    glfwDestroyWindow(m_win);
    m_win = nullptr;
}

inline bool window::run() const {
    return glfwWindowShouldClose(m_win);
}

inline window::windowHNDL window::getHNDL() const {
    return m_win;
}

inline int window::getKey(int key) const {
    return glfwGetKey(m_win, key);
}

#endif //INC_3CARDRENDERER_WINDOW_HPP
