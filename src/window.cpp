//
// Created by karl on 15.03.21.
//

#include "window.hpp"

#include <stdexcept>
#include <utility>

void window::init() {
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("GLFW cannot be initilized!");
}

window::window(uint32_t width, uint32_t height, std::string title)
        : m_win(nullptr), m_width(width),
          m_height(height),
          m_title(std::move(title)) {}

void window::createWindow() {
    m_win = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_win)
        throw std::runtime_error("GLFW window could not be created!");
    glfwMakeContextCurrent(m_win);
}

window::~window() {
    if (m_win)
        destroyWindow();
    glfwTerminate();
}

void window::destroyWindow() {
    glfwDestroyWindow(m_win);
    m_win = nullptr;
}

bool window::run() const {
    return glfwWindowShouldClose(m_win);
}

window::windowHNDL window::getHNDL() const {
    return m_win;
}

int window::getKey(int key) const {
    return glfwGetKey(m_win, key);
}
